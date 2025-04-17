#include <iostream>
#include "window.hpp"

using namespace std;

void draw_grid(Window* window, int grid_size, int cell_size, int offset_x, int offset_y) {
    SDL_SetRenderDrawColor(window->sdl_renderer, 0, 0, 0, 255);
    for (int i = 0; i <= grid_size; i++) {
        int y = offset_y + i * cell_size;
        SDL_RenderDrawLine(window->sdl_renderer, offset_x, y, offset_x + grid_size * cell_size, y);
    }
    for (int j = 0; j <= grid_size; j++) {
        int x = offset_x + j * cell_size;
        SDL_RenderDrawLine(window->sdl_renderer, x, offset_y, x, offset_y + grid_size * cell_size);
    }
}

int main(int argc, char** argv) {
    Window window;
    init_window(&window, 800, 600, "Événements SDL");

    set_color(&window.background, 255, 255, 255, 255); // blanc
    set_color(&window.foreground, 0, 0, 255, 255);     // bleu

    // Chargement des textures
    SDL_Texture* tux = load_image(&window, "tux.png");
    if (tux == nullptr) {
        cerr << "Erreur : tux.png non chargée." << endl;
        close_window(&window);
        return 1;
    }

    SDL_Texture* ball = load_image(&window, "ball.png");
    if (ball == nullptr) {
        cerr << "Erreur : ball.png non chargée." << endl;
        SDL_DestroyTexture(tux);
        close_window(&window);
        return 1;
    }

    // Position et direction initiales de la balle
    int x = 100, y = 100;
    int dx = 1, dy = 1;
    int speed = 5;
    const int ball_size = 20;

    // Affichage initial
    clear_window(&window);
    draw_grid(&window, 10, 40, 50, 50); // Grille statique
    refresh_window(&window);

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN: {
                    SDL_KeyboardEvent key = event.key;
                    switch (key.keysym.sym) {
                        case SDLK_q:
                            quit = true;
                            break;
                        case SDLK_UP:
                            if (speed < 10) speed++;
                            break;
                        case SDLK_DOWN:
                            if (speed > 1) speed--;
                            break;
                        case SDLK_LEFT:
                            cout << "Flèche gauche" << endl;
                            break;
                        case SDLK_RIGHT:
                            cout << "Flèche droite" << endl;
                            break;
                    }
                    break;
                }

                case SDL_MOUSEBUTTONDOWN: {
                    SDL_MouseButtonEvent btn = event.button;
                    cout << "Clic souris : "
                         << ((btn.state == SDL_PRESSED) ? "Appuyé" : "Relâché")
                         << " | Bouton : " << (int)btn.button
                         << " | Position : (" << btn.x << ", " << btn.y << ")" << endl;
                    x = btn.x - ball_size / 2;
                    y = btn.y - ball_size / 2;
                    break;
                }
            }
        }

        // Mise à jour de la position de la balle
        x += dx;
        y += dy;

        if (x <= 0 || x + ball_size >= window.width) dx = -dx;
        if (y <= 0 || y + ball_size >= window.height) dy = -dy;

        // Affichage
        clear_window(&window);
        draw_grid(&window, 10, 40, 50, 50); // redessiner la grille si nécessaire
        draw_texture(&window, tux, 300, 200, 200, 200);
        draw_texture(&window, ball, x, y, ball_size, ball_size);
        draw_text(&window, "Bonjour le monde !", 10, 10);
        refresh_window(&window);

        SDL_Delay(10 - speed);
    }

    SDL_DestroyTexture(tux);
    SDL_DestroyTexture(ball);
    close_window(&window);
    return 0;
}
