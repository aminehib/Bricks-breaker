#ifndef WORLD_HPP
#define WORLD_HPP

#include <SDL2/SDL.h>


#include <iostream>

using namespace std;

// Types de blocs dans le monde
enum Block {
    Empty,   // case vide
    Border,  // bloc incassable (gris)
    Type1,   // bloc cassable de type 1 (rouge)
    Type2,   // bloc cassable de type 2 (vert)
    Lose     // zone de défaite (bas de l’écran)
};

// Structure représentant le monde
struct World {
    int width;      // largeur de la grille
    int height;     // hauteur de la grille
    Block* grid;    // grille dynamique de blocs
};

// Fonctions associées

void init_world(World* world, int w, int h);  // initialisation
void free_world(World* world);                // libération

// Accès en lecture à un bloc de la grille
Block read(World* world, int x, int y);

// Accès en écriture à un bloc de la grille
void write(World* world, int x, int y, Block b);

void display(World* world);

void init_world_from_file(World* world, string filename);



#endif
