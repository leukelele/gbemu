# gbemu

A Game Boy emulator written in C.

## Building and running

You can build from the repo root without `cd`-ing into `build/`, using CMake's
`-S` (source dir) and `-B` (build dir) flags:

```bash
cmake -S . -B build     # configure (only needed once, or after CMakeLists.txt changes)
cmake --build build     # builds the 'gbemu' emulator and 'tests' executables
./build/gbemu           # run the emulator
./build/tests           # run the Unity test suite directly
# or:
ctest --test-dir build  # run tests via CTest
```

Alternatively, from inside `build/`:

```bash
cd build
cmake --build .
./gbemu
./tests
# or:
ctest
```
