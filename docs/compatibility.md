# Classic Macintosh OS compatibility

macMAKE v0.1.0 is a Linux x86-64 toolchain for Classic Macintosh PowerPC CFM/PEF applications, primarily written in C. Mac OS 9 is the current development baseline.

- The exact public v0.1.0 binary has passed Linux build, link, packaging, and structural artifact validation for the included PowerPC example. The OS point release was not specified, and the exact release binary has not yet been runtime-tested on a Macintosh OS.
- Historical Mac OS 9.2.2 runtime evidence exists for MacSurf built with an earlier macMAKE development build. That does not establish a runtime pass for the public v0.1.0 executable.
- Earlier PowerPC versions of System 7 and Mac OS 8 have not yet been verified.
- Native 68K application generation and Mac OS X targets are unsupported in v0.1.

The [compatibility tracker](https://macmake.dev/compatibility/) records version, architecture, macMAKE identity, application fixture, test stage, and limitations. It distinguishes compilation and package checks from OS loader, startup, and runtime results. SDKs and MSL/runtime files must be supplied from sources the user is authorized to use; they are not bundled with macMAKE.
