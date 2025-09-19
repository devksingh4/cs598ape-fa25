FUNC := g++
output := -o 
copt := -c 
SRC_DIR := ./
OBJ_DIR := ./
FLAGS := -O3 -lm -g -Werror -ftree-vectorize -march=native -flto -fno-math-errno -fno-trapping-math

CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix $(OBJ_DIR),$(notdir $(CPP_FILES:.cpp=.obj)))

TEXTURE_CPP_FILES := $(wildcard Textures/*.cpp)m
TEXTURE_OBJ_FILES := $(addprefix $(OBJ_DIR)Textures/,$(notdir $(TEXTURE_CPP_FILES:.cpp=.obj)))

all: $(SRC_DIR)texture $(OBJ_FILES)

texture:
	cd $(SRC_DIR)Textures && make

$(OBJ_DIR)vector.obj: $(SRC_DIR)vector.cpp $(SRC_DIR)vector.h $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)vector.obj $(copt) $(SRC_DIR)vector.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)mandel.obj: $(SRC_DIR)mandel.cpp $(SRC_DIR)mandel.h $(OBJ_DIR)box.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)mandel.obj $(copt) $(SRC_DIR)mandel.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)camera.obj: $(SRC_DIR)camera.cpp $(SRC_DIR)camera.h $(OBJ_DIR)vector.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)camera.obj $(copt) $(SRC_DIR)camera.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)light.obj: $(SRC_DIR)light.cpp $(SRC_DIR)light.h $(OBJ_DIR)camera.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)light.obj $(copt) $(SRC_DIR)light.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)shape.obj: $(SRC_DIR)shape.cpp $(SRC_DIR)shape.h $(OBJ_DIR)light.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)shape.obj $(copt) $(SRC_DIR)shape.cpp $(FLAGS)

$(OBJ_DIR)sphere.obj: $(SRC_DIR)sphere.cpp $(SRC_DIR)sphere.h $(OBJ_DIR)shape.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)sphere.obj $(copt) $(SRC_DIR)sphere.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)plane.obj: $(SRC_DIR)plane.cpp $(SRC_DIR)plane.h $(OBJ_DIR)shape.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)plane.obj $(copt) $(SRC_DIR)plane.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)mesh.obj: $(SRC_DIR)mesh.cpp $(SRC_DIR)mesh.h $(OBJ_DIR)shape.obj  $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)mesh.obj $(copt) $(SRC_DIR)mesh.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)hyperboloid.obj: $(SRC_DIR)hyperboloid.cpp $(SRC_DIR)hyperboloid.h $(OBJ_DIR)shape.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)hyperboloid.obj $(copt) $(SRC_DIR)hyperboloid.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)pictplane.obj: $(SRC_DIR)pictplane.cpp $(SRC_DIR)pictplane.h $(OBJ_DIR)plane.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)pictplane.obj $(copt) $(SRC_DIR)pictplane.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)box.obj: $(SRC_DIR)box.cpp $(SRC_DIR)box.h $(OBJ_DIR)plane.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)box.obj $(copt) $(SRC_DIR)box.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)triangle.obj: $(SRC_DIR)triangle.cpp $(SRC_DIR)triangle.h $(OBJ_DIR)plane.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)triangle.obj $(copt) $(SRC_DIR)triangle.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)pictbox.obj: $(SRC_DIR)pictbox.cpp $(SRC_DIR)pictbox.h $(OBJ_DIR)box.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)pictbox.obj $(copt) $(SRC_DIR)pictbox.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)disk.obj: $(SRC_DIR)disk.cpp $(SRC_DIR)disk.h $(OBJ_DIR)/plane.obj $(OBJ_DIR)/constants.obj
	$(FUNC) $(output)$(OBJ_DIR)disk.obj $(copt) $(SRC_DIR)disk.cpp $(FLAGS) -ffast-math

$(OBJ_DIR)constants.obj: $(SRC_DIR)constants.h
	$(FUNC) $(output)$(OBJ_DIR)constants.obj $(copt) $(FLAGS) -ffast-math

clean:
	cd Textures && make clean
	rm -f $(OBJ_DIR)*.obj
