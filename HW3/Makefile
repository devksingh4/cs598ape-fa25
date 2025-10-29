FUNC := clang++
OBJ_DIR := ./bin/
FLAGS := -std=c++20 -O3 -lm -g -Werror -ffast-math -ftree-vectorize -march=native -flto -funroll-loops

all:
	$(FUNC) ./main.cpp -o ./main.exe $(FLAGS)

clean:
	rm -f ./*.exe