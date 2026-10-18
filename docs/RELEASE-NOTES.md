# macMAKE v0.1.1 RC7 — Linux release candidate

RC7 is an unpublished Linux x86-64 release candidate based on the frozen RC6
payload. It preserves the qualified GNU compiler and 68K toolchain files and
corrects `macmake run` screenshot evidence handling. No public release or
installer activation is implied.

## Included

- **Installer and first application:** fixes the case-sensitive
  `macMAKELibs` paths, verifies the three user-supplied MSL archives before
  copying, and has a clean-home integration test that fetches/registers the
  pinned Universal Interfaces subset, builds the two-source example, checks
  the PEF/resource/Finder/MacBinary outputs, and verifies incremental no-op
  behavior.
- **Minimal SDK onboarding:** `macmake sdk fetch --minimal` uses the pinned
  manifest, sparse checkout, and per-file integrity checks. Registration is
  explicit. Apple and Metrowerks files remain outside the binary package and
  may be used only by people authorized to use them.
- **Experimental native M68000:** preserves the independent GCC 12.2.0 /
  Binutils 2.46.1 path, macMAKE-owned classic CODE 0/CODE 1 creation, bounded
  Toolbox veneers, Finder metadata, and MacBinary. The profile remains one
  near-model CODE 1 segment; it does not imply general System 6–9 support or
  CFM-68K. See `docs/native-m68k-roadmap.md`.
- **Rust-to-Classic PowerPC integration:** adds a source-available sample
  where a pinned external Rust nightly builds a PPC XCOFF object and the
  installed macMAKE CLI links it into a CFM/PEF application and packages it.
  Rust is not a direct `macmake build` source language and the Rust compiler
  is not bundled. Historical MacRust runtime demonstrations are identified
  separately from RC6 build evidence.
- **CodeWarrior XML/Classilla guide:** documents XML export/import, target
  selection, explicit membership, ordered libraries, SDK setup, build and
  artifact inspection. Historical Classilla target builds and package
  assembly are distinguished from a clean full rebuild and runtime test,
  neither of which is claimed.
- **Optional QEMU runtime workflow:** `macmake run` supports one interactive
  QEMU PowerPC `mac99` / G4 / Mac OS 9.2.2 profile using the user's own disk
  image. It uses a copy-on-write overlay and records separate operator
  confirmations; it does not inject an application or automate Finder.
  QMP screenshots are saved and validated as P6 PPM files with `.ppm`
  extensions and checkpoint metadata. Duplicate boot/application frames
  cannot be used to confirm an application state.
- **Installer analytics opt-out:**
  `curl -fsSL https://macmake.dev/install.sh | bash -s -- --no-analytics`
  propagates and persists the opt-out. The CLI itself sends no telemetry.

## Compatibility boundary

The established Linux x86-64 to Classic PowerPC CFM/PEF C workflow remains
the primary application profile. Native M68000 segmented applications are
experimental and limited as described above. macMAKE does not claim complete
CodeWarrior compatibility, general C++ runtime support, direct Rust source
compilation, Mac OS X targets, or CFM-68K support.

## Runtime evidence and qualification status

The exact RC6 Linux CLI built makePAD, and that application was observed in
QEMU 8.2.2 using a Mac OS 9.2.2 guest with a `mac99`/G4 profile. The operator
observed text entry, an unsaved-changes dialog, and return to Finder. The
makePAD MacBinary SHA-256 was
`505a3b1deb62ffc396537b1010c8f23921f4ae4308ac6ee989ccf7cd285ca3d1`. This is
one application and one guest runtime result; it does not establish that all
applications or operating-system versions work.

RC6's runner screenshots had a verified defect: QEMU wrote P6 PPM bytes to
`.png` paths, and the two checkpoint files were byte-identical. RC7 corrects
the format, metadata, operator prompts, and duplicate-image handling. The
fake-QEMU regression models QEMU 8.2.2 PPM output. A corrected real-guest
capture is still required before RC7 runtime evidence can be claimed.

RC7 must pass the exact-archive local and clean Ubuntu 24.04 qualification
before release approval. Hosted GitHub Actions are optional and were not
scheduled because of the account billing restriction; this is recorded as
**NOT RUN — billing restriction**, not a product test failure. Host-side
structural validation does not establish runtime behavior on a Macintosh OS.
