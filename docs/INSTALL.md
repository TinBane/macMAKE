# macMAKE v0.1.1 RC7 — Linux x86-64 release candidate

This is an unpublished candidate, not a public download. macMAKE is a Linux
development environment for Classic Macintosh software. Its primary
qualified application workflow targets Classic PowerPC CFM/PEF applications;
the separate native M68000 application profile is experimental and bounded.

## Host and targets

- Host: Linux x86-64.
- Primary target: Classic Macintosh PowerPC, CFM/PEF, primarily C89/C.
- Experimental target: native Motorola M68000, classic segmented CODE
  resources, using the exact `classic-68k-segmented-app-c-v1` profile.
- Mac OS runtime behavior must be tested separately. Build and structural
  inspection do not prove that a binary starts or works on a Macintosh OS.

Multiple 68K segments, general A5-relative globals, external 68K libraries,
CFM-68K, general C++ runtime compatibility, native Rust source compilation,
Mac OS X, and full CodeWarrior compatibility are not provided.

## Install from an extracted candidate

Extract the archive, then add its `bin` directory to `PATH`. The supplied
launcher locates the release's bundled toolchains. For a temporary shell:

```sh
export PATH="$HOME/.local/share/macmake/releases/0.1.1/bin:$PATH"
macmake --version
macmake help
macmake doctor
```

Use the installer and version/checksum information supplied with the eventual
approved public release. Do not use an unpublished candidate's checksum as a
public installer pin.

## Prepare the PowerPC first-app dependencies

The archive does not include Universal Interfaces or Metrowerks MSL. The
minimal fetch is explicit, revision-pinned, sparse, and hash-checked. It is
not a grant of use or redistribution rights. Run it only if you are
authorized to use the files:

```sh
macmake sdk fetch --minimal
macmake sdk add "$HOME/.local/share/macmake/macMAKELibs/Universal" \
  --id macos9-sdk
macmake sdk verify macos9-sdk
```

The sample uses three externally supplied MSL libraries. From
`examples/first-app`, place authorized files with the included checker:

```sh
./setup-user-msl.sh "$HOME/.local/share/macmake/macMAKELibs"
```

The helper verifies exact filenames, regular-file status, and expected
SHA-256 values before writing to the sample's ignored `sdk/` directory. It
does not download or redistribute MSL. Review the example's licensing and
dependency notes if your authorized copy differs.

Build, inspect, and repeat without source changes:

```sh
cd examples/first-app
macmake inspect .
macmake doctor . --target "Classic PPC C"
macmake build . --target "Classic PPC C"
macmake inspect-artifact build/HelloPPC/ClassicPPCC/HelloPPC.pef \
  --resource-fork build/HelloPPC/ClassicPPCC/HelloPPC.rsrc \
  --finder-info build/HelloPPC/ClassicPPCC/.finf/HelloPPC.APPL \
  --creator HmPP --file-type APPL --json
macmake build . --target "Classic PPC C"
```

The project has two C translation units. The build emits a PEF, resource
fork, Finder metadata, MacBinary II file, and build evidence. The second build
should be incremental. This small sample returns to Finder; it is not a GUI
application.

## Experimental native 68K example

`examples/first-app/hello-window-68k` uses the independent bundled M68000
GCC/Binutils provider and macMAKE's classic segmented application output.
The exact manifest profile is documented by the installed `macmake help
targets` and `macmake schema manifest --json`. Build it with:

```sh
cd examples/first-app/hello-window-68k
macmake inspect .
macmake doctor . --target "Classic 68K Mac OS 8.1"
macmake build . --target "Classic 68K Mac OS 8.1"
```

Inspect the resulting CODE resources and package using `macmake inspect-artifact`
with the emitted data fork, resource fork, Finder-info sidecar, and MacBinary
paths. See `toolchain/m68k/README.md` and `docs/native-m68k-roadmap.md` for
limits. No Retro68 executable is selected by this profile.

## Rust-produced PowerPC object integration

`examples/classic-rust-interop` builds a small `no_std` Rust library with the
pinned external nightly `rustc 1.70.0-nightly` and extracts its PPC XCOFF
object. macMAKE then consumes the object through its ordinary project/linker,
CFM/PEF, resource, Finder, and MacBinary path. This is a real Rust-compiled
function in the resulting application, but not a Rust compiler provider in
macMAKE. See that example's README for the exact toolchain, SDK prerequisites,
ABI boundary, build command, and reproducible structural test. The RC6 sample
has structural evidence only; its runtime has not been tested. Historical
MacRust runtime evidence is separate.

## CodeWarrior XML imports and Classilla

`macmake import-cw-xml` accepts supported XML project exports, not binary
`.mcp` files. Always inspect the generated manifest and `.cw-import.json`
sidecar before building. `docs/codewarrior-xml-and-classilla.md` records the
supported/partial/unsupported feature matrix and reproducible import steps.
Historical Classilla development produced many target outputs and a package
assembly, but available evidence does not establish a clean full graph rebuild
or a Classilla runtime pass.

## Optional QEMU runtime smoke test

`macmake run` supports an interactive QEMU PowerPC `mac99`/G4 profile with a
user-owned Mac OS 9.2.2 disk. It creates a copy-on-write overlay and preserves
the base image. The operator stages and launches the application inside the
guest and confirms each checkpoint. The command records QEMU identity,
expected guest OS, hashes, screenshots, and separate launch/visible-state/
exit confirmations. It does not bundle ROMs or OS images, copy the host
artifact into HFS, or automate Finder. QEMU screenshots are validated P6 PPM
files with checkpoint metadata. A real RC6 makePAD run was observed on Mac OS
9.2.2; that result does not test RC7's screenshot change. See
`docs/emulator-run.md` and `docs/v0.1.1-release-notes.md`.

## Analytics and release checks

The installer accepts `--no-analytics` even when piped:

```sh
curl -fsSL https://macmake.dev/install.sh | bash -s -- --no-analytics
```

The preference is persisted for that installation. The installer may send one
completion event after a successful install unless opted out; it does not send
an opt-out event. macMAKE CLI invocations and builds send no telemetry. The
website has separate privacy-respecting page analytics. See the installer's
privacy note for the exact data fields and network endpoint.

Use `macmake help`, `macmake help --all --json`, and
`macmake schema manifest --json` offline for the installed version's CLI
contract. See the `docs/` directory for language, C++, CodeWarrior import,
emulator, 68K roadmap, and qualification details.
