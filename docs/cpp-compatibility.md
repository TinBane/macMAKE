# C++ compatibility matrix

This matrix describes evidence, not a compatibility promise. The release
archive does not include a C++ frontend or a complete Classic C++ runtime.

| Capability | Current evidence | v0.1.1 release status |
|---|---|---|
| Compilation | Experimental GCC 12.2.0 `cc1plus` in development builds compiles selected Classilla C++ units with measured compatibility switches. | Not shipped or supported as a release workflow. |
| Name mangling | GCC's Itanium C++ ABI differs from CodeWarrior/Metrowerks mangling. Some XCOFF symbol forms are parsed, but there is no general name translation or ABI bridge. | Not generally compatible. |
| Linking | Some imported Classilla C++ targets linked using external runtime inputs. This is per-target evidence, not general C++ application linking. | Experimental, no support promise. |
| Static initialization | Selected XCOFF `.sinit` records and a few startup paths have been measured. General constructor registration, ordering and cross-fragment initialization are not qualified. | Partial research only. |
| RTTI | GCC objects use Itanium typeinfo layouts; historical Metrowerks RTTI symbols are not safe aliases. | Not compatible in general. |
| Exceptions | Selected source compiles with exceptions enabled, but measured output needs `__cxa_*`, unwinder and typeinfo providers not generally supplied by the Classic runtime. | No supported exception runtime. |
| Runtime libraries | Historical MSL C++/runtime archives remain separate user-provided inputs. The release does not bundle a complete C++ standard library or exception runtime. | User inputs do not create a macMAKE support commitment. |

Do not infer full CodeWarrior C++ replacement compatibility from successful
compilation or linkage of one project target. See `language-support.md` and
`classilla-evidence-summary.md` for context.
