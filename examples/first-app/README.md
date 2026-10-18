# First application

This two-source C89 project builds a Classic PowerPC CFM application through
`macmake build . --target "Classic PPC C"`. It uses macMAKE's bundled XCOFF
PowerPC GCC provider and native semantic linker, plus user-supplied
CodeWarrior MSL archives and Universal Interfaces import stubs. macMAKE does
not include or redistribute Apple or Metrowerks materials.

The sample is pinned to the CodeWarrior 8 Universal Interfaces `CarbonLib`
stub (SHA-256
`5606a921cc9c870b1981fc1e68fee78784fd8b05c6c37fd0a4dc14009784c9c7`).
The Linux extraction used for validation has no resource-fork sidecar, so the
project manifest records its four `cfrg` fragment extents. For a different
`CarbonLib`, use its matching `cfrg` metadata and update `pef_fragments` in
`macmake.toml`.

Fetch the versioned minimal C/PowerPC SDK subset from the source identified in
the installed CLI's manifest. This is a separate, user-triggered fetch; the
macMAKE release archive does not contain Apple or Metrowerks SDK material.
Only fetch and use these historical files if you are authorized to do so:

```sh
macmake sdk fetch --minimal
macmake sdk add "$HOME/.local/share/macmake/macMAKELibs/Universal" \
  --id macos9-sdk
macmake sdk verify macos9-sdk
```

Copy the three required MSL archives into this project from the fetched
macMAKELibs root. The helper also accepts a conventional CodeWarrior install
root if you already have one. It verifies the exact MSL archive hashes used by
this sample, rejects symlinked source/destination files, and stages all three
before replacing the project copies:

```sh
./setup-user-msl.sh "$HOME/.local/share/macmake/macMAKELibs"
```

Pass a second path to place the same verified archives in another example's
`sdk/` directory.

The helper prints the copied files' SHA-256 hashes. The local `sdk/` directory
is ignored by Git and is never included in the macMAKE distribution. The
versioned SDK manifest records the fetch revision and hashes; those records do
not grant usage or redistribution rights. If your authorized MSL files do not
match these validated inputs, the helper stops without copying; do not rename
different archives to make the check pass. Review their provenance and adapt
the project and validation separately.

Build and inspect the project:

```sh
macmake doctor . --target "Classic PPC C" \
  --toolchain-root /path/to/macmake/toolchain
macmake build . --target "Classic PPC C" \
  --toolchain-root /path/to/macmake/toolchain
macmake inspect-artifact build/HelloPPC/ClassicPPCC/HelloPPC.pef \
  --resource-fork build/HelloPPC/ClassicPPCC/HelloPPC.rsrc \
  --finder-info build/HelloPPC/ClassicPPCC/.finf/HelloPPC.APPL \
  --creator HmPP --file-type APPL --json
```

The build creates a MacBinary II package (`HelloPPC.bin`), its PEF data fork,
resource fork, Finder metadata, and build evidence beneath
`build/HelloPPC/ClassicPPCC/`. The small program checks a value returned by a
second translation unit and returns through the MSL startup path. It opens no
window. Running the same project-specific build command again should report
the link as current and reuse the cached objects.

On Mac OS 9, unpack `HelloPPC.bin` with a MacBinary-aware utility, copy the
`HelloPPC` application to a writable folder, and launch it. It should return
to the Finder normally. This checks basic load/start/return behavior only; it
does not establish broad API compatibility or exact CodeWarrior parity.

## Additional examples

[`classic-rust-interop/`](../classic-rust-interop/README.md) is a separate,
reproducible Rust-to-Classic-PowerPC interop example: an external pinned
Rust compiler produces XCOFF, and the ordinary macMAKE build links,
resources, and packages it. The release does not include a Rust compiler
provider.

`hello-window-68k/` is an experimental native 68K application fixture. It is
not part of the supported PowerPC C profile; read its README and the M68K
toolchain limitations before using it. `rust-cli-client/` demonstrates a
host-side Rust program invoking macMAKE's CLI. Separate MacRust experiments
have built Rust XCOFF and linked and run Classic PPC applications through
CodeWarrior. See [`docs/language-support.md`](../../docs/language-support.md)
for the exact distinction between that research, the linked sample, and the
absence of a bundled Rust provider.

## Troubleshooting

- **SDK registration missing**: If `doctor` fails with an unrecognized SDK, run `macmake sdk add` pointing to your Universal Interfaces directory and verify with `macmake sdk verify macos9-sdk`.
- **MSL archive hash mismatch**: The sample strictly requires the validated MSL archive hashes. Run `./setup-user-msl.sh` against the root of `macMAKELibs` or an authorized CodeWarrior installation. Do not rename different archives.
- **Incremental rebuild**: To force a clean rebuild, run `macmake clean .` before invoking `macmake build`.

## Relevant CLI Help

- `macmake help quickstart`
- `macmake help manifest`
- `macmake help targets`
- `macmake help sdk`
- `macmake help build`
- `macmake help troubleshooting`

