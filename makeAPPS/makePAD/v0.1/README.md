# makePAD v0.1 artifact record

This folder archives the native 68K makePAD application and its test evidence.
It does not contain the makePAD source project, SDK files, or a macMAKE
distribution. The final artifact was built with the macMAKE native 68K
development toolchain.

- `WIP/` contains superseded development candidates and their build records.
- `FINAL/` contains the owner-tested MacBinary and its build/runtime evidence.

The single `FINAL` artifact was tested on several systems. The results are
specific to this application and do not establish general operating-system or
API compatibility. See `FINAL/RUNTIME-RESULTS.md` for the owner-reported
results and limitations.

Finder double-click opening is a separate application behavior from File >
Open. The recurring blank-document failure, its code-level fix, and the
required acceptance check are recorded in
[`WIP/2026-10-18-finder-direct-open/README.md`](WIP/2026-10-18-finder-direct-open/README.md).
