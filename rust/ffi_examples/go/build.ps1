# 1. Build Rust
cargo build --manifest-path ..\..\connect_four_ffi\Cargo.toml

# 2. Copy DLL
Copy-Item ..\..\target\debug\connect_four_ffi.dll . -Force