# makePAD v0.1 — owner runtime results

Test date: 2026-10-16. The owner tested the same artifact in each listed
environment. These results describe makePAD v0.1 only; they do not establish
general OS or API compatibility for macMAKE or other applications.

Artifact: `makePAD-v0.1-macos8.1-68k-hle-mask.bin`

SHA-256: `097d8e54a505f4dd0d5a1969af2ae8a490b124986b0907bae84875dfd58842a6`

| Operating system | Architecture | Owner-observed result |
| --- | --- | --- |
| Mac OS 8.1 | 68K | Works fully, including opening a saved document directly from the Finder |
| Mac OS 8.0 (reported as “8”) | 68K | Works except direct opening of a saved document |
| System 7.6.1 | 68K | Works except direct opening of a saved document |
| System 7.6 | 68K | Works except direct opening of a saved document |
| System 7.5.5 | 68K | Works except direct opening of a saved document |
| System 7 (minor version unspecified) | 68K | Works fully |
| System 6.0.8 | 68K | The application “makePAD” has unexpectedly quit (1) |

The exact System 7 minor version and per-system emulator/hardware
configurations were not recorded. No cause is inferred for the System 6.0.8
quit. Finder document opening on the intermediate systems remains unresolved;
manual Open from within makePAD worked where reported. The owner operates the
Macintosh test environments.
