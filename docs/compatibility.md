# Classic Macintosh OS Compatibility

macMAKE targets Classic Macintosh systems from a modern Linux x86-64 workstation. Compatibility differs by architecture, operating system version, and application complexity.

## Current Release Status (v0.1.1)

### 1. Classic Mac OS 9 PowerPC CFM/PEF (Supported)
- **Host**: Linux x86-64.
- **Workflow**: C89/C source, CodeWarrior-style manifests, Universal Interfaces headers, MSL runtime libraries.
- **Output**: Native CFM/PEF container, resource fork, Finder metadata, MacBinary II packaging.
- **Verified Runtime Acceptance**:
  - **Environment**: QEMU 8.2.2, `mac99` / PowerPC G4, 1 GiB RAM, 800×600 guest display, running Mac OS 9.2.2.
  - **Application**: makePAD MacBinary (SHA-256 `505a3b1deb62ffc396537b1010c8f23921f4ae4308ac6ee989ccf7cd285ca3d1`).
  - **Results**: Launched successfully from guest volume, interactive text entry confirmed ("rc7 runtime ok"), File > Quit invoked unsaved-changes dialog, choosing "Don't Save" closed the dialog, and the guest returned cleanly to Finder.
  - **Screenshot Evidence**: P6 PPM captures at `guest_boot.ppm` (SHA-256 `7dc1fce7441346067023e89d542dc95e9c2e91006e26703769a4326a7c8e6ab2`) and `application_state.ppm` (SHA-256 `2fc378da228afdb12490e3079eb913d2e485f79c8e87966758e152cf61de8bf1`).
  - **Disk Integrity**: Base guest disk byte-identical before and after run (SHA-256 `5998d787dea695734948a52285e7b57d6cae840f2681a174f98e33ec9e8045e8`).

### 2. Motorola 68000 Segmented Applications (Experimental)
- **Backend**: Bundled GNU GCC 12.2.0 and GNU Binutils 2.46.1 for target `m68k-unknown-elf` (no Retro68 dependency).
- **Supported Profile**: C89, one near-model CODE 1 segment, CODE 0 jump table/startup, bounded PC-relative file-backed data, documented in-process Rez subset, Finder metadata, and MacBinary II.
- **Roadmap Boundaries**: Multi-segment architectures, general A5-relative global data, external library linking, and CFM-68K are not yet supported.
- **Historical makePAD Observations**: Application-specific runtime observations exist for Mac OS 8.1 and earlier systems; these reflect that specific fixture rather than general 68K toolchain support.

### 3. External Rust-to-Classic XCOFF Interop (Demonstrated Integration)
- Demonstrates consuming big-endian PowerPC XCOFF objects emitted by external pinned Rust nightly (`powerpc-apple-macos.json`).
- macMAKE performs native CFM/PEF linking, resource assembly, and MacBinary packaging.
- macMAKE does not bundle `rustc` or directly compile Rust source.

## Unsupported in v0.1.1

- **CFM-68K**: CFM shared libraries and applications on 68K are unsupported.
- **C++ Runtime Parity**: C++ support is preview-only; Itanium ABI runtime parity, exceptions, general RTTI, and `libstdc++` are not supported.
- **Full Classilla Clean Rebuild**: Classilla targets have been inventoried and individual targets built, but clean full-browser rebuilding is not supported.
- **Mac OS X / Mach-O**: Targets using Mach-O or dyld runtime are unsupported.
- **macOS / Windows Hosts**: Only Linux x86-64 is supported as a host platform.

## Online Compatibility Tracker

For complete OS-by-OS records, evidence manifests, logs, and historical observations, visit the [Online Compatibility Tracker](https://macmake.dev/compatibility/).
