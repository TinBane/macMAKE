# Language support in the v0.1.1 candidate

This release is primarily a C toolchain. Project-manifest acceptance of a
language value does not itself mean the release contains a compiler provider
or runtime for that language.

| Language/profile | Compile | Link/package | Runtime evidence | v0.1.1 candidate status |
|---|---|---|---|---|
| C, Classic PowerPC CFM/PEF | GCC 12.2.0; C89-oriented profile | Supported first-app workflow, PEF/resources/Finder metadata/MacBinary II | Historical Mac OS 9 application evidence; the release's clean-host fixture validation is Linux structural evidence | Supported |
| C, classic segmented M68K | GNU GCC 12.2.0 `m68k-unknown-elf`, M68000 baseline | macMAKE-owned single-segment CODE 0/CODE 1, bounded Rez subset, Finder metadata and MacBinary II | Owner tested HelloWindow and makePAD artifacts on the individual systems recorded in `toolchains/classic-m68k/toolchain.json` and the public makePAD archive | Experimental; not release-qualified |
| C++ PowerPC | Experimental GCC `cc1plus` exists in development builds; the ordinary release archive does not include it | Selected project builds have linked with external historical runtime inputs, but no general release C++ workflow is qualified | Selected historical Classilla components have been built; no completed clean Classilla application runtime claim | Experimental, outside supported release scope |
| Rust, Classic PowerPC | External pinned Rust nightly emits PPC XCOFF; no Rust compiler provider is bundled with macMAKE | [`classic-rust-interop`](../examples/classic-rust-interop/README.md) feeds a Rust object into ordinary `macmake build`; macMAKE performs native XCOFF linking, CFM/PEF, resources, Finder metadata, and MacBinary packaging | Exact candidate build and structural results are recorded with the release qualification evidence; historical MacRust/CodeWarrior runtime evidence is separate | Reproducible external-toolchain integration sample; Rust source itself is not a `macmake build` input |

## C++ detail

The private development compiler work measures several useful boundaries, but
does not amount to general CodeWarrior C++ compatibility:

| Area | Evidence and current limit |
|---|---|
| Frontend | GCC 12.2.0 `cc1plus` and compatibility options compile selected Classilla C++ units in development configurations. It is not included in the v0.1.1 release candidate. |
| Name mangling | GCC uses the Itanium C++ ABI. It does not generally emit CodeWarrior/Metrowerks names; no general mangling bridge is provided. |
| Linking | macMAKE has partial XCOFF/POWR and CFM handling exercised by measured targets. A general C++ application link contract is not qualified. |
| Static initialization | A few startup and `.sinit` paths have measured support in development fixtures. General constructor registration and cross-fragment initialization are not qualified. |
| RTTI | Selected compiler output exposes Itanium typeinfo requirements. CodeWarrior RTTI layouts are not interchangeable; no broad RTTI compatibility is claimed. |
| Exceptions | Selected sources compile with exceptions enabled, but the runtime census finds unresolved `__cxa_*`, unwinder, and typeinfo providers. General exception execution is unsupported. |
| Runtime libraries | CodeWarrior MSL C++ libraries and any other historical inputs are user-supplied, separately licensed materials. The release does not bundle or promise a complete C++ runtime. |

The Classilla evidence is a set of imported-target builds and a validated
package assembly, not a clean rebuild and runtime verification of the whole
browser. See [the CodeWarrior import guide](codewarrior-xml-and-classilla.md),
the [public-safe Classilla evidence summary](classilla-evidence-summary.md),
and the [C++ compatibility matrix](cpp-compatibility.md).

## Rust development evidence and release boundary

The separate [MacRust repository](https://github.com/mplsllc/MacRust) records
real Rust-to-Classic PowerPC work. Its ABI experiments pin
`classic-mac-rust` revision `ecab002216f7b5764b12e339a1880f4d96cdad90`,
`rustc 1.70.0-nightly` (`2036fdd24`, LLVM 16), and the
`powerpc-apple-macos.json` target, which emits 32-bit big-endian PPC XCOFF.
The E0-CW-16 record shows a Rust-produced XCOFF object passed through the
CodeWarrior Pro 8 object handoff and linker into a PEF, with a C-to-Rust call
executed successfully. Other MacRust experiments cover callbacks, `core` and
`alloc`, and a Rust-owned Window/Menu/Event loop behind C Toolbox shims.

Those are genuine Rust-to-Classic-Macintosh results, including a Rust-produced
XCOFF object linked through CodeWarrior, an executed C-to-Rust scalar call,
callbacks/allocation experiments, and a Rust-owned window/event loop behind C
Toolbox shims. The owner also confirms that the Rust-owned window/event-loop
application was run on Mac OS 9. The checked-in E0-CW-13 Phase B record itself
documents source admission on a Tiger/CodeWarrior host, while E0-CW-16 documents
its separate CodeWarrior PEF/runtime gate; preserve those evidence identities
and do not attribute any of these runs to a macMAKE release binary.

The `classic-rust-interop` example is a reproducible integration: the pinned
external Rust compiler emits an XCOFF object and the macMAKE release CLI
consumes it as a link input, creates a CFM/PEF application, and completes the
normal resource/Finder/MacBinary pipeline. Exact candidate identity, Linux
build results, and structural inspection are recorded with the release
qualification evidence. The sample does not imply that macMAKE compiles Rust
source directly or that the candidate binary has been runtime-tested on a
Classic Macintosh OS.

The existing [`rust-cli-client`](../examples/first-app/rust-cli-client) is a
separate Linux-side Rust program that invokes macMAKE's CLI and consumes JSON
help. It is not the Classic Rust application example.

### ABI boundary

Rust and CodeWarrior disagree on some by-value aggregate argument lowering.
Do not pass `#[repr(C)]` structures by value across the Rust/C boundary in
this profile. Use scalar and pointer/out-parameter interfaces or a C shim that
converts the representation. See MacRust's
[`aggregate ABI evidence`](https://github.com/mplsllc/MacRust/blob/main/docs/abi/aggregate-abi-divergence.md).
