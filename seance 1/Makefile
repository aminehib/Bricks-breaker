EXE = test
CPP = g++
SDL_INC = `sdl2-config --cflags`
SDL_LIB = `sdl2-config --libs`
CFLAGS = -O3 -Wall $(SDL_INC)
LIBS = $(SDL_LIB)

ALL = $(EXE)

obj/%.o: src/%.cpp src/%.hpp
	$(CPP) $(CFLAGS) -c $< -o $@  
	
$(EXE): obj/window.o src/main.cpp
	$(CPP) $(CFLAGS) $^ -o $@ $(LIBS)  

clean:
	-$(RM) obj/*.o $(EXE) 
