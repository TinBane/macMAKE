# Optional QEMU Macintosh runtime smoke test

`macmake run` supports one interactive profile: QEMU's `mac99` PowerPC
machine with a G4 CPU and a user-owned Mac OS 9.2.2 disk image. It does not
bundle a ROM, operating-system image, or emulator.

The command creates a new qcow2 copy-on-write overlay and attaches that
overlay to QEMU. QEMU writes to the overlay; the configured base disk is
SHA-256 hashed before and after the run. The overlay and evidence are retained
under `$XDG_STATE_HOME/macmake/runs/` or `~/.local/state/macmake/runs/`.

## Profile

Create a JSON file with paths to an authorized disk image and an application
already staged inside that image using a Mac-aware transfer method:

```json
{
  "schema_version": 1,
  "emulator": "qemu-system-ppc",
  "qemu_img": "qemu-img",
  "machine": "mac99",
  "cpu": "g4",
  "memory_mib": 1024,
  "display": "gtk",
  "guest_os": "Mac OS 9.2.2",
  "base_disk": "$HOME/MacOS-9.2.2.qcow2",
  "application": {
    "name": "HelloPPC",
    "guest_path": "Macintosh HD:Applications:HelloPPC"
  }
}
```

The initial profile accepts only `mac99`, `g4`, `Mac OS 9.2.2`, and a GTK or
SDL display. The guest path and OS identity are labels for the operator; the
command does not inspect the HFS volume or infer the guest's installed OS.
`--artifact` records and hashes a host-side MacBinary file but does not copy
it into the disk image.

## Run and checkpoints

```sh
macmake run ./qemu-macos-9.2.2.json \
  --artifact ./build/HelloPPC/ClassicPPCC/HelloPPC.bin \
  --build-evidence ./build/HelloPPC/ClassicPPCC/HelloPPC.build-evidence.json
```

The QEMU window opens. Boot Finder and check About This Computer to identify
the guest OS. Before answering yes to the boot checkpoint, close About This
Computer and any other dialog so the boot capture shows Finder. Launch the
configured application manually. Before answering yes to the launch
checkpoint, bring its main window to the front and dismiss unrelated Finder or
About This Computer dialogs. The application-state capture is taken
immediately after that answer. The CLI asks separately whether the captured
application state is correct and whether the application exited normally.
These are operator-confirmed observations, not automated guest assertions.

QEMU 8.2.2 writes binary P6 PPM data for QMP `screendump`; macMAKE saves it as
`guest_boot.ppm` or `application_state.ppm`, validates the PPM header and pixel
length, and records the actual format, dimensions, SHA-256, path, and named
checkpoint in `run.json` schema 2. A failed or truncated capture is a test
failure. If the two captures are byte-identical, both are retained and labeled,
but the run cannot claim runtime-state confirmation from duplicate visual
evidence. Separate screenshots supplement the operator's checkpoint answers;
they do not independently prove that an application works.

The host artifact is recorded and hashed but is not copied into the guest disk.
When `--build-evidence` is supplied, the CLI verifies that the evidence
record's MacBinary SHA-256 matches before setting `artifact_constructed` to
true. If no matching record is supplied, construction is marked unverified;
the CLI never infers a build from file existence alone.

Use `--timeout SECONDS` to bound the interactive session or `--json` to print
the final structured result. Each run directory contains `run.json`,
`qemu.log`, `serial.log`, the qcow2 overlay, and validated PPM screenshots
when captured. The JSON keeps emulator startup, guest boot, OS confirmation,
application launch, visible state, normal exit, timeout, and QEMU exit status
separate. Screenshot records are objects with `checkpoint`, `path`, `format`,
`sha256`, `width`, `height`, and `distinct_from_prior_checkpoint` fields.
Exit code 0 means the guest OS, application launch, and visible state were
confirmed; code 1 means a checkpoint failed, was not confirmed, or timed out.

To keep the test reproducible, retain the profile, base-disk hash, run record,
screenshots, and host artifact hash together. Do not share system images or
ROM files unless their redistribution is authorized.

## Limits

This is an interactive QEMU smoke-test workflow for the single named guest
profile. It does not inject a host artifact into a Macintosh disk, automate
Finder, verify application output independently, or prove physical Quadra
hardware behavior. Basilisk II, SheepShaver, other QEMU machines, other OS
versions, headless runs, and automatic test-result channels are unsupported
by this command. Structural artifact inspection remains a separate host-side
check.
