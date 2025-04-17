#include <iostream>
#include "window.hpp"

using namespace std;

void draw_grid(Window* window, int grid_size, int cell_size, int offset_x, int offset_y) {
    // S'assurer que la couleur utilisée est bien noire
    SDL_SetRenderDrawColor(window->sdl_renderer, 0, 0, 0, 255);

    // Dessiner les lignes horizontales
    for (int i = 0; i <= grid_size; i++) {
        int y = offset_y + i * cell_size;
        SDL_RenderDrawLine(window->sdl_renderer, offset_x, y, offset_x + grid_size * cell_size, y);
    }

    // Dessiner les lignes verticales
    for (int j = 0; j <= grid_size; j++) {
        int x = offset_x + j * cell_size;
        SDL_RenderDrawLine(window->sdl_renderer, x, offset_y, x, offset_y + grid_size * cell_size);
    }

    // Rafraîchir l'affichage pour appliquer la grille noire
    SDL_RenderPresent(window->sdl_renderer);
}


void echiquier(Window* window, int rows, int cols, SDL_Color color1, SDL_Color color2) {
    int cell_width = window->width / cols;  // Largeur des cases
    int cell_height = window->height / rows; // Hauteur des cases

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Alterner les couleurs entre color1 et color2
            if ((i + j) % 2 == 0) {
                set_color(&window->foreground, &color1);
            } else {
                set_color(&window->foreground, &color2);
            }
            draw_fill_rectangle(window, j * cell_width, i * cell_height, cell_width, cell_height);
        }
    }
}

void dessine_pentominos(Window* window) {
    int grid_size = 5; // Grille 5x5
    int cell_size = min(window->width / grid_size, window->height / grid_size); // Garde les cases carrées

    // Définition des couleurs
    SDL_Color violet = {255, 0, 255, 255};
    SDL_Color orange = {255, 165, 0, 255};
    SDL_Color blue = {0, 0, 255, 255};
    SDL_Color green = {0, 128, 0, 255};
    SDL_Color pink = {255, 0, 128, 255};

    // Matrice de la grille corrigée
    SDL_Color grid[5][5] = {
        {violet, violet, orange, blue, blue},
        {violet, orange, orange, orange, blue},
        {violet, violet, orange, pink, blue},
        {green, green, green, pink, blue},
        {green, green, pink, pink, pink}
    };

    // Centrer la grille
    int offset_x = (window->width - (grid_size * cell_size)) / 2;
    int offset_y = (window->height - (grid_size * cell_size)) / 2;

    // Dessin des cases
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            set_color(&window->foreground, &grid[i][j]);
            draw_fill_rectangle(window, offset_x + j * cell_size, offset_y + i * cell_size, cell_size, cell_size);
        }
    }

    // Dessiner la grille noire pour bien séparer les cases
    draw_grid(window, grid_size, cell_size, offset_x, offset_y);
}



int main(int argc, char** argv) {
    Window window;
    init_window(&window, 800, 600, "Chessboard and Pentominos");

    SDL_Color blue = {0, 0, 255, 255};   // Bleu
    SDL_Color red = {255, 0, 0, 255};    // Rouge

    clear_window(&window);
    echiquier(&window, 8, 10, blue, red); // 8 lignes, 10 colonnes
    refresh_window(&window);
    SDL_Delay(4000);

    clear_window(&window);
    dessine_pentominos(&window);
    refresh_window(&window);
    SDL_Delay(4000);

    close_window(&window);
}

