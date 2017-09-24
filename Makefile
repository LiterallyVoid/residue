OBJ = src/main.o src/texture.o
EXE = residue

LDFLAGS = -lX11 -lglfw -lGL -lm -lpng

$(EXE): $(OBJ)
	$(CXX) $^ -o $@ $(LDFLAGS)
