cmake_minimum_required(VERSION 3.16)

project(connect_four_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# -----------------------------
# Paths
# -----------------------------
set(RUST_DIR ${CMAKE_SOURCE_DIR}/../..)
set(RUST_CRATE connect_four_cpp_rs)

set(RUST_TARGET_DIR ${RUST_DIR}/target/debug)
set(RUST_LIB ${RUST_TARGET_DIR}/lib${RUST_CRATE}.a)

# -----------------------------
# Build Rust FIRST
# -----------------------------
add_custom_target(rust_build ALL
    COMMAND cargo build -p ${RUST_CRATE}
    WORKING_DIRECTORY ${RUST_DIR}
)

# -----------------------------
# C++ target
# -----------------------------
add_executable(connect_four_cpp
    example.cpp
)

# -----------------------------
# Include headers
# -----------------------------
target_include_directories(connect_four_cpp PRIVATE
    ${RUST_DIR}/target/cxxbridge
)

# -----------------------------
# Compile generated bridge
# -----------------------------
file(GLOB_RECURSE CXXBRIDGE_SRC
    "${RUST_DIR}/target/cxxbridge/*.cc"
)

target_sources(connect_four_cpp PRIVATE ${CXXBRIDGE_SRC})

# -----------------------------
# Link
# -----------------------------
target_link_libraries(connect_four_cpp PRIVATE
    ${RUST_LIB}
    pthread
)

add_dependencies(connect_four_cpp rust_build)