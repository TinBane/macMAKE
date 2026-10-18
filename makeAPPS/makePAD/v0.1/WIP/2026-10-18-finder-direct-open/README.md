# makePAD Finder direct-open regression

Date: 2026-10-18  
Status: reproduced by the owner in the RC7-built makePAD application; correction is documented, but this artifact has not been rebuilt with it.

## Observed behavior

The owner reports that the RC7-built makePAD opens a saved text document when
chosen through **File > Open**, but double-clicking the saved file in Finder
launches makePAD with a blank document. This is a recurring makePAD release
regression. File > Open and Finder double-click opening must be tested as two
separate workflows.

The affected MacBinary is:

| Property | Value |
|---|---|
| File | `makePAD-v0.1.1-rc7-os9.bin` |
| SHA-256 | `505a3b1deb62ffc396537b1010c8f23921f4ae4308ac6ee989ccf7cd285ca3d1` |
| Source snapshot | `f0cebb023617f9963b0951558528b5991d7e4047` |

The source snapshot predates the Finder Apple Event implementation at
`08e618db956d7a0b897673034dcbc60ff92a9bbf` (later ported to the PPC backport
branch in `bc38a946ed1fdbc2eaf1bca67a74928db393ddef`). The RC7 project sets
`SIZE(-1)` flags to decimal `22720` (`0x58c0`), which includes the
`isHighLevelEventAware` bit (`0x0040`). But the affected `application.c` has no
`kHighLevelEvent` dispatch and installs no `kAEOpenDocuments` handler. The
flag alone cannot load the document Finder asks the application to open.

## Why File > Open works while Finder does not

File > Open uses Standard File to obtain an `FSSpec`, then calls makePAD's
document reader directly. Opening a text document from Finder uses the
Classic Apple Event Manager: Finder launches or activates the app and sends
an `aevt/odoc` (**Open Documents**) event containing the selected file. If the
app does not process that event, its normal startup creates an empty document
and the requested file is ignored. This is not a save-data failure, and
changing the File Manager save routine does not fix it.

## Required code fix

For every makePAD target, retain all of these parts:

1. Keep `SIZE(-1)` high-level-event awareness enabled. The relevant flag is
   `0x0040`; preserve other target flags as needed. For the RC7 profile,
   `0x58c0` already includes it.
2. Install an Apple Event handler for `kAEOpenDocuments` in the application
   startup path. The established makePAD implementation also registers the
   core open-application, print-documents, and quit-application handlers.
3. Dispatch `kHighLevelEvent` from the normal event loop to
   `AEProcessAppleEvent`.
4. In the `odoc` handler, read `keyDirectObject` as an Apple Event list,
   extract the file reference (`FSSpec` for these classic targets), and pass
   it to a shared document-loading function. File > Open and Finder opening
   must use the same loader so title, dirty state, and redraw behavior stay
   consistent.
5. Preserve the app's correct Finder identity and document association.
   Where the target relies on bundle registration, include a creator-matching
   signature and valid `BNDL`/`FREF` mappings for `APPL` and `TEXT`, and retain
   the resource fork and Finder metadata in MacBinary. Bundle registration
   tells Finder which app handles the document; the `odoc` handler makes the
   app actually open it. These are separate requirements.

The application-level fix is present in the source history cited above. The
RC7 test project was copied from the earlier baseline instead of that fixed
source, and its runtime checklist only established File > Open behavior.
That stale project snapshot and missing direct-open test allowed the regression
to recur.

If a corrected bundle is structurally verified but Finder still uses stale
association data, rebuild the test volume's Desktop database and retest.
Desktop database refresh is only a follow-up for cached Finder metadata; it
does not replace the Apple Event handler or correct bundle resources.

## Mandatory makePAD release check

For every candidate and target OS/architecture, test both paths with the same
saved text file:

1. Open it through **File > Open** and confirm its contents appear.
2. Quit makePAD, then double-click that file in Finder.
3. Confirm Finder launches or activates makePAD and the file contents appear
   in the editor instead of a blank document.
4. Record the application source revision, CLI/toolchain identity, OS and
   architecture, MacBinary SHA-256, and the two results separately.

Do not infer Finder-open support from successful saving, File > Open, an
`APPL` file type, a high-level-event-aware `SIZE` resource, or a successful
PEF/CODE and MacBinary structural inspection alone.
