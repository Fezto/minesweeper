# Minesweeper (C++ Terminal & Web)

A modern, fully-featured Minesweeper game implemented in C++23. Play in your terminal or directly in your browser via WebAssembly (Emscripten). Designed for clarity, maintainability, and cross-platform compatibility.



---

## Features

- **Interactive terminal UI** with color-coded output
- **WebAssembly (Emscripten) support**: play in your browser
- **Robust input validation** using regular expressions
- **Automatic propagation** for empty cells
- **Flag system** to mark suspected mines
- **Win/loss detection**
- **Modern C++ architecture** (RAII, encapsulation, separation of concerns)
- **Easy to build and extend**

---

## Getting Started

### Prerequisites

- CMake >= 3.14
- C++23 compiler (GCC 11+, Clang 13+, MSVC 2022+)
- (Optional for web) Emscripten SDK

### Build & Run (Native)

```bash
# Clone the repository
# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
cmake --build .

# Run
./terminal      # Linux/macOS
terminal.exe    # Windows
```

### Build & Run (Web)

```bash
# Install Emscripten SDK (once)
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk && ./emsdk install latest && ./emsdk activate latest
source ./emsdk_env.sh

# Build for web
mkdir build-wasm && cd build-wasm
emcmake cmake ..
emmake make

# Serve the HTML file
python -m http.server 8000
# Open http://localhost:8000/terminal.html in your browser
```

---

## How to Play

- **Select board size** (e.g. 10x8)
- **Enter moves** in the format: `ColumnRow Action`
  - `A5 R` — Reveal cell at column A, row 5
  - `B3 F` — Place/remove flag at column B, row 3
  - `C7` — Reveal cell (default action)

### Symbols

- `#` — Hidden cell
- `F` — Flag
- `*` — Mine (shown when you lose)
- `1-8` — Number of adjacent mines
- (space) — Empty cell

---

## Project Structure

```
terminal/
├── src/        # Source files
│   ├── main.cpp
│   ├── Game.cpp
│   ├── Board.cpp
│   ├── Cell.cpp
│   └── web_bindings.cpp
├── include/    # Header files
│   ├── Game.h
│   ├── Board.h
│   ├── Cell.h
│   ├── Message.h
│   └── InputData.h
├── web/        # Web assets (HTML, JS, CSS)
├── build/      # Native build output
├── build-wasm/ # WebAssembly build output
├── CMakeLists.txt
└── README.md
```

---

## Technologies Used

- **C++23** (structured bindings, ranges, smart pointers)
- **CMake** (cross-platform build system)
- **Emscripten** (WebAssembly compilation)
- **Regex** (input validation)
- **ANSI color codes** (terminal UI)

---

## Educational Value

This project demonstrates:

- Modern C++ project structure
- Object-oriented design
- Robust I/O and input validation
- Game algorithms (flood fill, win/loss detection)
- Cross-platform compilation (native & web)

---

## License

MIT License. See LICENSE file for details.

## Contributing

Contributions are welcome! Please fork the repository, create a feature branch, and submit a pull request.

---

## Author

Ayrton (ayrto)

---

## Demo

Add screenshots or GIFs here to showcase the terminal and web versions.
