#include "window.hpp"
using namespace std;
#include <string>

// Fonction pour initialiser la fenêtre SDL avec un titre, une largeur et une hauteur spécifiés

void init_window(Window* window, int width, int height, string title) {
    // Initialisation de SDL pour la vidéo
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cerr << "Could not initialize SDL2: error " << SDL_GetError() << endl;
    SDL_Quit();
    }
    
    // Affectation de la largeur et de la hauteur de la fenêtre
   
    window -> width = width;
    window -> height = height;
    
    // Création de la fenêtre et du renderer SDL

    int ret = SDL_CreateWindowAndRenderer(width, height, 0, &window -> sdl_window, &window -> sdl_renderer);
    if (ret < 0) {
    cerr << " Could not create SDL window: error " << SDL_GetError() << endl;
    SDL_Quit();
    }

    // Définir le titre de la fenêtre

    SDL_SetWindowTitle(window -> sdl_window, title.c_str());

}

// Fonction pour fermer la fenêtre et nettoyer les ressources SDL


void close_window(Window* window) {
    SDL_DestroyWindow(window -> sdl_window);
    SDL_DestroyRenderer(window -> sdl_renderer);
    SDL_Quit();
}

// Fonction pour effacer la fenêtre en la remplissant avec la couleur de fond définie


void clear_window(Window* window) {
    // Définir la couleur de dessin à partir de la couleur de fond

    SDL_SetRenderDrawColor(window -> sdl_renderer,
                        window -> background.r,
                        window -> background.g,
                        window -> background.b,
                        window -> background.a);
    // Effacer la fenêtre

    SDL_RenderClear(window -> sdl_renderer);
}

// Fonction pour mettre à jour l'affichage de la fenêtre

void refresh_window(Window* window){
    // Présenter le rendu de la fenêtre

    SDL_RenderPresent(window -> sdl_renderer);
}

// Fonction pour définir la couleur de la SDL_Color


void set_color(SDL_Color* dst, int r, int g, int b, int a) {
    dst->r = r;
    dst->g = g;
    dst->b = b;
    dst->a = a;
}

void set_color(SDL_Color* dst, SDL_Color* src) {
    dst->r = src->r;
    dst->g = src->g;
    dst->b = src->b;
    dst->a = src->a;
}

// Fonction pour dessiner un rectangle rempli dans la fenêtre

void draw_fill_rectangle(Window* window, int x, int y, int w, int h) {
    
    // Définir la couleur de dessin à partir de la couleur de premier plan (foreground)

    SDL_SetRenderDrawColor(window -> sdl_renderer,
                            window -> foreground.r,
                            window -> foreground.g,
                            window -> foreground.b,
                            window -> foreground.a);
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    SDL_RenderFillRect(window -> sdl_renderer, &rectangle);
}

