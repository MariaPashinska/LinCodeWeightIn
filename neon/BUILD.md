# neon — Build Targets and Test Suite

## Library

| Target | Type | Source Files | Compiler Flags |
|--------|------|-------------|----------------|
| `v1.3` | Static library (`.a`) | `LinCodeWeightInv.cpp`, `Polynomials.cpp`, `ReadWrite.cpp`, `lib_neon.cpp`, `Data.cpp`, `testDriver.cpp` | `-march=native` (GCC/Clang on ARM) |



Variant-specific header: `lib_neon.h`

---

## Executable Targets

### Test-UI

- **Source:** `Source.cpp`
- **Purpose:** Interactive command-line interface for end users.
- **Features:**
  - Read generator matrices from a file or generate a random linear code.
  - Choose among 6 operations:
    1. Calculate weight spectrum
    2. Calculate minimum distance
    3. Search for a codeword with weight less than W
    4. Search for a codeword with weight equal to W
    5. Count codewords with weight less than W
    6. Count codewords with weight equal to W
  - Option to write found codewords to a file.
  - Option to run the automated **Test Driver** (see below).

### test128_WeightDistribution

- **Source:** `Test128.cpp`
- **Purpose:** Tests the weight distribution calculation using the ARM NEON backend.
- **Calls:** `test_driveSSE(1)` — mode 1 = weight distribution.

### test128_MinimumDistance

- **Source:** `Test128_MinimumDistance.cpp`
- **Purpose:** Tests the minimum distance calculation using the ARM NEON backend.
- **Calls:** `test_driveSSE(2)` — mode 2 = minimum distance.

### test128_SearchEqual

- **Source:** `Test128_SearchEqual.cpp`
- **Purpose:** Tests searching for a codeword with weight equal to a given value using the ARM NEON backend.
- **Calls:** `test_driveSSE(3)` — mode 3 = search equal weight.

### test128_SearchLessThan

- **Source:** `Test128_SearchLessThan.cpp`
- **Purpose:** Tests searching for a codeword with weight less than a given value using the ARM NEON backend.
- **Calls:** `test_driveSSE(4)` — mode 4 = search less than weight.

### test128_CountEqual

- **Source:** `Test128_CountEqual.cpp`
- **Purpose:** Tests counting codewords with weight equal to a given value using the ARM NEON backend.
- **Calls:** `test_driveSSE(5)` — mode 5 = count equal weight.

### test128_CountLessThan

- **Source:** `Test128_CountLessThan.cpp`
- **Purpose:** Tests counting codewords with weight less than a given value using the ARM NEON backend.
- **Calls:** `test_driveSSE(6)` — mode 6 = count less than weight.

---

## Test Drive Function

The **Test Driver** (`testDrive`) is the comprehensive correctness and performance testing suite for the library.

### How it works

When invoked (via the Test-UI menu option 3, or directly through the `test_drive()` function), it:


1. **Runs all six test modes** using data from the reference manuscript:
   - Mode 1 — Weight distribution
   - Mode 2 — Minimum distance
   - Mode 3 — Search for codeword with weight equal to W
   - Mode 4 — Search for codeword with weight less than W
   - Mode 5 — Count codewords with weight equal to W
   - Mode 6 — Count codewords with weight less than W
2. **Measures and reports** average execution times and total computational time for each mode.
3. **Validates correctness** against known reference results.
4. **Writes results** to the `Results` file.
5. **Writes errors** to `error.txt` if any computation produces incorrect results.

### Per-variant test functions

| Function | Backend |
|----------|---------|
| `test_driveScalar(int mode)` | Plain C++, no SIMD |
| `test_driveSSE(int mode)` | 128-bit SSE / ARM NEON |
| `test_driveAVX(int mode)` | 256-bit AVX2 |
| `test_driveAVX512(int mode)` | 512-bit AVX-512 |

Each function accepts a `mode` parameter (1–6) to select which library function to test.