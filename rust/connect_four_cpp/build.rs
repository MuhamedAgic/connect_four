use std::{fs, path::Path};

fn copy_dir(src: &Path, dst: &Path) {
    fs::create_dir_all(dst).unwrap();

    for entry in fs::read_dir(src).unwrap() {
        let entry = entry.unwrap();
        let path = entry.path();

        if path.is_dir() {
            copy_dir(&path, &dst.join(path.file_name().unwrap()));
        } else {
            fs::copy(&path, dst.join(path.file_name().unwrap())).unwrap();
        }
    }
}

fn main() {
    cxx_build::bridge("src/ffi.rs")
        .flag_if_supported("-std=c++20")
        .compile("connect_four_cpp_rs");

    // Copy the generated C++ header files to the cpp directory so they can be included in the C++ project
    let workspace_dir = Path::new(env!("CARGO_MANIFEST_DIR")).parent().unwrap();
    copy_dir(
        Path::new(workspace_dir.join("target/cxxbridge").to_str().unwrap()),
        Path::new(workspace_dir.join("ffi_examples/cpp").to_str().unwrap())
    );

    println!("cargo:rerun-if-changed=src/ffi.rs");
}