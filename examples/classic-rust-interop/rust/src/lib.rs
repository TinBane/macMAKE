#![no_std]

/// Small C ABI function compiled to PowerPC XCOFF for the example app.
#[no_mangle]
pub extern "C" fn macmake_rust_answer(value: u32) -> u32 {
    value.wrapping_add(1)
}
