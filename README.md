# ProiectC

This repository contains a small C++ catalog management application. Sources
are organised as follows:

- `src/` - library source files (`.cpp` except for app1/app2)
- `include/` - all header files
- `app1.cpp` / `app2.cpp` - two command line tools
- `data/elevi/` - sample input files for students

Use CMake to build both tools:

```bash
cmake -S . -B build
cmake --build build
```

The build and executable files are ignored via `.gitignore`.
