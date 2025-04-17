#ifndef GAME_HPP
#define GAME_HPP

#include "world.hpp"
#include "window.hpp"
#include <SDL2/SDL.h>

enum Statut {
    Begin,
    Play,
    Pause,
    Win,
    GameOver
};

struct Game {
    World* world;

    SDL_Color empty_color;
    SDL_Color border_color;
    SDL_Color type1_color;
    SDL_Color type2_color;
    SDL_Color lose_color;

    int racket_x;
    int racket_y;
    int racket_half_width;
    SDL_Color racket_color;

    int ball_x;
    int ball_y;
    int ball_dx;
    int ball_dy;
    int ball_speed;
    SDL_Color ball_color;

    Statut statut;
    
    // Texture de la balle
    SDL_Texture* ball_texture;
    
    int score;

};

void init_game(Game* game, Window* window, string filename);
void display_game(Window* window, Game* game);
bool keyboard_event(Game* game);
void change_statut(Game* game);
void move_racket(Game* game, int d);
void move_ball(Game* game);
void check_game_status(Game* game);
Block get_block(Game* game, int x, int y);

#endif
