# CodeWarrior XML import and Classilla evidence

`macmake import-cw-xml` reads a CodeWarrior XML project export and writes a
native `macmake.toml` plus a `.cw-import.json` review record. Importing is an
experimental translation step: the sidecar is part of the result and must be
reviewed before building. The importer does not read proprietary binary
`.mcp` files.

## Import and build workflow

1. In CodeWarrior, export the intended project or target in XML format. Keep
   the XML next to the project sources and use the IDE's XML project export,
   not a source/resource XML file. Include the target's file membership,
   access paths, libraries, and link order in the export.
2. Identify the exact target name from the XML export. Provide the authorized
   CodeWarrior installation root so CodeWarrior-root paths can be resolved.
3. Write the generated files beside the XML. The selected-target importer
   rejects an output directory different from the XML directory because that
   would change project-relative path meaning.

```sh
macmake import-cw-xml Project-Export.xml \
  --target "Target Name" \
  --codewarrior-root "$HOME/authorized/CodeWarrior Pro 8" \
  --output ./macmake-imported.toml
macmake inspect ./macmake-imported.toml
```

For the retained Classilla export, the actual file was `apprunner.xml`, whose
CodeWarrior export metadata identifies export version 1.0.1 and IDE version
4.2. The reviewed imported result is `macmake-apprunner-reviewed2.toml` with
its sibling `.cw-import.json` record. The `apprunner` target contains explicit
source and resource membership plus ordered `NSRuntime`, `NSPR20`, `NSStdLib`,
JavaScript, XPCOM, and interface-stub link inputs. This is a real Classilla
project import, not a synthetic example.

To repeat the import against an authorized local Classilla checkout, point the
command at that checkout's retained XML export and its matching CodeWarrior
installation. The output stays beside the XML so its relative paths retain
their meaning; use a new output name to preserve an existing reviewed import:

```sh
CLASSILLA_ROOT=/path/to/authorized/classilla
CW_XML="$CLASSILLA_ROOT/mozilla/xpfe/bootstrap/macbuild/apprunner.xml"
CW_ROOT="/path/to/authorized/CodeWarrior Pro 8"
macmake import-cw-xml "$CW_XML" \
  --target apprunner \
  --codewarrior-root "$CW_ROOT" \
  --output "$(dirname "$CW_XML")/macmake-apprunner-review.toml"
macmake inspect "$(dirname "$CW_XML")/macmake-apprunner-review.toml"
```

The exact local source checkout and CodeWarrior root are user-supplied. The
retained historical `macmake-apprunner-reviewed2.toml` and sidecar remain the
reference output for comparing a fresh import; do not overwrite them during a
reproduction.

Review both files before a build:

```sh
macmake help import-cw-xml
macmake help manifest
macmake inspect ./macmake-imported.toml
python3 -m json.tool ./macmake-imported.toml.cw-import.json | less
```

Check the sidecar's `unsupported_settings`, `unknown_settings`,
`ignored_settings`, and `assumptions`. Do not treat a generated manifest as a
complete translation when any unreviewed entries remain. Verify every source,
resource, and archive path against the local project tree. Preserve source
membership and library order; do not replace them with broad directory scans
or an unordered list.

Register an authorized SDK and verify the required capabilities. For a
project rooted at `macmake.toml`, resolve each missing header or import with
the CLI's exact diagnostics; update the manifest's access paths and logical
SDK declarations rather than embedding machine-specific absolute paths.

```sh
macmake sdk list
macmake sdk verify macos9-sdk
macmake doctor ./macmake-imported.toml --target "Target Name"
macmake build ./macmake-imported.toml --target "Target Name"
```

After a successful build, inspect the emitted PEF, resource fork, Finder
metadata, and MacBinary using their actual output paths:

```sh
macmake inspect-artifact path/to/Target.pef \
  --resource-fork path/to/Target.rsrc \
  --finder-info path/to/.finf/Target.APPL \
  --creator HmPP --file-type APPL --json
```

Use `macmake help import-cw-xml`, `macmake help access-paths`,
`macmake help libraries`, and `macmake help troubleshooting` for the installed
binary's version-specific syntax. An import exit code indicating a partial
translation does not mean no files were written: inspect the manifest and
sidecar, correct or remove unsupported target settings, then run `inspect`,
`doctor`, and `build` independently.

## XML capability matrix

| Feature | State | Boundary |
|---|---|---|
| XML project and target discovery/order | Supported | Target names and declared target order are recorded; target selection is explicit. |
| Explicit C/C++/assembly membership | Supported | Recognized source entries are kept in declaration order. Headers are compile inputs, not link inputs. |
| Rez/precompiled resources | Supported | `.r`, `.rez`, and recognized resource entries are represented; build still validates the actual tool/input. |
| Project archives, objects, and CFM library entries | Supported | Recognized inputs and weak/merge flags are preserved where the canonical model supports them. |
| `LINKORDER` | Supported | Recognized file references are translated in declared order; unresolved references remain evidence. |
| User/system access paths | Partial | Supported path anchors and classic separators are translated. Unsupported roots/path semantics are reported in the sidecar. |
| Common Classic PowerPC compiler/runtime settings | Partial | An explicit allowlist maps selected settings. Unknown settings stay visible; values are not assumed to be equivalent. |
| Prefixes, defines, API/import hints, Finder and memory metadata | Partial | Mapped fields use canonical target values; inspect the generated manifest and verify dependencies. |
| Unknown settings and extra XML nodes | Preserved for review | Raw XML-shaped evidence is retained; preservation does not implement the setting. |
| Design-level settings and `SEGMENTLIST` | Unsupported | Raw evidence is kept, but the current target model does not represent these configurations. |
| Framework/plugin behavior, arbitrary compiler options, nested project semantics | Unsupported or partial | No general translation guarantee; the sidecar identifies unresolved elements. |
| Non-PowerPC target/linker, Mac OS X target, binary `.mcp` input | Unsupported | Import fails or the binary project is not accepted. |

## Classilla import and build evidence

The retained Classilla source checkout identifies revision
`d10153e65267aee9c1f82e431da9a0ff0821e2bb`. Its CodeWarrior XML corpus
includes a real `apprunner.xml` export and retained selected-target imports,
including the reviewed `apprunner` manifest and sidecar. The historical
2026-10-10 target census records 131 configured entries: 129 native targets
and two non-native operations. It contains successful macMAKE development
build evidence for 128 native targets; this is per-target development
evidence, not qualification of the v0.1.1 release archive.

The retained exception is `NSStdLib.shlb`, whose selected MSL sources
`unix.c` and `unix.mac.c` were not available in the authorized local source
set. `Stubs` is a clean-only operation, and `MRJPlugin.jar` is Java. A
separate package assembly validated 92 PEFs and 87 component registry
references, but its evidence says `clean_build_status: NOT_PERFORMED`. The
assembled browser package was not run on Mac OS 9 in that validation.

These stages remain separate: XML import, individual target builds, package
assembly, and target-OS execution. The evidence does not establish a clean
complete Classilla rebuild from this release candidate or a successful
Classilla runtime. The original source, local SDKs, and generated package are
not part of the macMAKE distribution. See
[`classilla-evidence-summary.md`](classilla-evidence-summary.md) and the
[`C++ compatibility matrix`](cpp-compatibility.md).
