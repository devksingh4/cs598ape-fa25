# 598APE-HW3


## Ablation Studies

All runs below run on the course-provided VMs.

| Description | Commit Hash | Small (s) | Large (s) | Largest (s) |
|-------------|-------------|-----------|-----------|-------------|
| Baseline | c3eded6f04a1d7cd326fdc60910508571ba253a8 | 5.685062 | DNF | DNF |
| Reduce calls to calculateTotalEnergy | 72c945695f88fc05d5d705861131d197d9c0be7e | 0.004845 | 6.094991 | 58.649651 |
| Move to clang++/c++ | 8e955178b6f1a01e05a4607fdbaacea5336d63b6 | 0.004453 | 5.49703 | 52.746704 |
| Cache exponentiation | e4809cac4613fc7c41f00770729002386feed88d | 0.00316 | 4.040908 | 37.596806 |
| Move to wyrand for randomU64 | 5f9c9b0187a99cb404fb48d3c1ed7022cf625832 | 0.002946 | 3.852188 | 37.33894 |
| Call randomU64 one time less, remove the division | 83d8003dff0f6f34eddea58f6d270bd77939f37a | 0.002619 | 3.342784 | 31.718899 |
| Use -Ofast instead of -O3 | 08d0376100bf535cf581806eef67b769b0582f8b | 0.002571 | 3.307072 | 31.577038 

---

This repository contains code for homework 3 of 598APE.

This assignment is relatively simple in comparison to HW1 and HW2 to ensure you have enough time to work on the course project.

In particular, this repository implements a 2D Ising model Monte Carlo simulator (with Metropolis–Hastings algorithm) on an L×L lattice with periodic boundary conditions.

To compile the program run:
```bash
make -j
```

To clean existing build artifacts run:
```bash
make clean
```

This program assumes the following are installed on your machine:
* A working C compiler (gcc is assumed in the Makefile)
* make
* ImageMagick `convert` for PNG output

Usage (after compiling):
```bash
./main.exe <L> <temperature> <steps>
```

In particular, consider speeding up simple run like the following (which runs ~5 seconds on my local laptop under the default setup):
```bash
./main.exe 100 2.269 100000
```

Exact bitwise reproducibility is not required; sanity checks on energy/magnetization bounds must pass. In addition, at the critical temperature (T ≈ 2.269) the energy per spin should approach -1.414 in equilibrium.