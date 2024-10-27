#include "world.h"
#include "assert.h"
#include "cell.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL3/SDL.h>

cell_t* world_cell(struct world* world, const int x, const int y)
{
    if (x >= GRID_SIZE || x < 0) return nullptr;
    else if(y >= GRID_SIZE || y < 0) return nullptr;
    else return &world->grid[(y * GRID_SIZE) + x];
}

cell_type_t world_cell_type(struct world* world, const int x, const int y)
{
    if (x >= GRID_SIZE || x < 0) return CT_NONE;
    else if(y >= GRID_SIZE || y < 0) return CT_NONE;
    else return (*world_cell(world, x, y)).type;
}

bool world_cell_is_empty(struct world* world, const int x, const int y)
{
    if (x >= GRID_SIZE || x < 0) return false;
    else if(y >= GRID_SIZE || y < 0) return false;
    else return (*world_cell(world, x, y)).type == CT_EMPTY;
}

void world_cell_set(struct world* world, const int x, const int y, const enum cell_type type)
{
    cell_t* cell = world_cell(world, x, y);
    assert(cell);
    assert(cell->type != CT_NONE);
    cell->type = type;
}



struct world* world_init(struct SDL_Window* win, struct SDL_Renderer* renderer)
{
    struct world* the_world = malloc(sizeof(struct world));
    memset(the_world, 0, sizeof(struct world));

    the_world->window = win;
    the_world->renderer = renderer;
    the_world->quit = SDL_APP_CONTINUE;
    the_world->spawn_type = CT_SAND;
    return the_world;
}

void world_cell_move(struct world* world, const struct world_pos src, const struct world_pos dst)
{
    struct world_change_list* list = &world->changes;
    struct world_change* change = list->head;
    if (!change)
    {
        change = malloc(sizeof(struct world_change));
        list->change = change;
    } else
    {
        change->next = malloc(sizeof(struct world_change));
        change = change->next;
    }
    memset(change, 0, sizeof(struct world_change));

    change->src_pos = src;
    change->dst_pos = dst;
    list->head = change;
}

void world_cell_commit(struct world* world)
{
    struct world_change_list* list = &world->changes;
    if (!list->head) return;

    struct world_change* change = list->change;
    while (change)
    {
        struct world_change* temp = change->next;
        cell_type_t src_type = world_cell_type(world, change->src_pos.x, change->src_pos.y);
        cell_type_t dst_type = world_cell_type(world, change->dst_pos.x, change->dst_pos.y);
        if (dst_type != CT_NONE)
        {
            world_cell_set(world, change->src_pos.x, change->src_pos.y, dst_type);
            world_cell_set(world, change->dst_pos.x, change->dst_pos.y, src_type);
        }

        free(change);
        change = temp;
    }
    list->head = nullptr;
    list->change = nullptr;
}

void world_update(struct world* world)
{
    if (world->button_pressed)
    {
        int w, h;

        if (!SDL_GetWindowSize(world->window, &w, &h))
        {
            SDL_Log("Could not get window size - will not render.");
        }
        float ratio_x = (float)w / GRID_SIZE;
        float ratio_y = (float)h / GRID_SIZE;

        float x, y;
        SDL_GetMouseState(&x, &y);
        x /= ratio_x;
        if (x >= GRID_SIZE)
            x = GRID_SIZE - 1;
        else if (x < 0)
            x = 0;

        y /= ratio_y;

        if (y >= GRID_SIZE)
            y = GRID_SIZE - 1;
        else if (y < 0)
            y = 0;

#ifndef NDEBUG
        printf("Mouse Position: %f:%f\n", x, y);
#endif
        world_cell_set(world, (int)x, (int)y, world->spawn_type);
    }

    for (int j = 0; j < GRID_SIZE; ++j)
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            cell_type_t cell_type = world_cell_type(world, i, j);
            switch (cell_type)
            {
            case CT_WATER:
                cell_action_water(world, i, j);
                break;
            case CT_SAND:
                cell_action_sand(world, i, j);
                break;
            default:
                break;
            };
        }
    }
    world_cell_commit(world);
}

void world_handle_input(struct world* world, union SDL_Event* event)
{
    if (event->type == SDL_EVENT_KEY_DOWN)
    {
        world->button_pressed = true;
        switch(event->key.key)
        {
        case SDLK_W:
            world->spawn_type = CT_WATER;
            break;
        case SDLK_S:
            world->spawn_type = CT_SAND;
            break;
        default:
            break;
        };
    }
    if (event->type == SDL_EVENT_KEY_UP)
    {
        world->button_pressed = false;
    }
}

void world_render(struct world* world)
{
    for (int j = 0; j < GRID_SIZE; ++j)
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            int scr_w;
            int scr_h;
            if (!SDL_GetWindowSize(world->window, &scr_w, &scr_h))
            {
                SDL_Log("Could not get window size - will not render.");
            }

            float ratio_x = (float)scr_w / (float)GRID_SIZE;
            float ratio_y = (float)scr_h / (float)GRID_SIZE;
            cell_type_t cell_type = world_cell_type(world, i, j);
            switch (cell_type)
            {
            case CT_WATER:
                SDL_SetRenderDrawColor(world->renderer, 0x00, 0xb2, 0xFF, 255);
                break;
            case CT_SAND:
                SDL_SetRenderDrawColor(world->renderer, 0xc2, 0xb2, 0x80, 255);
                break;
            default:
                SDL_SetRenderDrawColor(world->renderer, 0, 0, 0, 255);
                break;
            };

            SDL_FRect rect = {
                (float)i * ratio_x,
                (float)j * ratio_y,
                (float)ratio_x,
                (float)ratio_y
            };

            SDL_RenderFillRect(world->renderer, &rect);
        }
    }
}
