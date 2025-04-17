#include "window.hpp"
#include "game.hpp"
#include <SDL2/SDL_image.h>

int main(int argc, char** argv) {
    // Initialisation SDL_image
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "Erreur SDL_image : " << IMG_GetError() << std::endl;
        return 1;
    }

    Window window;
    init_window(&window, 800, 600, "Casse-brique");

    set_color(&window.background, 0, 0, 0, 255);
    set_color(&window.foreground, 255, 255, 255, 255);

    Game game;
    init_game(&game, &window, "world.dat");

    bool quit = false;
    int compteur = 0;

    while (!quit) {
        clear_window(&window);
        quit = keyboard_event(&game);

        if (game.statut == Play && compteur % (100 - game.ball_speed) == 0) {
            move_ball(&game);
            check_game_status(&game);
        }

        display_game(&window, &game);
        refresh_window(&window);
        SDL_Delay(10);
        compteur++;
    }

    // Libération de la texture
    SDL_DestroyTexture(game.ball_texture);
    free_world(game.world);
    delete game.world;
    close_window(&window);
    SDL_DestroyTexture(game.ball_texture);
    IMG_Quit();

    return 0;
}
