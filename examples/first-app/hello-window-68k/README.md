# HelloWindow68K

A self-contained C89 source example demonstrating macMAKE's experimental native Motorola 68000 classic segmented application backend. This backend uses the bundled GNU GCC 12.2.0 and GNU Binutils 2.46.1 `m68k-unknown-elf` toolchain and macMAKE-owned classic application packaging without invoking Retro68.

The surrounding `examples/first-app/LICENSE.txt` applies to the source and project configuration in this directory; keep that license with copies of these example files.

## Prerequisites

- Linux x86-64 and installed macMAKE v0.1.1.
- The bundled M68000 toolchain located in the macMAKE distribution beneath `toolchain/m68k`.
- No Apple or Metrowerks SDK is required: the example declares its own minimal Toolbox veneer signatures directly in C89.

## Exact Commands

Set the toolchain root (adjust to your installation prefix if not using default `~/.local`) and build:

```sh
export MACMAKE_M68K_TOOLCHAIN_ROOT="$HOME/.local/share/macmake/current/toolchain/m68k"
macmake inspect .
macmake doctor . --target "Classic 68K Mac OS 8.1"
macmake build . --target "Classic 68K Mac OS 8.1"
```

Inspect the generated Macintosh binary artifacts:

```sh
macmake inspect-artifact build/HelloWindow68K.data \
  --resource-fork build/HelloWindow68K.rsrc \
  --finder-info build/HelloWindow68K.finderinfo \
  --creator M68K --file-type APPL --json
```

## Expected Output

The build generates:
- `build/HelloWindow68K.bin`: MacBinary II container ready for transfer to vintage hardware or emulator.
- `build/HelloWindow68K.data`: Flat application data fork (CODE 1 segment code payload).
- `build/HelloWindow68K.rsrc`: Resource fork containing:
  - `CODE 0`: Jump table header and dispatch entries.
  - `CODE 1`: Application entry point and near-model code.
- `build/HelloWindow68K.finderinfo`: Finder metadata establishing type `APPL` and creator `M68K`.
- `build/build-evidence.json`: Build provenance and hash manifest.

When launched on Classic Mac OS (System 7 through Mac OS 8.1), the application opens a standard window titled "macMAKE 68K", displays a centered greeting string, processes update and drag events, and exits when clicked.

## Troubleshooting

- **Toolchain not found**: If `macmake doctor` reports `m68k-unknown-elf-gcc` is missing, ensure `MACMAKE_M68K_TOOLCHAIN_ROOT` points to the `toolchain/m68k` directory in your macMAKE install, or pass `--toolchain-root /path/to/toolchain/m68k`.
- **Target constraint errors**: The experimental 68K backend requires `backend = "macmake-classic"`, `compiler_target = "classic-68k-segmented-app-c-v1"`, and `runtime_profile = "macmake-classic-m68k-c-v1"`. Code and file-backed data must remain within the 32 KB near-model addressing limit.
- **Relocations**: Multi-segment code and general A5-relative global data are unsupported in v0.1.1. Keep globals static/PC-relative or stack-allocated.

## Relevant CLI Help

- `macmake help targets`
- `macmake help toolchain`
- `macmake help manifest`
- `macmake help output`
- `macmake help troubleshooting`
