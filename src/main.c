#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "world.h"


SDL_AppResult SDL_AppInit(void** appstate, [[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return SDL_APP_FAILURE;
    }

    SDL_Window* window = SDL_CreateWindow(
            "sand",
            800, 
            800,
            0
    );
    if (!window) {
        return SDL_APP_FAILURE;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        return SDL_APP_FAILURE;
    }

    *appstate = malloc(sizeof(struct world));
    struct world* the_world = (struct world*)*appstate;
    memset(the_world, 0, sizeof(struct world));

    the_world->window = window;
    the_world->renderer = renderer;
    the_world->quit = SDL_APP_CONTINUE;
    SDL_Log("sand initialized successfully");

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    struct world* world = (struct world*)appstate;

    if (event->type == SDL_EVENT_QUIT) {
        world->quit = SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        if(event->key.key == SDLK_Q)
        {
            world->quit = SDL_APP_SUCCESS;
        }
    }

    world_handle_input(world, event);

    return world->quit;
}

SDL_AppResult SDL_AppIterate(void* appstate)
{
    struct world* world = (struct world*)appstate;

    SDL_SetRenderDrawColor(world->renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(world->renderer);

    world_render(world);

    SDL_RenderPresent(world->renderer);

    world_update(world);
    return world->quit;
}

void SDL_AppQuit(void* appstate, [[maybe_unused]] SDL_AppResult result)
{
    struct world* world = (struct world*)appstate;
    if (world)
    {
        SDL_DestroyRenderer(world->renderer);
        SDL_DestroyWindow(world->window);
        free(world);
    }

    SDL_Log("sand quit successfully");
}
