EXE = test
CPP = g++
SDL_INC = `sdl2-config --cflags`
SDL_LIB = `sdl2-config --libs`
CFLAGS = -O3 -Wall $(SDL_INC)
LIBS = $(SDL_LIB) -lSDL2_ttf -lSDL2_image

SRC = src/main.cpp src/world.cpp src/window.cpp src/game.cpp
OBJ = obj/main.o obj/world.o obj/window.o obj/game.o

ALL: $(EXE)

# Règle générique pour tous sauf main.cpp
obj/%.o: src/%.cpp src/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@

# Règle spécifique pour main.cpp (pas de .hpp requis)
obj/main.o: src/main.cpp
	$(CPP) $(CFLAGS) -c $< -o $@

# Création de l'exécutable
$(EXE): $(OBJ)
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)

# Nettoyage
clean:
	-$(RM) obj/*.o $(EXE)
