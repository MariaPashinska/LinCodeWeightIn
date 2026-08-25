# 512 — 512-bit SIMD (AVX-512)

## Library

| Target | Type | Variant Source | Compiler Flags |
|--------|------|---------------|----------------|
| `v1.3` | Static library (`.a`) | `LinCodeWeightInv.cpp`, `Polynomials.cpp`, `ReadWrite.cpp`, `lib512.cpp`, `Data.cpp`, `testDriver.cpp` | `-march=native -mavx512vpopcntdq` (GCC/Clang) / `/arch:AVX512` (MSVC) |

Variant-specific header: `include/lib512.h`

---

## Purpose

This variant targets CPUs with **512-bit SIMD** capabilities (AVX-512), including the **AVX-512 VPOPCNT DQ** extension for population count operations. It provides the highest parallel throughput of all x86 variants, processing up to 16 bytes (popcount) or 8 double-words per instruction.

## Key Characteristics

- **512-bit vector registers** (ZMM registers on x86).
- **AVX-512** + **VPOPCNTDQ** instruction set support (Skylake-X/W, Icelake, or newer).
- **Definition of `AVX512POCNT_MANUAL=1`** — enables manual popcount intrinsics.
- **Maximum throughput** — up to 4× the scalar variant for vectorizable operations.
- Requires a **very modern x86-64 CPU** (2017+).

## Internal Layout

```
512/
├── CMakeLists.txt
├── Makefile
├── include/
│   ├── LinCodeWeightInv.h
│   ├── Data.h
│   ├── DataManagement.h
│   ├── Polynomials.h
│   ├── ReadWrite.h
│   ├── testDriver.h
│   └── lib512.h
├── src/
│   ├── CMakeLists.txt
│   ├── LinCodeWeightInv.cpp
│   ├── Data.cpp
│   ├── DataManagement.cpp
│   ├── Polynomials.cpp
│   ├── ReadWrite.cpp
│   ├── testDriver.cpp
│   └── lib512.cpp
├── testFiles/
│   ├── ArticleData
│   ├── TestDataBig
│   └── TestDataSmall
└── testProgram/
    ├── CMakeLists.txt
    ├── Source.cpp
    ├── Test512.cpp
    └── Test512_*.cpp
```

## Building

### CMake

```bash
cd 512/src
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Make

```bash
cd 512/src
make
```

---

## API

All 512-bit-specific functions share the same API as the other variants (see the main `README.md` for the full API reference). The `instructionSet` variable will report a value of 11 when AVX-512 VPOPCNTDQ is detected.

---

## Authors

Maria Pashinska-Gadzheva and Iliya Bouyukliev

## Further Reading

- [ACM Algorithm 1059](https://doi.org/10.1145/3777479) — LinCodeWeightInv library paper
- [calgo.acm.org](https://calgo.acm.org/) — Full library with instruction detection
