# Rust client for the macMAKE CLI

This source-available sample demonstrates a Rust program invoking the Linux
macMAKE executable and reading its JSON help interface. It is not a Rust
cross-compiler sample and does not produce a Classic Macintosh executable.

Requirements: Rust stable, Cargo, and an installed `macmake` on `PATH` (or set
`MACMAKE_BIN` to its path).

```sh
cargo run --offline --locked
```

The program runs `macmake --version` and `macmake help build --json`, checks
that the latter is a JSON object, and prints it. It does not modify a project
or send telemetry. The sample uses only the Rust standard library. The
First Application Example License in the parent directory applies to this
example.
