# Native Motorola 68K compatibility and roadmap

## What the current implementation means

macMAKE has an independent, experimental native M68000 application path. It
uses GNU GCC 12.2.0 and Binutils 2.46.1 to compile C89 into M68000 code, then
macMAKE constructs the classic segmented application's CODE resources,
Finder metadata, and MacBinary II package. It does not use Retro68.

The exact current manifest profile is:

```toml
architecture = "m68k"
runtime = "classic-segmented"
runtime_profile = "macmake-classic-m68k-c-v1"
executable = "code-resources"
compiler_target = "classic-68k-segmented-app-c-v1"
```

It is a bounded application profile, not a claim that every application or
operating-system version works. The current implementation emits one
near-model CODE 1 segment and a CODE 0 startup/jump-table resource. The
CODE 0 A5 allocation reserves Toolbox/QuickDraw space; current application
globals are file-backed in CODE 1 and addressed PC-relative. General
A5-relative global layout, multi-segment intersegment relocations, external
library linking, and CFM-68K are not implemented.

## Application observations

These runtime observations refer to owner-tested **makePAD 0.1 development
artifacts**, not to every program macMAKE can build and not to the RC5 binary
having run inside Mac OS. `makePAD` was the same basic text-editor application
across the listed tests.

| System | CPU/profile tested | makePAD observation | General status |
|---|---|---|---|
| System 6.0.8 | 68K | Unexpected quit with error 1 | No compatibility established |
| System 7, minor version unspecified | 68K | Owner reported full basic operation | One application/version-unspecified observation |
| System 7.5.5 | 68K | Basic editor worked; opening a saved document directly from Finder did not | One application observation with limitation |
| System 7.6 / 7.6.1 | 68K | Basic editor worked; direct saved-document open did not | One application observation with limitation |
| Mac OS 8.0 | 68K | Basic editor worked; direct saved-document open did not | One application observation with limitation |
| Mac OS 8.1 | 68K | Owner confirmed makePAD worked, including direct open of saved files | One application observation |
| Mac OS 8.1 | PowerPC | makePAD worked | Separate PPC application observation |
| Mac OS 8.5 / 8.6 | PowerPC | makePAD worked without source changes | Separate PPC application observations |
| Mac OS 9 | PowerPC | makePAD editing/save/open behavior confirmed; broader application evidence includes MacSurf | Separate PPC observations; no 68K claim |

The native M68000 compiler profile is architecture-specific; PPC runtime
results say nothing about 68K execution, and vice versa. OS 9 PPC/MacSurf
history is not evidence that a new RC5 artifact has been run on OS 9.

## OS-family compatibility summary

| OS family | PowerPC Classic applications | Native segmented 68K applications | CFM-68K |
|---|---|---|---|
| System 6 | Not part of current PPC observations | Not established; makePAD failed on 6.0.8 | Unsupported |
| System 7 | makePAD tested on some later versions; see per-version results above | makePAD observations exist for 7.0 (minor unspecified), 7.5.5, 7.6, and 7.6.1 with Finder-open limitations on listed versions | Unsupported |
| Mac OS 8 | PPC makePAD 8.1 tested; other PPC versions not inferred | makePAD observed on 8.0 and 8.1; 8.0 has a direct-open limitation | Unsupported |
| Mac OS 9 | PPC makePAD and historical MacSurf runtime evidence exist | No native 68K result asserted here | Unsupported |

“Build verified” means a target artifact was built and structurally checked.
“Application observed” above means the owner used the named makePAD artifact
on the named guest OS. Neither is universal API coverage or a promise that
all applications run there.

## Engineering roadmap

1. **Stabilize the current single-segment profile.** Keep ABI veneers,
   startup, resource structure, and artifact validation independently
   tested. Preserve the M68000 instruction baseline.
2. **General A5-world data model.** Define the application global-data
   layout and relocation model, including initialized/uninitialized globals,
   A5-relative references, QuickDraw globals, and ownership of A5 across
   Toolbox calls. Validate against classic startup documentation and real OS
   launches before advertising it.
3. **Multiple code segments.** Add CODE segment table and jump-table
   construction, `LoadSeg` behavior, cross-segment call stubs, segment
   lifecycle, and relocation validation. Avoid treating an INIT movable-code
   resource as an application segment.
4. **External libraries.** Define how static library members, system
   imports, shared fragments, and library initialization participate in the
   classic segment model. Add deterministic member selection and link-order
   tests before allowing general application libraries.
5. **Broader resources and OS profiles.** Version resource/Rez behavior and
   test the required Finder, `SIZE`, `CODE`, and application resources on
   each OS family. Keep application observations tied to exact fixtures.
6. **CFM-68K as a separate target.** Research the CFM-68K ABI, Code Fragment
   Manager loader, transition vectors/import libraries, mixed-mode glue,
   fragment initialization, and PEF/CFM structure. Design a separate runtime
   profile and executable format; do not overload `classic-segmented`.
7. **System 6 and earlier.** After System 7/8 behavior is stable, reduce
   startup/API assumptions and validate the CPU baseline and memory limits on
   suitable hardware/emulation. A successful System 7 build cannot establish
   System 6 compatibility.

No milestone in this roadmap is implemented merely because it appears here.
Update the compatibility evidence only after the corresponding artifact and
runtime test exist.
