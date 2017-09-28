OBJ = src/main.o src/texture.o src/shader.o src/file.o src/chunk.o src/mesh.o
EXE = residue

LDFLAGS = -lX11 -lglfw -lGL -lm -lpng -lGLU

$(EXE): $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)
