# Getting Started with macMAKE

macMAKE is a Linux-native toolchain for building Classic Macintosh applications. This guide walks through installing macMAKE, configuring SDK inputs, and building the included examples.

## Requirements

- **Operating System**: Linux x86-64 (tested and qualified on Ubuntu 24.04 LTS).
- **macMAKE Release**: `macmake-v0.1.1-linux-x86_64.tar.xz` (SHA-256 `d83c173d4184a67738df3bad7d0cadb2b6eab45fa2cc06df89f9f7eff4bd0656`).
- **Dependencies**: `curl`, `sha256sum`, `tar`, `xz-utils`, `git`, `python3`.
- **Historical SDK Material**: Apple Universal Interfaces and Metrowerks MSL archives are proprietary third-party files. You must provide files you are authorized to use.

## Installation

### Method 1: Automated user-level installer

Install macMAKE under `~/.local` with the official script:

```sh
curl -fsSL https://macmake.dev/install.sh | bash
```

To opt out of post-install completion telemetry:

```sh
curl -fsSL https://macmake.dev/install.sh | bash -s -- --no-analytics
```

To automatically fetch the versioned minimal SDK subset during installation (requires authorization for Apple Universal Interfaces):

```sh
curl -fsSL https://macmake.dev/install.sh | bash -s -- --with-sdk
```

Ensure `~/.local/bin` is in your `$PATH`:

```sh
export PATH="$HOME/.local/bin:$PATH"
```

### Method 2: Manual archive extraction

Download `macmake-v0.1.1-linux-x86_64.tar.xz` from [GitHub Releases](https://github.com/mplsllc/macMAKE/releases/tag/v0.1.1), verify its checksum, and extract to your preferred location:

```sh
sha256sum -c macmake-v0.1.1-linux-x86_64.tar.xz.sha256
tar -xf macmake-v0.1.1-linux-x86_64.tar.xz -C "$HOME/.local"
```

## Discover the CLI

The installed executable includes its complete manual and operates fully offline:

```sh
macmake --version
macmake help
macmake help quickstart
macmake help targets
macmake help manifest
macmake schema manifest --json
```

## First Application: Classic PowerPC C

The supported release path builds Classic Mac OS PowerPC CFM/PEF applications.

### 1. Set up the minimal SDK

If you did not pass `--with-sdk` during installation, fetch the pinned Universal Interfaces subset from the authorized repository:

```sh
macmake sdk fetch --minimal
macmake sdk add "$HOME/.local/share/macmake/macMAKELibs/Universal" --id macos9-sdk
macmake sdk verify macos9-sdk
```

### 2. Copy the example and supply MSL archives

Copy the example project to a writable workspace:

```sh
cp -r "$HOME/.local/share/macmake/current/examples/first-app" "$HOME/HelloPPC"
cd "$HOME/HelloPPC"
```

Run the helper to verify and copy the three required MSL archives (`MSL_C_Carbon.Lib`, `MSL_Runtime_PPC_D.Lib`, and `MSL_Extras_Carbon.Lib`) from your fetched SDK or CodeWarrior installation:

```sh
./setup-user-msl.sh "$HOME/.local/share/macmake/macMAKELibs"
```

### 3. Check and build

Validate and build the project:

```sh
macmake inspect .
macmake doctor . --target "Classic PPC C"
macmake build . --target "Classic PPC C"
```

The build emits `build/HelloPPC/ClassicPPCC/`:
- `HelloPPC.bin`: MacBinary II container ready for transfer.
- `HelloPPC.pef`: CFM/PEF binary data fork.
- `HelloPPC.rsrc`: Macintosh resource fork.
- `.finf/HelloPPC.APPL`: Finder metadata (`HmPP` / `APPL`).
- Build evidence and manifests.

### 4. Inspect the output

Inspect the generated Macintosh artifacts:

```sh
macmake inspect-artifact build/HelloPPC/ClassicPPCC/HelloPPC.pef \
  --resource-fork build/HelloPPC/ClassicPPCC/HelloPPC.rsrc \
  --finder-info build/HelloPPC/ClassicPPCC/.finf/HelloPPC.APPL \
  --creator HmPP --file-type APPL --json
```

## Experimental: Native Motorola 68000 Application

macMAKE v0.1.1 includes an experimental independent M68000 backend without Retro68.

From `examples/first-app/hello-window-68k`:

```sh
cd "$HOME/HelloPPC/hello-window-68k"
macmake inspect .
macmake doctor . --target "Classic 68K Mac OS 8.1"
macmake build . --target "Classic 68K Mac OS 8.1"
```

The build produces `build/HelloWindow68K.bin` containing CODE 0 (jump table/startup), CODE 1 (single near-model segment), Finder metadata (`M68K` / `APPL`), and Toolbox veneers.

## External: Rust-to-Classic XCOFF Interop

`examples/classic-rust-interop` demonstrates linking a function compiled with an external pinned Rust nightly (`powerpc-apple-macos.json`) into a Classic PowerPC CFM/PEF application:

```sh
cd "$HOME/.local/share/macmake/current/examples/classic-rust-interop"
./build-rust.sh
macmake doctor . --target "Classic PPC Rust Interop"
macmake build . --target "Classic PPC Rust Interop"
```

Or run the automated test:

```sh
python3 test-rust-interop.py --macmake macmake
```

## Running Applications in QEMU (`macmake run`)

macMAKE v0.1.1 includes optional profile-driven QEMU execution for Mac OS 9.2.2:

```sh
macmake run --profile qemu-macos9 --artifact build/HelloPPC/ClassicPPCC/HelloPPC.bin
```

The runner:
- Creates a safe copy-on-write overlay (`qcow2`) without mutating your base disk.
- Launches QEMU (`mac99` / G4).
- Validates P6 PPM screenshots at boot and application checkpoints.
- Emits structured execution reports in run-report schema v2.

*Note: While awaiting operator input, the runner prints repeated prompt lines on each 250ms timeout; this is a known nonblocking log-noise defect.*

## Telemetry Opt-Out

macMAKE collects no ongoing CLI telemetry. To disable the single post-install completion ping:
- Pass `--no-analytics` to `install.sh`.
- Or set `export MACMAKE_DISABLE_ANALYTICS=1` in your environment.
