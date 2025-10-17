CC := g++
CFLAGS := -std=c++20 -O3 -lm -g -Werror -ffast-math -ftree-vectorize -march=native -flto -funroll-loops
OBJ_DIR := ./bin/

C_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix $(OBJ_DIR),$(notdir $(C_FILES:.cpp=.o)))

all: $(OBJ_DIR) $(OBJ_FILES)
	$(CC) ./main.cpp -o ./main.exe $(OBJ_FILES) $(CFLAGS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: src/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

bench_matmul.exe: $(OBJ_DIR) $(OBJ_FILES) ./benchmark/bench_matmul.cpp
	$(CC) ./benchmark/bench_matmul.cpp -o $@ $(OBJ_FILES) $(CFLAGS)

bench_bw.exe: $(OBJ_DIR) $(OBJ_FILES) ./benchmark/bench_bw.cpp
	$(CC) ./benchmark/bench_bw.cpp -o $@ $(OBJ_FILES) $(CFLAGS)

bench_sobel.exe: $(OBJ_DIR) $(OBJ_FILES) ./benchmark/bench_sobel.cpp
	$(CC) ./benchmark/bench_sobel.cpp -o $@ $(OBJ_FILES) $(CFLAGS)

clean:
	rm -f ./*.exe
	rm -f ./*.o
	rm -rf $(OBJ_DIR)
