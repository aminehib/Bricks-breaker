#include "game.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>

using namespace std;

void init_game(Game* game, Window* window, string filename) {
    game->score = 0;
    game->world = new World;
    init_world_from_file(game->world, filename);

    // Couleurs des blocs
    game->empty_color  = {0, 0, 0, 255};
    game->border_color = {100, 100, 100, 255};
    game->type1_color  = {255, 0, 0, 255};
    game->type2_color  = {0, 255, 0, 255};
    game->lose_color   = {50, 50, 50, 255};
    game->racket_color = {0, 255, 255, 255};
    game->ball_color   = {255, 255, 255, 255};

    // Position raquette
    game->racket_half_width = 3;
    game->racket_y = game->world->height - 2;
    game->racket_x = game->world->width / 2;

    // Position balle
    game->ball_x = game->racket_x;
    game->ball_y = game->racket_y - 1;
    game->ball_dx = 0;
    game->ball_dy = -1;
    game->ball_speed = 50;

    game->statut = Begin;

    // Chargement de la texture de la balle
    SDL_Surface* surface = IMG_Load("ball.png");
    if (!surface) {
        cerr << "Erreur IMG_Load ball.png : " << IMG_GetError() << endl;
        game->ball_texture = NULL;
    } else {
        game->ball_texture = SDL_CreateTextureFromSurface(window->sdl_renderer, surface);
        SDL_FreeSurface(surface);
    }
}

void display_game(Window* window, Game* game) {
    int cell_w = window->width / game->world->width;
    int cell_h = window->height / game->world->height;

    // Affichage des blocs
    for (int y = 0; y < game->world->height; y++) {
        for (int x = 0; x < game->world->width; x++) {
            Block b = read(game->world, x, y);
            SDL_Color color;
            switch (b) {
                case Empty:  color = game->empty_color; break;
                case Border: color = game->border_color; break;
                case Type1:  color = game->type1_color; break;
                case Type2:  color = game->type2_color; break;
                case Lose:   color = game->lose_color; break;
                default:     color = game->empty_color;
            }

            set_color(window, &color);
            draw_fill_rectangle(window, x * cell_w, y * cell_h, cell_w, cell_h);
        }
    }

    // Affichage raquette
    set_color(window, &game->racket_color);
    for (int i = -game->racket_half_width; i <= game->racket_half_width; i++) {
        int rx = game->racket_x + i;
        if (rx >= 0 && rx < game->world->width) {
            draw_fill_rectangle(window, rx * cell_w, game->racket_y * cell_h, cell_w, cell_h);
        }
    }

    // Affichage balle avec texture
    if (game->ball_texture != NULL) {
        SDL_Rect dest = {game->ball_x * cell_w, game->ball_y * cell_h, cell_w, cell_h};
        SDL_RenderCopy(window->sdl_renderer, game->ball_texture, NULL, &dest);
    } else {
        set_color(window, &game->ball_color);
        draw_fill_rectangle(window, game->ball_x * cell_w, game->ball_y * cell_h, cell_w, cell_h);
    }
}

bool keyboard_event(Game* game) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return true;

        if (event.type == SDL_KEYDOWN) {
            SDL_Keycode key = event.key.keysym.sym;

            switch (key) {
                case SDLK_q:
                    cout << "Quitter (Q)" << endl;
                    return true;

                case SDLK_r:
                    cout << "Reset (R)" << endl;
                    // À compléter si besoin plus tard
                    break;

                case SDLK_LEFT:
                    move_racket(game, -1);
                    break;

                case SDLK_RIGHT:
                    move_racket(game, 1);
                    break;

                case SDLK_SPACE:
                    change_statut(game);
                    break;
            }
        }
    }
    return false;
}


void change_statut(Game* game) {
    switch (game->statut) {
        case Begin:
            game->statut = Play;
            break;
        case Play:
            game->statut = Pause;
            break;
        case Pause:
            game->statut = Play;
            break;
        case Win:
        case GameOver:
            game->statut = Begin;

            // Réinitialisation position
            game->racket_x = game->world->width / 2;
            game->ball_x = game->racket_x;
            game->ball_y = game->racket_y - 1;
            game->ball_dx = 0;
            game->ball_dy = -1;
            break;
    }
}


void move_racket(Game* game, int d) {
    if (game->statut == Pause || game->statut == Win || game->statut == GameOver)
        return;

    int new_x = game->racket_x + d;
    int min = game->racket_half_width;
    int max = game->world->width - 1 - game->racket_half_width;

    if (new_x >= min && new_x <= max) {
        game->racket_x = new_x;

        if (game->statut == Begin) {
            game->ball_x = game->racket_x;
            game->ball_y = game->racket_y - 1;
        }
    }
}

void move_ball(Game* game) {
    int x = game->ball_x;
    int y = game->ball_y;
    int dx = game->ball_dx;
    int dy = game->ball_dy;

    int next_x = x + dx;
    int next_y = y + dy;

    Block cible = get_block(game, next_x, next_y);

    // 1. Rebond sur bloc destructible
    if (cible == Type1 || cible == Type2) {
        write(game->world, next_x, next_y, Empty);
        dy *= -1; // rebond vertical
        game->score += 1;
    }

    // 2. Rebond sur Border
    else if (cible == Border) {
        Block h = get_block(game, x + dx, y);
        Block v = get_block(game, x, y + dy);

        if (h == Border && v == Border) {
            dx *= -1;
            dy *= -1;
        } else if (h == Border) {
            dx *= -1;
        } else if (v == Border) {
            dy *= -1;
        } else {
            dx *= -1;
            dy *= -1;
        }
    }

    // 3. Rebond sur la raquette (si on descend et touche une cellule de la raquette)
    if (dy > 0 && y + 1 == game->racket_y) {
        int rx = game->racket_x;
        int rh = game->racket_half_width;

        if (next_x >= rx - rh && next_x <= rx + rh) {
            if (next_x == rx) { // centre
                dx = 0;
                dy = -1;
            } else if (next_x == rx - rh) { // gauche
                dx = -1;
                dy = -1;
            } else if (next_x == rx + rh) { // droite
                dx = 1;
                dy = -1;
            } else {
                if (game->ball_dx == 0) dx = 0;
                else if (game->ball_dx < 0) dx = -1;
                else dx = 1;
                dy = -1;
            }
        }
    }

    // Appliquer le déplacement mis à jour
    game->ball_dx = dx;
    game->ball_dy = dy;
    game->ball_x += dx;
    game->ball_y += dy;
}


void check_game_status(Game* game) {
    Block b = read(game->world, game->ball_x, game->ball_y);

    if (b == Lose) {
        game->statut = GameOver;
        cout << "Game Over !" << endl;
        return;
    }

    // Vérifie s'il reste des blocs à casser
    for (int y = 0; y < game->world->height; y++) {
        for (int x = 0; x < game->world->width; x++) {
            Block bloc = read(game->world, x, y);
            if (bloc == Type1 || bloc == Type2)
                return;
        }
    }

    game->statut = Win;
    cout << "Win !" << endl;
}

Block get_block(Game* game, int x, int y) {
    if (x < 0 || x >= game->world->width || y < 0 || y >= game->world->height)
        return Border;
    return read(game->world, x, y);
}

