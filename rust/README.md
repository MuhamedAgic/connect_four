# Connect 4
Connect 4 game written in Rust

# Installing Rust <a href="https://emoji.gg/emoji/4504-rust"><img src="https://cdn3.emoji.gg/emojis/4504-rust.png" width="32px" height="32px" alt="rust" style="vertical-align: -5px;"></a>
If you don't have Rust installed, you can do so using [this link](https://rust-lang.org/tools/install/)

# Project setup
In this setup we currently have 5 main elements, these elements are:
- `connect_four_core`: The core functionallity of the connect four game.
- `connect_four_rs`: The connect four game loop, which uses the components of `connect_four_core`.
- `connect_four_cpp`: A cargo project which exports Rust code to C++.
- `connect_four_py`: A cargo project which exports Rust code to Python.
- `connect_four_ffi`: A cargo project which has generic C exports which can be called from many languages.
- `ffi_examples`: Examples where Rust code is called in different programming languages.

# Running the game 
Go to the `connect_four_rs` folder and run the `cargo run` command

# Running the tests
In the `connect_four_core` folder, run the `cargo test` command

## Running tests with code coverage
To run the tests with code coverage, install `cargo-llvm-cov`. \
You can do so by running `cargo install cargo-llvm-cov` in the terminal. \
To generate nice html output where you can see the code coverage visualy line by line, run `cargo llvm-cov --html --open` in the project root. \
Some more documentation about `cargo-llvm-cov` can be found [here](https://www.rustprojectprimer.com/measure/coverage.html#cargo-llvm-cov).

# Integration in other programming languages (FFI)
There are packages which allow us to make bindings for other programming languages! \
How to integrate the connect 4 game in other programming languages is described below in this section.

## Python <a href="https://emoji.gg/emoji/64443-python"><img src="https://cdn3.emoji.gg/emojis/64443-python.png" width="24px" height="24px" alt="python" style="vertical-align: -5px;"></a>
This [package](https://crates.io/crates/pyo3) provides functionality to easily export (parts of) our Rust module to Python. \
Running and interacting with Python code from a Rust binary is also supported, but is not of importance here. \
To be able to call the main `run()` function of the game in python, follow these steps:
- create a virtual environment (Python 3.13 works)
- install maturin with `pip install maturin`
- go inside the `connect_four_py` directory, it's a separate cargo project, and run `maturin develop`, you should see it install the Rust components as a Python package
- you should be able to see the Rust code installed as a Python package when you run `pip list` or something similar in the terminal
- You should be able to run the python file in `ffi_examples/python/example.py`

If it worked, Congratulations! You succesfully ran Rust <a href="https://emoji.gg/emoji/4504-rust"><img src="https://cdn3.emoji.gg/emojis/4504-rust.png" width="20px" height="20px" alt="rust" style="vertical-align: -5px;"></a> code in Python <a href="https://emoji.gg/emoji/64443-python"><img src="https://cdn3.emoji.gg/emojis/64443-python.png" width="16px" height="16px" alt="python" style="vertical-align: -3px;"></a> 🚀


## <a href="https://emoji.gg/emoji/92158-cpp"><img src="https://cdn3.emoji.gg/emojis/92158-cpp.png" width="48px" height="48px" alt="cpp"></a>
This [package](https://crates.io/crates/cxx) provides functionality to export (parts of) our Rust module to C++. \
In this example, we use cmake to build the Rust and C++ code. \
Currently, this C++ ffi example only works under linux. \
To be able to call the main `run()` function of the game in C++, follow these steps:
- go to the `ffi_examples/cpp/` folder
- run the following commands to build and link the Rust and C++ code
```bash
cmake -S . -B build
cmake --build build
```
If everything worked, you should be able to run the `connect_four_cpp` executable in the build folder. \
Congratulations! You succesfully ran Rust <a href="https://emoji.gg/emoji/4504-rust"><img src="https://cdn3.emoji.gg/emojis/4504-rust.png" width="20px" height="20px" alt="rust" style="vertical-align: -5px;"></a> code in C++ 🚀

## Java <a href="https://emoji.gg/emoji/64443-java"><img src="https://cdn3.emoji.gg/emojis/64443-java.png" width="30px" height="30px" alt="java" style="vertical-align: -5px;"></a>
The `connect_four_ffi` crate in this project provides generic bindings, which we can use in Java.\
In this example, we use gradle to build and the JDK 21.\
Install gradle [here](https://gradle.org/releases/). \
Install JDK [here](https://adoptium.net/temurin/releases?version=21&os=any&arch=any&mode=filter). 

You might need to set the path to your installed Java version, you can do so by executing `setx JAVA_HOME "<path to java folder>"` and then restarting your terminal. 

Go inside the `ffi_examples/java/` folder and execute the `gradle run --quiet --console=plain` command.\
If it works, congratulations! You succesfully ran Rust <a href="https://emoji.gg/emoji/4504-rust"><img src="https://cdn3.emoji.gg/emojis/4504-rust.png" width="20px" height="20px" alt="rust" style="vertical-align: -5px;"></a> code in Java <a href="https://emoji.gg/emoji/64443-java"><img src="https://cdn3.emoji.gg/emojis/64443-java.png" width="20px" height="20px" alt="java" style="vertical-align: -5px;"></a> 🚀

## <a href="https://emoji.gg/emoji/23123-csharp"><img src="https://cdn3.emoji.gg/emojis/23123-csharp.png" width="48px" height="48px" alt="csharp"></a>
The `connect_four_ffi` crate in this project provides generic bindings, which we can use in C#.\
Go inside the `ffi_examples/cs/` folder and execute the `dotnet run` command.\
If it works, congratulations! You succesfully ran Rust <a href="https://emoji.gg/emoji/4504-rust"><img src="https://cdn3.emoji.gg/emojis/4504-rust.png" width="20px" height="20px" alt="rust" style="vertical-align: -5px;"></a> code in <a href="https://emoji.gg/emoji/23123-csharp"><img src="https://cdn3.emoji.gg/emojis/23123-csharp.png" width="20px" height="20px" alt="csharp" style="vertical-align: -5px;"></a> 🚀

## <a href="https://emoji.gg/emoji/3058-golang"><img src="https://cdn3.emoji.gg/emojis/3058-golang.png" width="64px" height="64px" alt="Golang" style="vertical-align: -10px;"></a>
The `connect_four_ffi` crate in this project provides generic bindings, which we can use in Go. Install Go [here](https://go.dev/dl/).\
Currently, this go ffi example only works under windows.
Go inside the `ffi_examples/go/` folder and execute the following commands: \
```bash
go mod init connect_four_go
go mod tidy
./build.ps1
go run .
```
If it works, congratulations! You succesfully ran Rust <a href="https://emoji.gg/emoji/4504-rust"><img src="https://cdn3.emoji.gg/emojis/4504-rust.png" width="20px" height="20px" alt="rust" style="vertical-align: -5px;"></a> code in <a href="https://emoji.gg/emoji/3058-golang"><img src="https://cdn3.emoji.gg/emojis/3058-golang.png" width="32px" height="32px" alt="Golang" style="vertical-align: -10px;"></a> 🚀

