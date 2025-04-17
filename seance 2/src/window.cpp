#include "window.hpp"
using namespace std;
#include <string>

void init_window(Window* window, int width, int height, string title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cerr << "Could not initialize SDL2: error " << SDL_GetError() << endl;
    SDL_Quit();
    }
    
    window -> width = width;
    window -> height = height;

    int ret = SDL_CreateWindowAndRenderer(width, height, 0, &window -> sdl_window, &window -> sdl_renderer);
    if (ret < 0) {
    cerr << " Could not create SDL window: error " << SDL_GetError() << endl;
    SDL_Quit();
    }

    SDL_SetWindowTitle(window -> sdl_window, title.c_str());

    // Initialise SDL_TTF for TTF font rendering
    if (TTF_Init() == -1){
        cout << "Could not initialize SDL_TTF: error " << TTF_GetError() << endl;
        SDL_Quit();
    }

    // Spécifie la police
    window->sdl_font = TTF_OpenFont("VeraMono.ttf", 20);
    if (window->sdl_font == NULL) {
        cout << "Could not load font: error " << TTF_GetError() << endl;
        SDL_Quit();
    }


}

void close_window(Window* window) {
    SDL_DestroyWindow(window -> sdl_window);
    SDL_DestroyRenderer(window -> sdl_renderer);
    SDL_Quit();
}

void clear_window(Window* window) {
    SDL_SetRenderDrawColor(window -> sdl_renderer,
                        window -> background.r,
                        window -> background.g,
                        window -> background.b,
                        window -> background.a);
    SDL_RenderClear(window -> sdl_renderer);
}

void refresh_window(Window* window){
    SDL_RenderPresent(window -> sdl_renderer);
}

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

void draw_fill_rectangle(Window* window, int x, int y, int w, int h) {
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

//seance 2

SDL_Texture* load_image(Window* window, string str) {
    SDL_Surface* surface = IMG_Load(str.c_str());
    if (surface == nullptr) {
        cerr << "Erreur SDL_Image : " << IMG_GetError() << endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
        cerr << "Erreur lors de la creation d'une texture à partir d'une surface" << endl;
        return nullptr;
    }

    return texture;
}

void draw_texture(Window* window, SDL_Texture* texture, int x, int y, int w, int h) {
    SDL_Rect box;
    box.x = x;
    box.y = y;
    box.w = w;
    box.h = h;
    SDL_RenderCopy(window->sdl_renderer, texture, NULL, &box);
}


void draw_text(Window* window, string str, int x, int y) {
    // Créer une surface avec le texte à afficher
    SDL_Surface* surface = TTF_RenderText_Shaded(
        window->sdl_font,
        str.c_str(),
        window->foreground,   // couleur du texte
        window->background    // couleur du fond
    );

    if (surface == NULL) {
        cout << "Could not init the SDL surface for TTF: " << TTF_GetError() << endl;
        exit(1);
    }

    // Récupérer les dimensions
    int w = surface->w;
    int h = surface->h;

    // Créer une texture à partir de la surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);
    SDL_FreeSurface(surface); // libérer la surface

    if (texture == nullptr){
        cout << "Could not init the SDL Texture for TTF: " << SDL_GetError() << endl;
        SDL_Quit();
    }

    // Dessiner la texture à l'écran
    draw_texture(window, texture, x, y, w, h);
    SDL_DestroyTexture(texture); // libérer la texture après affichage
}
