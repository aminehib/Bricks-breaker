#include "window.hpp"
#include <iostream>

void init_window(Window* window, int width, int height, string title) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    window->width = width;
    window->height = height;
    window->sdl_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    window->sdl_renderer = SDL_CreateRenderer(window->sdl_window, -1, SDL_RENDERER_ACCELERATED);
    window->font = TTF_OpenFont("arial.ttf", 16); // ou un autre fichier .ttf existant
    if (!window->font) cout << "Police non trouvée" << endl;
}

void close_window(Window* window) {
    TTF_CloseFont(window->font);
    SDL_DestroyRenderer(window->sdl_renderer);
    SDL_DestroyWindow(window->sdl_window);
    TTF_Quit();
    SDL_Quit();
}

void clear_window(Window* window) {
    SDL_SetRenderDrawColor(window->sdl_renderer, window->background.r, window->background.g, window->background.b, window->background.a);
    SDL_RenderClear(window->sdl_renderer);
}

void refresh_window(Window* window) {
    SDL_RenderPresent(window->sdl_renderer);
}

void set_color(SDL_Color* color, int r, int g, int b, int a) {
    color->r = r;
    color->g = g;
    color->b = b;
    color->a = a;
}

void set_color(Window* window, SDL_Color* color) {
    SDL_SetRenderDrawColor(window->sdl_renderer, color->r, color->g, color->b, color->a);
}

void draw_fill_rectangle(Window* window, int x, int y, int w, int h) {
    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(window->sdl_renderer, &rect);
}

void draw_text(Window* window, const char* text, int x, int y) {
    // Initialisation police
    static TTF_Font* font = nullptr;
    if (!font) {
        font = TTF_OpenFont("FreeSans.ttf", 24); // Tu peux mettre un autre fichier .ttf
        if (!font) {
            SDL_Log("Erreur chargement police : %s", TTF_GetError());
            return;
        }
    }

    // Rendu texte
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, window->foreground);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);
    if (!texture) {
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

    SDL_RenderCopy(window->sdl_renderer, texture, NULL, &dest);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
