# makeAPPS artifact archive

This directory keeps Macintosh application build artifacts organized by
application and application version. Application source remains in its own
project repository.

For each application version:

- `WIP/` contains current development builds that still need owner testing.
- `FINAL/` contains artifacts the owner has tested and accepted.

Include the target OS and architecture in each artifact filename. Keep a
checksum and a short build/runtime record with each candidate. Do not put SDK
or runtime source material in this archive.
