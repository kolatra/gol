#include <stdio.h>
#include <stdint.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

// conway's game of life in a single function
int main(int argc, char** argv) {
    // variable declarations
    uint16_t pixel_size = 12;
    uint16_t video_width = 64;
    uint16_t video_height = 32;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect pixels[video_width * video_height];
    // end local variable declarations

    // SDL initialization
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(
        "a program", 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        video_width * pixel_size,
        video_height * pixel_size,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Surface* image = SDL_GetWindowSurface(window);

    if (!image) {
        printf("SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    // end SDL initialization

    bool running = true;
    SDL_Event e;
    while (running) {
        // event handling
        while (SDL_PollEvent(&e)) {
            switch(e.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                    }
                    break;
            }
        }

        // render
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        for (int i = 0; i < video_width * video_height; i++) {
            if (i % 10 == 0) {
                continue;
            }

            pixels[i].x = (i % video_width) * pixel_size;
            pixels[i].y = (i / video_height) * pixel_size;
            pixels[i].w = pixel_size;
            pixels[i].h = pixel_size;

            SDL_RenderFillRect(renderer, &pixels[i]);
        }

        SDL_RenderPresent(renderer);
    }
    
    // cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
