use std::env;
use std::process::{Command, Stdio};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let executable = env::var_os("MACMAKE_BIN").unwrap_or_else(|| "macmake".into());

    let version = Command::new(&executable)
        .arg("--version")
        .stdout(Stdio::piped())
        .stderr(Stdio::inherit())
        .output()?;
    if !version.status.success() {
        return Err("macmake --version failed".into());
    }
    print!("{}", String::from_utf8(version.stdout)?);

    let help = Command::new(&executable)
        .args(["help", "build", "--json"])
        .stdout(Stdio::piped())
        .stderr(Stdio::inherit())
        .output()?;
    if !help.status.success() {
        return Err("macmake help build --json failed".into());
    }
    let help_text = String::from_utf8(help.stdout)?;
    if !help_text.trim_start().starts_with('{') {
        return Err("macmake help build --json did not return a JSON object".into());
    }
    println!("Machine-readable build help follows:\n{help_text}");
    Ok(())
}
