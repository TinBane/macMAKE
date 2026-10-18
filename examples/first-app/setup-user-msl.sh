#!/usr/bin/env bash
set -euo pipefail

if [[ $# -lt 1 || $# -gt 2 ]]; then
    printf 'usage: %s CODEWARRIOR_INSTALL_ROOT_OR_MACMAKELIBS_ROOT [DESTINATION]\n' "$0" >&2
    exit 2
fi

sdk_root=$(cd -- "$1" && pwd)
example_root=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)
destination=${2:-"$example_root/sdk"}

if [[ -f "$sdk_root/MSL_C/MSL_MacOS/Lib/PPC/MSL_C_Carbon.Lib" \
    && -f "$sdk_root/MSL_Runtime_PPC_D.Lib" \
    && -f "$sdk_root/MSL_Extras/MSL_MacOS/Lib/PPC/MSL_Extras_Carbon.Lib" ]]; then
    # The macMAKELibs minimal fetch retains its repository-relative layout.
    sources=(
        "$sdk_root/MSL_C/MSL_MacOS/Lib/PPC/MSL_C_Carbon.Lib"
        "$sdk_root/MSL_Runtime_PPC_D.Lib"
        "$sdk_root/MSL_Extras/MSL_MacOS/Lib/PPC/MSL_Extras_Carbon.Lib"
    )
elif [[ -f "$sdk_root/MSL/MSL_C/MSL_MacOS/Lib/PPC/MSL_C_Carbon.Lib" \
    && -f "$sdk_root/MacOS Support/Libraries/Runtime/Libs/MSL_Runtime_PPC_D.Lib" \
    && -f "$sdk_root/MSL/MSL_Extras/MSL_MacOS/Lib/PPC/MSL_Extras_Carbon.Lib" ]]; then
    # Also accept a conventional CodeWarrior Pro installation root.
    sources=(
        "$sdk_root/MSL/MSL_C/MSL_MacOS/Lib/PPC/MSL_C_Carbon.Lib"
        "$sdk_root/MacOS Support/Libraries/Runtime/Libs/MSL_Runtime_PPC_D.Lib"
        "$sdk_root/MSL/MSL_Extras/MSL_MacOS/Lib/PPC/MSL_Extras_Carbon.Lib"
    )
else
    printf 'could not find the three required MSL archives under %s\n' "$sdk_root" >&2
    printf 'expected the pinned macMAKELibs layout or a CodeWarrior Pro 8 installation root\n' >&2
    exit 1
fi

expected_hashes=(
    39c0506b0c2c55942680838e9fe874fbf303c2c42e21dda6fc4f43e189280588
    dd53d1a0ee9fa744d2179cde8ad77e25e0f43772f74a5f6783b59b2ad8c9dc1a
    a887ba9f7e0201d47278196b1032707050d7a92278848a5b20704f34b63e0e78
)
filenames=(MSL_C_Carbon.Lib MSL_Runtime_PPC_D.Lib MSL_Extras_Carbon.Lib)

for index in "${!sources[@]}"; do
    source=${sources[$index]}
    if [[ ! -f "$source" || -L "$source" ]]; then
        printf 'required MSL archive is missing or is not a regular file: %s\n' "$source" >&2
        exit 1
    fi
    actual_line=$(sha256sum -- "$source") || {
        printf 'could not hash MSL archive: %s\n' "$source" >&2
        exit 1
    }
    actual_hash=${actual_line%% *}
    if [[ "$actual_hash" != "${expected_hashes[$index]}" ]]; then
        printf 'MSL archive does not match the validated first-app input: %s\n' "$source" >&2
        printf '  expected SHA-256: %s\n  actual SHA-256:   %s\n' "${expected_hashes[$index]}" "$actual_hash" >&2
        printf 'No files were copied. Use the pinned SDK revision or update the project inputs deliberately.\n' >&2
        exit 1
    fi
done

if [[ -e "$destination" || -L "$destination" ]]; then
    if [[ ! -d "$destination" || -L "$destination" ]]; then
        printf 'refusing to copy MSL files through a non-directory or symlink: %s\n' "$destination" >&2
        exit 1
    fi
fi
mkdir -p -- "$destination"
for filename in "${filenames[@]}"; do
    target="$destination/$filename"
    if [[ -e "$target" || -L "$target" ]]; then
        if [[ ! -f "$target" || -L "$target" ]]; then
            printf 'refusing to replace a non-regular MSL destination: %s\n' "$target" >&2
            exit 1
        fi
    fi
done

staging=$(mktemp -d "$destination/.sdk-staging.XXXXXXXX")
trap 'rm -rf -- "$staging"' EXIT
for index in "${!sources[@]}"; do
    install -m 0644 -- "${sources[$index]}" "$staging/${filenames[$index]}"
done
for filename in "${filenames[@]}"; do
    mv -f -- "$staging/$filename" "$destination/$filename"
done

printf 'Copied and verified the pinned MSL archives from %s to %s\n' "$sdk_root" "$destination"
sha256sum -- "${sources[@]}"
