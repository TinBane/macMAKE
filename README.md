**This project is developed with the assistance of an LLM**

# macMAKE

<p align="center">
  <img src="img/logo.png" alt="macMAKE">
</p>

**macMAKE v0.1.0 is a Linux-native toolchain for building Classic PowerPC Macintosh applications.** Its supported release path targets Mac OS 9 CFM/PEF applications, primarily written in C.

It grew out of a simple problem: compiling Classic Mac software with a modern compiler is possible, but large historical Macintosh applications were built around much more than a compiler.

They depended on CodeWarrior project semantics, the Classic PowerPC ABI, CFM linking, PEF binaries, resource forks, historical runtime behavior, target membership, access paths, library ordering, and numerous assumptions that were normally invisible because CodeWarrior handled them.

macMAKE attempts to reproduce that environment on a modern host.

It is not a CodeWarrior emulator and it is not a frontend for Retro68. The goal is to understand what a CodeWarrior-era project means and reproduce the relevant build behavior directly.

> Retro68 asks: **How can modern GCC produce a Classic Mac program?**
>
> macMAKE asks: **What did CodeWarrior mean when it built this Classic Mac project, and how can we reproduce that behavior from Linux?**
<p align="center"><strong>Support development</strong></p>
<p align="center">
  <a href="https://ko-fi.com/macsurf" target="_blank"><img src="https://img.shields.io/badge/Ko--fi-Support-FF5E5B?style=for-the-badge&logo=kofi&logoColor=white" alt="Support on Ko-fi" height="40"></a>
  &nbsp;
  <a href="https://www.patreon.com/cw/MacSurf" target="_blank"><img src="https://img.shields.io/badge/Patreon-Support-FF424D?style=for-the-badge&logo=patreon&logoColor=white" alt="Support on Patreon" height="40"></a>
  &nbsp;
  <a href="https://github.com/sponsors/mplsllc" target="_blank"><img src="https://img.shields.io/badge/GitHub-Sponsor-DB61A2?style=for-the-badge&logo=githubsponsors&logoColor=white" alt="Sponsor on GitHub" height="40"></a>
</p>

<p align="center"><strong>Follow along</strong></p>
<p align="center">
  <a href="https://discord.gg/mrwZK8zHr2" target="_blank"><img src="https://img.shields.io/badge/Discord-Join-5865F2?style=for-the-badge&logo=discord&logoColor=white" alt="Join our Discord" height="40"></a>
  &nbsp;
  <a href="https://bsky.app/profile/macsurfos9.bsky.social" target="_blank"><img src="https://img.shields.io/badge/Bluesky-Follow-0285FF?style=for-the-badge&logo=bluesky&logoColor=white" alt="Follow on Bluesky" height="40"></a>
</p>

<p align="center"><strong>Thanks to our supporters:</strong><br>Ko-Fi: <strong>Chris Marks, Rogue, Turuun, kilgeist</strong><br>Patreon: <strong>Mack Chamberlain, Lucas, Joseph Mulvaney, Shlooom</strong></p>

---
## Why macMAKE exists

Classic Mac development currently has two especially important reference points.

**Metrowerks CodeWarrior** remains the historical standard. It provided an unusually complete Macintosh development environment and produced much of the software people still run on Classic Mac OS today. CodeWarrior 8 is an important behavioral reference for macMAKE: when ABI behavior, project semantics, object formats, libraries, or linker behavior are ambiguous, the question is often simply, "What did CodeWarrior do?"

**Retro68**, created by Wolfgang Thaller, demonstrated that modern GCC could successfully target both 68K and PowerPC Macintosh systems and brought modern cross-development techniques to machines that predate them by decades. It has been important prior art for macMAKE and was used during macMAKE's early development.

macMAKE approaches the problem from a different direction.

Rather than adapting historical applications to a new runtime and build model, macMAKE increasingly attempts to preserve the assumptions those applications originally made.

That distinction becomes important with large applications.

A small Toolbox program can exercise only a narrow portion of the historical development environment. A browser or other substantial CodeWarrior project can expose differences in structure alignment, calling conventions, runtime behavior, CFM imports, transition vectors, exception handling, library archives, relocation formats, and project dependency semantics.

macMAKE treats those differences as toolchain compatibility problems rather than application bugs.

## What macMAKE does

macMAKE is being developed toward an end-to-end Classic PowerPC build environment. The v0.1.0 product is a narrower, measured release: Linux x86-64 host to Classic Mac OS 9 PowerPC CFM/PEF applications, primarily C.

Current work includes support for areas such as:

- CodeWarrior-style project and target semantics
- Large dependency graphs and workspaces
- Classic PowerPC ABI compatibility
- Historical Macintosh structure alignment
- CFM linking
- PEF generation
- CodeWarrior/MWOB library handling
- resource processing
- Classic Macintosh packaging
- compatibility with historical Macintosh libraries
- modern automated builds and testing from Linux

The project is being developed against real historical software rather than only synthetic examples. MacSurf has served as a large application target, while Classilla is being used to expose deeper CodeWarrior C++ runtime, linker, and library compatibility requirements.

Passing a compiler is not considered sufficient evidence of compatibility. Where possible, macMAKE uses small fixtures, binary inspection, comparison with historical CodeWarrior output, and runtime testing under Classic Mac OS to establish behavior.

## Development philosophy

macMAKE does not attempt to "modernize away" Classic Mac OS.

The target is still Classic Mac OS, with its own ABI, executable formats, runtime conventions, Toolbox APIs, resources, and limitations.

The modernization happens on the development side.

The long-term objective is that a developer should be able to work from a modern Linux system using modern source control, editors, storage, automation, and hardware while producing applications that behave like proper Classic Macintosh software.

In other words:

**modern workstation, historical target.**

## Current status

macMAKE v0.1.0 is the initial public Linux x86-64 release. It supports a C-focused workflow for building Classic Mac OS 9 PowerPC CFM/PEF applications. Earlier PowerPC versions of System 7 and Mac OS 8 have not yet been verified. Native 68K application generation and Mac OS X targets are unsupported in v0.1. The project has historical Mac OS 9.2.2 MacSurf runtime evidence from a development build; the exact public v0.1.0 binary has not yet reproduced that runtime result. This is not a complete CodeWarrior replacement; broad C++ parity is outside this release.

See the [OS-by-OS compatibility tracker](https://macmake.dev/compatibility/) for the evidence level and release identity behind each result.

Start at [macmake.dev](https://macmake.dev), follow the [installation guide](https://macmake.dev/install.html), or read [Getting Started](https://macmake.dev/getting-started.html). The packaged first-app example requires authorized Apple Universal Interfaces and Metrowerks MSL material supplied by the user; these proprietary SDK files are not included.

## Source availability

MPLS LLC owns the original macMAKE implementation. The macMAKE core is **proprietary and closed-source software**; the public binary license grants the stated development-use rights but does not grant public redistribution of the proprietary executable.

This repository is the public home of the project, documentation, examples, issue tracking, and binary releases. It does **not** contain the proprietary macMAKE implementation.

macMAKE makes use of existing open-source software where appropriate. Source code and modifications that must be made available under the licenses of redistributed components are published separately in the [`macmake-gpl`](https://github.com/mplsllc/macmake-gpl) repository.

The presence of GPL-licensed components in the distributed toolchain does not mean that the proprietary macMAKE components are themselves released under the GPL.

See [docs/licensing.md](docs/licensing.md) for the v0.1.0 component boundaries and corresponding-source identity. The proprietary binary license applies only to the macMAKE executable and identified proprietary files; GCC, Binutils, runtime components, examples, and Rust dependencies retain their own licenses.

## Historical SDKs and libraries

macMAKE does not intend to redistribute proprietary Apple or Metrowerks development material without permission.

Some compatibility and historical-development workflows may require users to provide files from software they already possess, such as CodeWarrior libraries or Macintosh interfaces.

Where macMAKE can provide independently redistributable replacements or metadata, those can be distributed separately.

The v0.1 first-build guide explains SDK registration and user-supplied MSL setup in [docs/getting-started.md](docs/getting-started.md).

## Prior art and acknowledgements

macMAKE would not exist without the work that came before it.

**Metrowerks CodeWarrior** is the primary historical reference for the environment macMAKE is attempting to understand and reproduce. Its compiler, project system, Macintosh libraries, linker, debugger, PowerPlant framework, and overall development environment defined an important era of Macintosh software development.

**Retro68**, by Wolfgang Thaller, demonstrated that GCC-based modern cross-compilation for vintage Macintosh systems is practical and provided important tooling, research, and prior art for both 68K and PowerPC Macintosh development. macMAKE began with Retro68 as part of its development path before progressively replacing pieces where stricter CodeWarrior compatibility was required.

Apple's **Macintosh Programmer's Workshop**, Universal Interfaces, the Classic Macintosh runtime and executable-format documentation, and the work of developers who preserved and documented these systems remain essential references.

The Classilla build system and the work of **Cameron Kaiser** are also important practical references for understanding the challenges involved in building very large CodeWarrior-era Macintosh applications.

macMAKE builds on decades of Macintosh development knowledge. It should not be confused with having invented the formats, APIs, ABIs, or techniques it implements.

## Releases

Download the [macMAKE v0.1.0 Linux x86-64 release](https://github.com/mplsllc/macMAKE/releases/tag/v0.1.0). Its release page includes the archive, SHA-256 checksum, component manifest, and release notes. The exact [GNU corresponding-source release](https://github.com/mplsllc/macmake-gpl/releases/tag/macmake-v0.1.0-toolchain-sources) is published separately.

The CLI requires a project path. From a configured project directory, a supported build command looks like:

```sh
macmake build . --target "Classic PPC C"
```

Use `macmake help` and `macmake help build` in the installed version for its complete offline command reference.

## Project links

- Website: [macmake.dev](https://macmake.dev)
- Compatibility: [Classic Macintosh OS compatibility tracker](https://macmake.dev/compatibility/)
- Repository summary: [compatibility scope and evidence boundary](docs/compatibility.md)
- Install: [Linux installation instructions](https://macmake.dev/install.html)
- Getting started: [first application guide](https://macmake.dev/getting-started.html)
- CLI reference: [commands, project format, and JSON schemas](https://macmake.dev/docs/cli-reference.html)
- Releases: [GitHub Releases](https://github.com/mplsllc/macMAKE/releases)
- GNU corresponding source: [macMAKE v0.1.0 toolchain sources](https://github.com/mplsllc/macmake-gpl/releases/tag/macmake-v0.1.0-toolchain-sources)
- Issues: [GitHub issue tracker](https://github.com/mplsllc/macMAKE/issues)

For offline, version-accurate command help, use `macmake help` and `macmake help build` in the installed binary.
