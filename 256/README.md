# 256 — 256-bit SIMD (AVX2)

## Library

| Target | Type | Variant Source | Compiler Flags |
|--------|------|---------------|----------------|
| `v1.3` | Static library (`.a`) | `LinCodeWeightInv.cpp`, `Polynomials.cpp`, `ReadWrite.cpp`, `lib256.cpp`, `Data.cpp`, `testDriver.cpp` | `-march=native` (GCC/Clang) / `/arch:AVX2` (MSVC) |

Variant-specific header: `include/lib256.h`

---

## Purpose

This variant targets CPUs with **256-bit SIMD** capabilities (AVX2). It uses 256-bit YMM registers to process twice as many data elements in parallel compared to the 128-bit variant, providing significant performance gains for workloads with large data sets.

## Key Characteristics

- **256-bit vector registers** (YMM registers on x86).
- **AVX2** instruction set support (Haswell and later, or Zen 1+ on AMD).
- **2× throughput** over the 128-bit variant for vectorizable operations.
- Requires a **modern x86-64 CPU** (2013+).

## Internal Layout

```
256/
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
│   └── lib256.cpp
├── testFiles/
│   ├── ArticleData
│   ├── TestDataBig
│   └── TestDataSmall
└── testProgram/
    ├── CMakeLists.txt
    ├── Source.cpp
    ├── Test256.cpp
    └── Test256_*.cpp
```

## Building

### CMake

```bash
cd 256/src
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Make

```bash
cd 256/src
make
```

---

## API

All 256-bit-specific functions share the same API as the other variants (see the main `README.md` for the full API reference). The `instructionSet` variable will report a value of 8 when AVX2 is detected.

---

## Authors

Maria Pashinska-Gadzheva and Iliya Bouyukliev

## Further Reading

- [ACM Algorithm 1059](https://doi.org/10.1145/3777479) — LinCodeWeightInv library paper
- [calgo.acm.org](https://calgo.acm.org/) — Full library with instruction detection
