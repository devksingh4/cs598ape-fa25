#!/bin/bash
make bench_matmul.exe
time ./bench_matmul.exe 0 16
time ./bench_matmul.exe 1 32
make bench_bw.exe
time ./bench_bw.exe inputs/bird.jpg
make bench_sobel.exe
time ./bench_sobel.exe inputs/bird.jpg

diff output/original.png output/base-outputs/original_base.png
diff output/fhe_grayscale.png output/base-outputs/fhe_grayscale_base.png
diff output/plaintext_grayscale.png output/base-outputs/plaintext_grayscale_base.png
diff output/sobel_fhe.png output/base-outputs/sobel_fhe_base.png
diff output/sobel_plain.png output/base-outputs/sobel_plain_base.png
diff output/grayscale.png output/base-outputs/grayscale_base.png