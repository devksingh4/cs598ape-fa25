FUNC := clang++
OBJ_DIR := ./bin/
FLAGS := -std=c++20 -Ofast -lm -g -Werror -ftree-vectorize -march=native -flto -funroll-loops

all:
	$(FUNC) ./main.cpp -o ./main.exe $(FLAGS)

clean:
	rm -f ./*.exe