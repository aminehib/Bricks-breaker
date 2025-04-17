#include "world.hpp"

#include <fstream>
#include <string>


// Initialise le monde avec une grille w × h remplie de blocs Empty
void init_world(World* world, int w, int h) {
    world->width = w;
    world->height = h;
    world->grid = new Block[w * h];
    
    for (int i = 0; i < w * h; i++) {
        world->grid[i] = Empty;
    }
}

// Libère la mémoire allouée dynamiquement pour la grille
void free_world(World* world) {
    delete[] world->grid;
    world->grid = nullptr; // bonne pratique pour éviter un pointeur sauvage
}


// Retourne le bloc aux coordonnées (x, y), ou Empty si coordonnées invalides
Block read(World* world, int x, int y) {
    if (x < 0 || x >= world->width || y < 0 || y >= world->height) {
        cerr << "Erreur (read) : coordonnées (" << x << ", " << y << ") hors limites." << endl;
        return Empty;
    }
    int index = y * world->width + x;
    return world->grid[index];
}

// Écrit le bloc b aux coordonnées (x, y), ne fait rien si coordonnées invalides
void write(World* world, int x, int y, Block b) {
    if (x < 0 || x >= world->width || y < 0 || y >= world->height) {
        cerr << "Erreur (write) : coordonnées (" << x << ", " << y << ") hors limites." << endl;
        return;
    }
    int index = y * world->width + x;
    world->grid[index] = b;
}

// Affiche la grille du monde en mode texte
void display(World* world) {
    for (int y = 0; y < world->height; y++) {
        for (int x = 0; x < world->width; x++) {
            Block b = read(world, x, y);
            char c;
            switch (b) {
                case Empty:  c = '.'; break;
                case Border: c = '#'; break;
                case Lose:   c = '$'; break;
                case Type1:  c = '1'; break;
                case Type2:  c = '2'; break;
                default:     c = '?'; break;
            }
            cout << c;
        }
        cout << endl;
    }
}

void init_world_from_file(World* world, string filename) {
    ifstream fic(filename);
    
    if (!fic.is_open()) {
        cerr << "Erreur : impossible d’ouvrir le fichier " << filename << endl;
        exit(1);
    }

    int w, h;
    fic >> w >> h;
    fic.ignore(); // ignore le \n après la hauteur

    init_world(world, w, h);

    for (int y = 0; y < h; y++) {
        string ligne;
        getline(fic, ligne);

        for (int x = 0; x < w && x < (int)ligne.length(); x++) {
            char c = ligne[x];
            Block b;
            switch (c) {
                case '.': b = Empty; break;
                case '#': b = Border; break;
                case '$': b = Lose;   break;
                case '1': b = Type1;  break;
                case '2': b = Type2;  break;
                default:
                    cerr << "Caractère inconnu '" << c << "' à (" << x << ", " << y << "), remplacé par Empty." << endl;
                    b = Empty;
            }
            write(world, x, y, b);
        }
    }

    fic.close();
}