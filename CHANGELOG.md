# Changelog

All notable changes to the macMAKE public distribution will be documented in this file.

## [0.1.1] - 2026-10-18

### Seven Release Enhancements
- **Installer and First Application**: Fixed case-sensitive library lookup to match the actual layout in `macMAKELibs` repository (`MSL_C/MSL_MacOS/Lib/PPC/MSL_C_Carbon.Lib`, `MSL_Runtime_PPC_D.Lib`, `MSL_Extras/MSL_MacOS/Lib/PPC/MSL_Extras_Carbon.Lib`). Verified safe extraction, SHA-256 validation, incremental rebuilds, and clean unprivileged onboarding.
- **SDK Setup and Onboarding**: Added `macmake sdk fetch --minimal` using sparse git checkout to retrieve the pinned Universal Interfaces subset with SHA-256 validation. Provided `setup-user-msl.sh` helper to verify and stage user-supplied MSL archives without redistributing proprietary SDK materials.
- **Independent Native Motorola 68000 Application Backend**: Bundled GNU GCC 12.2.0 and GNU Binutils 2.46.1 for target `m68k-unknown-elf`, building bounded C89 applications with CODE 0/1 segments, Toolbox veneers, Finder metadata, and MacBinary II packaging without Retro68. Documented a sequenced roadmap separating toolchain capabilities from application-specific observations.
- **External Rust-to-Classic XCOFF Interop**: Added `examples/classic-rust-interop`, demonstrating consumption of big-endian PowerPC XCOFF objects emitted by external pinned Rust nightly (`powerpc-apple-macos.json`), with macMAKE handling native CFM/PEF linking, resources, and MacBinary packaging.
- **CodeWarrior XML Import & Classilla Build Boundary**: Added `macmake import-cw-xml` feature matrix and practical workflow guide in `docs/codewarrior-xml-and-classilla.md` for converting historical XML project exports into `macmake.toml`. Documented the Classilla 128-target inventory and package assembly boundaries.
- **Optional Emulator Execution (`macmake run`)**: Added profile-driven QEMU Mac OS 9.2.2 runner with copy-on-write disk protection, P6 PPM screenshot capture and validation, and structured run reports. Known nonblocking issue: prompt repetition on 250ms timeouts during interactive wait.
- **Analytics Opt-Out**: Provided complete telemetry opt-out via `--no-analytics` installer flag, `MACMAKE_DISABLE_ANALYTICS=1` environment variable, and persistent configuration preference marker.

### Runtime Acceptance
- Qualified on Mac OS 9.2.2 under QEMU 8.2.2 (mac99/G4, 800×600 display) with makePAD MacBinary (SHA-256 `505a3b1deb62ffc396537b1010c8f23921f4ae4308ac6ee989ccf7cd285ca3d1`).
- Interactive text entry confirmed ("rc7 runtime ok"), unsaved-changes dialog presented and dismissed, and return to Finder verified.
- Unmodified P6 PPM screenshots verified at `guest_boot.ppm` (SHA-256 `7dc1fce7441346067023e89d542dc95e9c2e91006e26703769a4326a7c8e6ab2`) and `application_state.ppm` (SHA-256 `2fc378da228afdb12490e3079eb913d2e485f79c8e87966758e152cf61de8bf1`).
- Guest base disk byte-identical before and after run (SHA-256 `5998d787dea695734948a52285e7b57d6cae840f2681a174f98e33ec9e8045e8`).

### Release Assets and Licensing
- Binary archive: `macmake-v0.1.1-linux-x86_64.tar.xz` (73,934,728 bytes, SHA-256 `d83c173d4184a67738df3bad7d0cadb2b6eab45fa2cc06df89f9f7eff4bd0656`).
- Matching GNU corresponding source: `macmake-v0.1.1-rc4-toolchain-sources` (SHA-256 `ddd3b20cbaf3e2cbdca4ed5f61f34946065f71089b9ea7a99bac188213145433`).
- Licensed under the MPLS LLC Proprietary Binary License v1.0, preserving separate third-party and GNU licenses.

## [0.1.0] - 2026-10-13

### Initial Linux Release
- Initial public Linux x86-64 release targeting Classic Mac OS 9 PowerPC CFM/PEF C applications.
- Bundled PowerPC GCC 12.2.0 and GNU Binutils 2.46.1 cross-compiler toolchain.
- Native CFM linker and PEF binary generator with CodeWarrior-style project configuration.
- Macintosh resource processing, Finder metadata generation, and MacBinary II packaging.
- Offline CLI reference, JSON help schema (1.0.0), and manifest schema.
- Binary archive: `macmake-v0.1.0-linux-x86_64.tar.xz` (SHA-256 `3c9da84e53022d16a07208d0591a9964b8399dbe043b3628e227373a6aa6e980`).
- Corresponding source release: `macmake-v0.1.0-toolchain-sources` (SHA-256 `fde5254ecda60264e7e0ab25098e74c3b6108de34e506f2d3941011059923a96`).

## [0.1.0-preview] - 2026-10-06

### Initial Public Repository Setup
- Established public project presence for `macmake.dev`.
- Added high-level architecture, licensing, compatibility, and getting-started documentation.
- Linked corresponding source repository `macmake-gpl` for redistributed open-source toolchain components.
- Established issue tracking templates and project guidelines.
