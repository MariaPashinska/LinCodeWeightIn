# 128 — 128-bit SIMD (SSE2 / SSE4.1)

## Library

| Target | Type | Variant Source | Compiler Flags |
|--------|------|---------------|----------------|
| `v1.3` | Static library (`.a`) | `LinCodeWeightInv.cpp`, `Polynomials.cpp`, `ReadWrite.cpp`, `lib128.cpp`, `Data.cpp`, `testDriver.cpp` | `-march=native` (GCC/Clang) / `/arch:AVX` (MSVC) |

Variant-specific header: `include/lib128.h`

---

## Purpose

This variant targets CPUs with **128-bit SIMD** capabilities (SSE2, SSE3, SSSE3, SSE4.1). It uses 128-bit registers to process multiple data elements in parallel, providing a moderate performance improvement over the scalar baseline.

## Key Characteristics

- **128-bit vector registers** (XMM registers on x86).
- **SSE2 / SSE4.1** instruction set support.
- **Universal x86 compatibility** — works on any x86/x86-64 CPU from the last 20+ years.
- **Good balance** of performance and compatibility.

## Internal Layout

```
128/
├── CMakeLists.txt
├── Makefile
├── include/
│   ├── LinCodeWeightInv.h
│   ├── Data.h
│   ├── DataManagement.h
│   ├── Polynomials.h
│   ├── ReadWrite.h
│   ├── testDriver.h
│   ├── lib128.h
│   ├── lib256.h
│   ├── lib512.h
│   └── lib_neon.h
├── src/
│   ├── CMakeLists.txt
│   ├── LinCodeWeightInv.cpp
│   ├── Data.cpp
│   ├── DataManagement.cpp
│   ├── Polynomials.cpp
│   ├── ReadWrite.cpp
│   ├── testDriver.cpp
│   └── lib128.cpp
├── testFiles/
│   ├── ArticleData
│   ├── TestDataBig
│   └── TestDataSmall
└── testProgram/
    ├── CMakeLists.txt
    ├── Source.cpp
    ├── Test128.cpp
    └── Test128_*.cpp
```

## Building

### CMake

```bash
cd 128/src
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Make

```bash
cd 128/src
make
```

---

## API

All 128-bit-specific functions share the same API as the other variants (see the main `README.md` for the full API reference). The `instructionSet` variable will report a value in the range 2–5 depending on the detected CPU capabilities.

---

## Authors

Maria Pashinska-Gadzheva and Iliya Bouyukliev

## Further Reading

- [ACM Algorithm 1059](https://doi.org/10.1145/3777479) — LinCodeWeightInv library paper
- [calgo.acm.org](https://calgo.acm.org/) — Full library with instruction detection
