# ProiectC

This repository contains a small C++ catalog management application. Sources
are organised as follows:

- `src/` - library source files (`.cpp` except for `main.cpp`)
- `include/` - all header files
- `main.cpp` - entry point of the application
- `data/elevi/` - sample input files for students

Use CMake to build the `ProiectC_` executable:

```bash
cmake -S . -B build
cmake --build build
```

The build and executable files are ignored via `.gitignore`.
