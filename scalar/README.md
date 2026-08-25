# scalar — Plain C++ (No SIMD)

## Library

| Target | Type | Variant Source | Compiler Flags |
|--------|------|---------------|----------------|
| `v1.3` | Static library (`.a`) | `LinCodeWeightInv.cpp`, `Polynomials.cpp`, `ReadWrite.cpp`, `lib_scalar.cpp`, `Data.cpp`, `testDriver.cpp` | `-march=native` (GCC/Clang) / `/arch:SSE` (MSVC) |

Variant-specific header: `include/lib_scalar.h`

---

## Purpose

This is the **baseline implementation** of the LinCodeWeightInv library using **plain C++ with no SIMD or vectorization**. It serves as a reference for correctness and a performance baseline to compare against the optimized SIMD variants.

## Key Characteristics

- **No extended registers** — computations use standard scalar operations only.
- **Universal compatibility** — runs on any x86/x86-64 or ARM CPU without requiring special instruction set support.
- **Slowest variant** — expected to be the slowest of all five builds, but useful for validation.

## Internal Layout

```
scalar/
├── CMakeLists.txt
├── Makefile
├── include/
│   ├── LinCodeWeightInv.h
│   ├── Data.h
│   ├── DataManagement.h
│   ├── Polynomials.h
│   ├── ReadWrite.h
│   ├── testDriver.h
│   └── lib_scalar.h
├── src/
│   ├── CMakeLists.txt
│   ├── LinCodeWeightInv.cpp
│   ├── Data.cpp
│   ├── DataManagement.cpp
│   ├── Polynomials.cpp
│   ├── ReadWrite.cpp
│   ├── testDriver.cpp
│   └── lib_scalar.cpp
├── testFiles/
│   ├── ArticleData
│   ├── TestDataBig
│   └── TestDataSmall
└── testProgram/
    ├── CMakeLists.txt
    ├── Source.cpp
    ├── TestScalar.cpp
    └── TestScalar_*.cpp
```

## Building

### CMake

```bash
cd scalar/src
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Make

```bash
cd scalar/src
make
```

---

## API

All scalar-specific functions share the same API as the other variants (see the main `README.md` for the full API reference). The only difference is that `instructionSet` will always report a value `< 5` (no extended registers).

---

## Authors

Maria Pashinska-Gadzheva and Iliya Bouyukliev

## Further Reading

- [ACM Algorithm 1059](https://doi.org/10.1145/3777479) — LinCodeWeightInv library paper
- [calgo.acm.org](https://calgo.acm.org/) — Full library with instruction detection
