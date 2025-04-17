#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

struct Window {
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;
    int width;
    int height;

    // Ajout des couleurs de fond et premier plan
   
    SDL_Color background;
    SDL_Color foreground;
};

    

void init_window(Window* window, int width, int height, string title);

void close_window(Window* window);

void set_color(SDL_Color* dst, int r, int g, int b, int a);

void set_color(SDL_Color* dst, SDL_Color* src);

void clear_window(Window* window);

void draw_fill_rectangle(Window* window, int x, int y, int w, int h);

void refresh_window(Window* window);




#endif