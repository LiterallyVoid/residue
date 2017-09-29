OBJ = src/main.o src/texture.o src/shader.o src/file.o src/chunk.o src/mesh.o src/world.o
EXE = residue

CXXFLAGS = -g -Og
LDFLAGS = -lX11 -lglfw -lGL -lm -lpng -lGLU -lnoise

$(EXE): $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)
