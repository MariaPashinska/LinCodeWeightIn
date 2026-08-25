# LinCodeWeightInv — Linear Code Weight Invariants Library

> **Authors:** Maria Pashinska-Gadzheva and Iliya Bouyukliev  
> **Affiliation:** Institute of Mathematics and Informatics, Bulgarian Academy of Sciences

A high-performance C/C++ library for fast computation of the weight distribution, minimum distance, and other weight invariants of linear codes over finite fields. The library leverages **Extended Vector Registers** (SSE4.1, AVX2, AVX-512, and ARM NEON) to deliver optimized performance across x86 and ARM architectures.

## 🎯 Key Features

- **Weight Distribution** — Compute the full weight spectrum `(A₀, A₁, ..., Aₙ)` of a linear code, where `Aᵢ` is the number of codewords of weight `i`.
- **Minimum Distance** — Calculate the minimum Hamming distance `d` of a linear code.
- **Codeword Search** — Find codewords with weight less than or equal to a given threshold.
- **Codeword Counting** — Count the number of codewords with weight less than or equal to a given value.
- **Multi-Finite-Field Support** — Works with binary fields GF(2), prime fields GF(p), and composite fields GF(pᵐ) for `Q ≤ 64`.
- **Dual Field Element Representation** — Supports both **polynomial** and **multiplicative** representation of finite field elements.
- **SIMD-Accelerated** — Six optimized variants targeting different CPU instruction sets for maximum performance.
- **Cross-Platform** — Tested on Windows, Linux, and macOS across Intel, AMD, and Apple Silicon platforms.
- **Build Systems** — Both CMake (≥3.16) and GNU Make build configurations provided.
- **Built-in Testing** — Includes a `testDriver` for correctness verification and runtime benchmarking across all instruction set variants.

## 📖 Mathematical Background

A linear `[n, k]_q` code is a `k`-dimensional subspace of the `n`-dimensional vector space over the Galois field GF(`q`). The parameters `n` and `k` are called the **length** and **dimension** of the code, respectively, and the vectors in the code are called **codewords**. For an arbitrary codeword `v`, its Hamming weight `wt(v)` is defined as the number of its non-zero coordinates. The **weight distribution** `(A₀, A₁, ..., Aₙ)` records the number of codewords of each weight `i`.

The library uses **Gray code** traversal for efficient enumeration of field elements, with precomputed transition sequences for fields with characteristics 2, 3, 5, and 7.

## 📁 Directory Structure

```
lib divided/
├── README.md              ← You are here
│
├── scalar/                ← Plain C++ (no SIMD/vectorization)
├── 128/                   ← 128-bit SIMD (SSE2/SSE4.1)
├── 256/                   ← 256-bit SIMD (AVX2)
├── 512/                   ← 512-bit SIMD (AVX-512)
└── neon/             ← ARM NEON SIMD (ARM64)
```

### Supported Finite Fields

| Field | Supported | Representation |
|-------|-----------|----------------|
| GF(2) | ✅ | Bitwise |
| GF(4) | ✅ | Polynomial / Multiplicative |
| GF(8) | ✅ | Polynomial / Multiplicative |
| GF(9) | ✅ | Polynomial / Multiplicative |
| GF(16) | ✅ | Polynomial / Multiplicative |
| GF(25) | ✅ | Polynomial / Multiplicative |
| GF(27) | ✅ | Polynomial / Multiplicative |
| GF(32) | ✅ | Polynomial / Multiplicative |
| GF(49) | ✅ | Polynomial / Multiplicative |
| GF(64) | ✅ | Polynomial / Multiplicative |

For composite fields GF(`pᵐ`), primitive polynomials are pre-initialized (see `usersManual.pdf` for the complete list of primitive polynomials used).

---

## 📦 Subdirectory Details

```
lib divided/
├── README.md              ← You are here
│
├── scalar/                ← Plain C++ (no SIMD/vectorization)
├── 128/                   ← 128-bit SIMD (SSE2/SSE4.1)
├── 256/                   ← 256-bit SIMD (AVX2)
├── 512/                   ← 512-bit SIMD (AVX-512)
└── neon/             ← ARM NEON SIMD (ARM64)
```

---

## 📦 Subdirectory Details

Each subdirectory contains a complete, self-contained C++ project (version **1.3**) with a single `src/` folder:

| Subdirectory | Instruction Set | Build Systems | Notes |
|-------------|-----------------|---------------|-------|
| **`scalar/`** | None (plain C++) | CMake, Makefile | Baseline implementation; no extended registers |
| **`128/`** | 128-bit SSE | CMake, Makefile | Targets SSE2 / SSE4.1 capable CPUs |
| **`256/`** | 256-bit AVX2 | CMake, Makefile | Targets AVX2-capable CPUs (Haswell+) |
| **`512/`** | 512-bit AVX-512 | CMake, Makefile | Targets AVX-512-capable CPUs (Skylake-X/IZ+) |
| **`neon/`** | ARM NEON | CMake, Makefile | For ARM64 / mobile platforms |

### Common internal layout (per subdirectory)

```
<subdir>/
└── src/
    ├── CMakeLists.txt     ← CMake build configuration
    ├── Makefile           ← GNU Make build file
    ├── include/           ← Public headers
    │   ├── LinCodeWeightInv.h   ← Main API header
    │   ├── Data.h
    │   ├── DataManagement.h
    │   ├── Polynomials.h
    │   ├── ReadWrite.h
    │   ├── testDriver.h
    │   └── lib<variant>.h       ← Variant-specific header (e.g. lib128.h, lib_neon.h)
    ├── src/               ← C++ source files
    │   ├── LinCodeWeightInv.cpp
    │   ├── Data.cpp
    │   ├── DataManagement.cpp
    │   ├── Polynomials.cpp
    │   ├── ReadWrite.cpp
    │   ├── testDriver.cpp
    │   └── lib<variant>.cpp     ← Variant-specific source (e.g. lib128.cpp, lib_neon.cpp)
    ├── testFiles/         ← Test input data
    └── testProgram/       ← Test harness
```

---

## 🔧 Building

### CMake

```bash
cd <subdir>/src
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```

### Make

```bash
cd <subdir>/src
make
```

---

## 📖 API Overview

The main header is `include/LinCodeWeightInv.h`. All functions write results to the global array `weights[]` unless noted otherwise.

### Weight Distribution

| Function | Description |
|----------|-------------|
| `calculateWeightDistribution(int** generatorMatrix, int N, int K, int Q, bool multiplicativeForm)` | Compute the full weight spectrum from a given generator matrix |
| `calculateWeightDistribution(int N, int K, int Q)` | Compute the weight spectrum of a randomly generated linear code |
| `calculateWeightDistribution(char* generatorMatrixFile)` | Compute weight distribution for generator matrices read from a file (output: `Weight_dis.txt`) |

### Minimum Distance

| Function | Description |
|----------|-------------|
| `min_dis(int** generatorMatrix, int N, int K, int Q, bool multiplicativeForm)` | Calculate the minimum Hamming distance from a given generator matrix |
| `min_dis(int N, int K, int Q)` | Calculate the minimum distance of a randomly generated linear code |
| `min_dis(char* generatorMatrixFile)` | Calculate minimum distance for matrices from a file (output: `min_distance.txt`) |

### Find Codeword — Weight Less Than W

| Function | Description |
|----------|-------------|
| `find_word_less_than_fixed_weight(int** generatorMatrix, int N, int K, int Q, int W, bool multiplicativeForm)` | Search for a codeword with weight < W from a given generator matrix |
| `find_word_less_than_fixed_weight(int N, int K, int Q, int W)` | Search for a codeword with weight < W from a randomly generated code |
| `find_word_less_than_fixed_weight(char* generatorMatrixFile, unsigned long long int W)` | Search for codewords with weight < W from matrices in a file (output: `find_less_than.txt`) |

### Find Codeword — Weight Equal To W

| Function | Description |
|----------|-------------|
| `find_word_equal_to_fixed_weight(int** generatorMatrix, int N, int K, int Q, int W, bool multiplicativeForm)` | Search for a codeword with weight == W from a given generator matrix |
| `find_word_equal_to_fixed_weight(int N, int K, int Q, int W)` | Search for a codeword with weight == W from a randomly generated code |
| `find_word_equal_to_fixed_weight(char* generatorMatrixFile, unsigned long long int w_searched)` | Search for codewords with weight == W from matrices in a file (output: `find_equal.txt`) |

### Count Codewords — Weight Less Than W

| Function | Description |
|----------|-------------|
| `calculate_number_of_words_less_than_fixed_w(int** generatorMatrix, int N, int K, int Q, int w, bool write, bool multiplicativeForm)` | Count codewords with weight < W from a given generator matrix |
| `calculate_number_of_words_less_than_fixed_w(int N, int K, int Q, int w, bool write)` | Count codewords with weight < W from a randomly generated code |
| `calculate_number_of_words_less_than_fixed_w(char* generatorMatrixFile, unsigned long long int w_searched, bool write)` | Count codewords with weight < W from matrices in a file (output: `count_less_than.txt`) |

### Count Codewords — Weight Equal To W

| Function | Description |
|----------|-------------|
| `calculate_number_of_words_with_fixed_w(int** generatorMatrix, int N, int K, int Q, int w, bool write, bool multiplicativeForm)` | Count codewords with weight == W from a given generator matrix |
| `calculate_number_of_words_with_fixed_w(int N, int K, int Q, int w, bool write)` | Count codewords with weight == W from a randomly generated code |
| `calculate_number_of_words_with_fixed_w(char* generatorMatrixFile, unsigned long long int w_searched, bool write)` | Count codewords with weight == W from matrices in a file (output: `count_equal.txt`) |


## ⚙️ Technical Details

- **Language:** C++
- **CMake minimum version:** 3.16
- **Default build type:** Release
- **Output:** Static library + test executables
- **Input format:** Generator matrices provided as 2D arrays, files, or generated randomly
- **Field support:** Binary (GF(2)), prime and composite finite fields GF(Q) with multiplicative or polynomial representation for Q<=64

## 🖥️ Sample Program & Testing

Each subdirectory includes a **Sample program** (`testProgram/`) that provides a simple interactive interface for all library functionalities:

1. **File-based input** — Load a generator matrix from a file and perform calculations.
2. **Random code generation** — Generate a random linear code with user-specified parameters `(n, k, q)` and perform calculations.
3. **Test Driver** — Run correctness and runtime tests across all functions and instruction set variants.

### Input File Format

Generator matrices in input files can use two element representations:
- **Decimal representation** — Rows starting with `?` use decimal indices of field elements.
- **Multiplicative representation** — Rows starting with `!` use the index in multiplicative (exponent) form.

After the matrix header, parameters `k`, `n`, `q` are provided, followed by the generator matrix rows.

### Test Driver

The `testDriver` reads pre-generated test data files (`TestDataSmall`, `TestDataBig`) containing:
- Code parameters `(n, k, q)`
- Generator matrices
- Pre-computed weight distributions (via Gray code reference software)

It verifies correctness of all six core functions and measures average execution time across 100 randomly generated codes per parameter set. Users can select which instruction set to test: SSE4.1, AVX2, AVX-512, or scalar (no vectorization).

---

## 🖥️ Tested Platforms

The library has been tested on the following platforms:

| CPU | OS | Instruction Set | Compiler | Build System / IDE |
|-----|----|----------------|----------|-------------------|
| Intel Xeon Gold 5118 @2.36GHz | Red Hat Enterprise 7.9 | AVX-512 F/BW | gcc 9.2 | Makefile |
| Intel Core i5-13600K @3.5GHz | Windows 11 Pro | AVX2 | gcc 10.3, msvc 19.37 | CodeBlocks 20.03, VS Community 17 |
| Intel Core i5-1035G @1.0GHz | Windows 10 Pro | AVX-512 F/BW / VPOPCNTDQ | gcc 8.1, msvc 19.29 | CodeBlocks 20.03, VS Community 16 |
| Intel Xeon E5-2640 @2.5GHz | Ubuntu 18.04 | SSE4.2 | gcc 7.5 | Makefile, CodeBlocks 20.03 |
| AMD Ryzen 5 7600 @3.8GHz | Windows 11 Home | AVX-512 F/BW / VPOPCNTDQ | gcc 8.1, msvc 19.39 | CodeBlocks 20.03, VS Community 17 |
| Apple M1 @3.2 GHz | macOS Sonoma 14.1.2 | NEON | clang 15.0.0 | Xcode 15.0.2 |
| Cortex-A76 | Ubuntu Server 24.04 (arm64) | NEON | clang 18.1.3 | Makefile |

---

## 📚 Further resources

- The full library with instruction detection is available at https://calgo.acm.org/ (Algorithm 1059: LinCodeWeightInv-Library for Computing the Weight Distribution of Linear Codes over Finite Fields)
- The  algorithms and optimization techniques are presented in full in the accompanying paper: Maria Pashinska-Gadzheva and Iliya Bouyukliev. 2025. Algorithm 1059: LinCodeWeightInv—Library for Computing the Weight Distribution of Linear Codes over Finite Fields. ACM Trans. Math. Softw. 51, 4, Article 27 https://doi.org/10.1145/3777479

---
