# makePAD v0.1 — native 68K build record

## Artifact

- File: `makePAD-v0.1-macos8.1-68k-hle-mask.bin`
- Size: 18,560 bytes
- SHA-256: `097d8e54a505f4dd0d5a1969af2ae8a490b124986b0907bae84875dfd58842a6`
- Intended baseline: Classic Mac OS 8.1, Motorola 68K
- Format: MacBinary II containing a resource-based classic 68K application

## Build provenance

- makePAD application/configuration revision: `be0f26871f6ed26466c287d0d735078a51ec40db`
- macMAKE native 68K provider revision: `c55760a`, with resource-inspection follow-up `eabeaed`
- Compiler/toolchain: GNU GCC 12.2.0 and GNU Binutils 2.46.1, target `m68k-unknown-elf`
- Application sources compiled: six C translation units (`main`, `application`,
  `editor`, `documents`, `menus`, and `dialogs`)
- Runtime/link support: macMAKE-owned startup, Toolbox ABI bridges, and byte
  runtime objects; link completed without undefined symbols
- Retro68 and Metrowerks MSL archives: not used for this artifact
- Authorized local Universal Interfaces headers were compilation inputs and
  are not included in this archive

## Output checks

The build generated classic 68K `CODE` 0 and `CODE` 1 resources, a resource
fork, Finder information (`APPL` / `MPAD`), and MacBinary II packaging. The
independent structural inspection passed checks for the resource-based
executable, Finder metadata, `CODE` 0/`CODE` 1 structure, `SIZE` resource, and
absence of a CFM fragment.

Host-side structural validation does not establish runtime compatibility by
itself. Owner-observed runtime results are recorded separately in
`RUNTIME-RESULTS.md`.
