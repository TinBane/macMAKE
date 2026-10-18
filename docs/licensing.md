# Licensing for macMAKE v0.1.1

**Release status:** macMAKE v0.1.1 is publicly available from [GitHub Releases](https://github.com/mplsllc/macMAKE/releases/tag/v0.1.1). Its matching GNU corresponding-source release for both PowerPC and Motorola 68000 toolchains is public at [`macmake-v0.1.1-rc4-toolchain-sources`](https://github.com/mplsllc/macmake-gpl/releases/tag/macmake-v0.1.1-rc4-toolchain-sources).

macMAKE is a mixed distribution. The proprietary macMAKE executable and separately licensed toolchain components have distinct license boundaries. The proprietary license applies only to the files it identifies; it does not override the license or redistribution rights of third-party components.

## Proprietary macMAKE executable

The macMAKE CLI and original macMAKE product implementation are proprietary and closed-source. The [macMAKE Proprietary Binary License](../LICENSE) permits free personal, educational, research, nonprofit, and commercial development use, including use from scripts, coding agents, CI, and automated build environments. It permits installations and reasonable internal backup copies within an individual's or organization's authorized environment. It restricts public redistribution, mirroring, resale, sublicensing, and distribution of modified proprietary executable copies unless MPLS LLC expressly authorizes that channel. Its scope is limited to the proprietary components identified by the release manifest (`bin/macmake`).

The license states that developers retain ownership and licensing control of independent applications they create with macMAKE. It does not itself govern any third-party runtime code incorporated into an application. The release archive carries separate permissive licenses for the [First Application example](../examples/first-app/LICENSE.txt), [HelloWindow68K example](../examples/first-app/hello-window-68k/LICENSE.txt), and [Classic Rust Interop example](../examples/classic-rust-interop/LICENSE.txt), allowing users to incorporate and distribute those examples as part of their own applications.

## GNU compilers and Binutils

The distribution includes separate GNU GCC 12.2.0 and GNU Binutils 2.46.1 executables for both PowerPC (`powerpc-unknown-macmake` / `powerpc-ibm-aix7.1.0.0`) and Motorola 68000 (`m68k-unknown-elf`). Their source and binaries retain their applicable GNU licenses and may be copied or redistributed as those licenses permit. The proprietary macMAKE terms do not restrict those rights.

The exact v0.1.1 source release is [`macmake-v0.1.1-rc4-toolchain-sources`](https://github.com/mplsllc/macmake-gpl/releases/tag/macmake-v0.1.1-rc4-toolchain-sources), source revision `f471dd13a79dd6e095d8f00be20d8a318e30be2f`. Its archive is `macmake-v0.1.1-rc4-toolchain-corresponding-source.tar.xz`, SHA-256 `ddd3b20cbaf3e2cbdca4ed5f61f34946065f71089b9ea7a99bac188213145433`. It contains:
- Complete upstream GCC 12.2.0 (SHA-256 `e549cf9cf3594a00e27b6589d4322d70e0720cdd213f39beb4181e06926230ff`) and Binutils 2.46.1 (SHA-256 `e127a709cba24c76de8936cb7083dd768f28cd37eb010492e2f19b71eb1294e4`) source archives.
- PowerPC target patch (SHA-256 `20d025ecf9f4d83da5144ce5f03d9b9d382df53c986ab7152d9a2766910c16c9`), build scripts, and configuration.
- Motorola 68000 target configuration and build scripts under `m68k/`.
- Runtime support source, build scripts, license texts, and component identity records.

The public Linux x86-64 binary is `macmake-v0.1.1-linux-x86_64.tar.xz`, SHA-256 `d83c173d4184a67738df3bad7d0cadb2b6eab45fa2cc06df89f9f7eff4bd0656`.

The PowerPC runtime inputs include packaged `libgcc.a` (SHA-256 `9204ff56371500f9aa92401623ec2a2877918396498b87ad40943980458928aa`) and `crtdbase.o` (SHA-256 `01ab3b224d6906fa3f6a1fb9dd61d062a9685b6102d5ca02b9a3b69f38b5be4f`). The M68000 runtime archive is `libgcc.a` (SHA-256 `8ec2269f540f791e2429441bd5633ac7bd71fa7f964e61ed79e356d55b63cacd`). Individual source files carry GPLv3 and GCC Runtime Library Exception 3.1 notices; the exception is file-specific and its permissions depend on an eligible compilation process. Distribution of the runtime archives themselves remains subject to applicable GPL terms.

## Other third-party dependencies

Rust dependency notices and license texts are included separately in the release archive under `licenses/`. Binutils carries its GNU and bundled zlib license notices; GCC carries GPL and runtime exception notices. Each component remains under its own terms.

## User-supplied historical development files

The distribution does not include Apple Universal Interfaces, Metrowerks MSL, CodeWarrior archives, or other nonredistributable historical SDK material. Users must provide files they are authorized to use and register them with the installed CLI. Those user-supplied files are not covered by macMAKE's proprietary license or included in the GPL corresponding-source package.

## Legal review boundary

This document records a technical audit of the release artifacts and source mapping; it is not legal advice, a legal opinion, or a guarantee of legal clearance. The audit verified the published source archive, source and patch hashes, packaged GCC/Binutils component hashes, included notices, and the documented runtime selection. No qualified legal opinion is claimed. GCC and Binutils remain separately licensed programs in the distribution; their licenses are not applied to the proprietary macMAKE CLI by the fact that the programs are packaged together.
