# neon — ARM NEON SIMD

## Library

| Target | Type | Variant Source | Compiler Flags |
|--------|------|---------------|----------------|
| `v1.3` | Static library (`.a`) | `LinCodeWeightInv.cpp`, `Polynomials.cpp`, `ReadWrite.cpp`, `lib_neon.cpp`, `Data.cpp`, `testDriver.cpp` | `-march=native` (GCC/Clang on ARM) |

Variant-specific header: `include/lib_neon.h`

---

## Purpose

This variant targets **ARM64 / AArch64** platforms using **NEON SIMD** instructions. It brings SIMD acceleration to  Apple Silicon and other ARM-based systems.

## Key Characteristics

- **ARM NEON** SIMD instructions (128-bit wide vector registers).
- **ARM64 / AArch64** architecture support.
- **Universal ARM compatibility** — works across ARMv8 and later.

## Internal Layout

```
neon/
├── Src/
│   ├── CMakeLists.txt
│   ├── BUILD.md
│   ├── Makefile
│   ├── include/
│   │   ├── LinCodeWeightInv.h
│   │   ├── Data.h
│   │   ├── DataManagement.h
│   │   ├── Polynomials.h
│   │   ├── ReadWrite.h
│   │   ├── testDriver.h
│   │   └── lib_neon.h
│   ├── src/
│   │   ├── CMakeLists.txt
│   │   ├── LinCodeWeightInv.cpp
│   │   ├── Data.cpp
│   │   ├── DataManagement.cpp
│   │   ├── Polynomials.cpp
│   │   ├── ReadWrite.cpp
│   │   ├── testDriver.cpp
│   │   └── lib_neon.cpp
│   ├── testFiles/
│   │   ├── ArticleData
│   │   ├── TestDataBig
│   │   └── TestDataSmall
│   └── testProgram/
│       ├── CMakeLists.txt
│       ├── Source.cpp
│       ├── Test128.cpp
│       └── Test128_*.cpp
└── README.md
```

## Building

### CMake

```bash
cd neon/Src
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Make

```bash
cd neon/Src
make
```

---

## API

All NEON-specific functions share the same API as the other variants (see the main `README.md` for the full API reference). The `instructionSet` variable will report the detected ARM NEON capability.

---

## Authors

Maria Pashinska-Gadzheva and Iliya Bouyukliev

## Further Reading

- [ACM Algorithm 1059](https://doi.org/10.1145/3777479) — LinCodeWeightInv library paper
- [calgo.acm.org](https://calgo.acm.org/) — Full library with instruction detection
