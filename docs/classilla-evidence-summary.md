# Classilla build evidence summary

Classilla is retained as a large CodeWarrior-project research corpus. The
latest retained 2026-10-10 graph census reports 131 configured entries: 129
native targets and two non-native operations. 128 native targets have
successful macMAKE build evidence. One `NSStdLib.shlb` target remains a
retained historical input because its selected MSL implementation sources
`unix.c` and `unix.mac.c` were not present in the local authorized source set.

A separate package assembly validated 92 PEF files and 87 component registry
references. Its provenance explicitly says that a clean graph rebuild was
not performed, and the assembled browser package was not run on Mac OS 9 in
that validation. Some earlier macMAKE development builds of Classilla are
documented separately; they must not be conflated with a completed clean
build from this release candidate.

The retained work used CodeWarrior XML exports to discover target settings,
explicit source membership, access paths, and ordered libraries, then
reviewed generated manifests and applied target-specific adjustments. The
binary `.mcp` format is not imported. The XML importer is experimental; each
partial import and each target build must be checked independently.

No Classilla source, proprietary SDK, compiler binary, or package is part of
the macMAKE release. This evidence demonstrates neither general C++ parity
nor that the current candidate can rebuild or run the browser end to end.
