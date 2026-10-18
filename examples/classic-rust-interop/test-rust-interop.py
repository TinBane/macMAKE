#!/usr/bin/env python3
"""Build and structurally verify the Rust-object + macMAKE application path."""

from __future__ import annotations

import argparse
import hashlib
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys


ROOT = Path(__file__).resolve().parent
TARGET = "Classic PPC Rust Interop"
BUILD = ROOT / "build/RustInterop/ClassicPPCRustInterop"
OBJECT = ROOT / "build/rust/macmake_rust_value.o"
PEF = BUILD / "RustInterop.pef"
RESOURCE = BUILD / "RustInterop.rsrc"
MACBINARY = BUILD / "RustInterop.bin"
FINDER = BUILD / ".finf/RustInterop.APPL"
EVIDENCE = BUILD / "RustInterop.build-evidence.json"


def run(args: list[str], *, cwd: Path, env: dict[str, str]) -> subprocess.CompletedProcess[str]:
    result = subprocess.run(args, cwd=cwd, env=env, text=True, capture_output=True, timeout=360, check=False)
    if result.returncode:
        sys.stderr.write(result.stdout)
        sys.stderr.write(result.stderr)
        raise SystemExit(f"command failed ({result.returncode}): {' '.join(args)}")
    return result


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--macmake", default="macmake", help="installed macMAKE executable or PATH command")
    parser.add_argument("--skip-rust-build", action="store_true", help="use the existing Rust XCOFF object")
    options = parser.parse_args()

    cli = shutil.which(options.macmake) if os.sep not in options.macmake else options.macmake
    if not cli or not Path(cli).is_file():
        raise SystemExit(f"macMAKE executable not found: {options.macmake}")
    cli = str(Path(cli).resolve())
    env = os.environ.copy()

    if not options.skip_rust_build:
        run(["bash", str(ROOT / "build-rust.sh")], cwd=ROOT, env=env)

    if not OBJECT.is_file() or OBJECT.is_symlink():
        raise SystemExit(f"missing regular Rust XCOFF object: {OBJECT}")
    if OBJECT.read_bytes()[:2] != b"\x01\xdf":
        raise SystemExit("Rust compiler output is not big-endian PPC XCOFF32")

    version = run([cli, "--version"], cwd=ROOT, env=env).stdout.strip()
    if not version.startswith("macMAKE 0.1.1"):
        raise SystemExit(f"expected a macMAKE 0.1.1 binary, got {version!r}")
    run([cli, "doctor", ".", "--target", TARGET], cwd=ROOT, env=env)
    run([cli, "build", ".", "--target", TARGET], cwd=ROOT, env=env)
    inspect = run(
        [
            cli,
            "inspect-artifact",
            str(PEF),
            "--resource-fork",
            str(RESOURCE),
            "--finder-info",
            str(FINDER),
            "--creator",
            "HmRS",
            "--file-type",
            "APPL",
            "--json",
        ],
        cwd=ROOT,
        env=env,
    )
    inspection = json.loads(inspect.stdout)
    checks = inspection.get("checks", [])
    if not checks or any(check.get("passed") is not True for check in checks):
        raise SystemExit("independent artifact inspection did not report all checks passed")

    evidence = json.loads(EVIDENCE.read_text(encoding="utf-8"))
    if evidence.get("format") != "single-fragment-CFM-application":
        raise SystemExit("macMAKE build evidence is not for a single-fragment CFM application")
    rust_inputs = [
        item for item in evidence.get("inputs", [])
        if item.get("name") == "RustValue" and item.get("kind") == "library"
    ]
    if len(rust_inputs) != 1 or rust_inputs[0].get("sha256") != digest(OBJECT):
        raise SystemExit("final macMAKE link evidence does not include the current Rust XCOFF object")
    if evidence.get("artifact_sha256") != digest(PEF):
        raise SystemExit("PEF hash does not match macMAKE build evidence")
    if evidence.get("resource_sha256") != digest(RESOURCE):
        raise SystemExit("resource fork hash does not match macMAKE build evidence")
    if evidence.get("macbinary_sha256") != digest(MACBINARY):
        raise SystemExit("MacBinary hash does not match macMAKE build evidence")
    if not any(item.get("library") == "CarbonLib" and item.get("symbol") == "SysBeep"
               for item in evidence.get("imports", [])):
        raise SystemExit("expected CarbonLib SysBeep import was not recorded")
    if evidence.get("exports") != ["__start"]:
        raise SystemExit("unexpected application entry/export contract")

    print(f"PASS: {version}; Rust XCOFF SHA-256 {digest(OBJECT)}")
    print(f"PEF SHA-256 {digest(PEF)}")
    print(f"resource fork SHA-256 {digest(RESOURCE)}")
    print(f"MacBinary II SHA-256 {digest(MACBINARY)}")
    print(f"independent artifact checks: {len(checks)} passed")
    print("runtime: NOT TESTED by this command; host structural validation only")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
