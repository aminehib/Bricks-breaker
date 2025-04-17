#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
using namespace std;

struct Window {
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;
    int width;
    int height;
    SDL_Color background;
    SDL_Color foreground;
    TTF_Font* font;
};

void init_window(Window* window, int width, int height, string title);
void close_window(Window* window);

void clear_window(Window* window);
void refresh_window(Window* window);

void set_color(SDL_Color* color, int r, int g, int b, int a);
void set_color(Window* window, SDL_Color* color);

void draw_fill_rectangle(Window* window, int x, int y, int w, int h);
void draw_text(Window* window, const char* text, int x, int y);

#endif
