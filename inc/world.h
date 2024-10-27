#pragma once
#include <SDL3/SDL_init.h>
#include "cell.h"

#define GRID_SIZE  250

struct world_pos
{
    int x;
    int y;
};
struct world_change
{
    struct world_pos src_pos;
    struct world_pos dst_pos;
    struct world_change* next;
};

struct world_change_list
{
    struct world_change* change;
    struct world_change* head;
};

struct SDL_Window;
struct SDL_Renderer;
union SDL_Event;

struct world
{
    cell_t grid[GRID_SIZE * GRID_SIZE];
    struct world_change_list changes;
    struct SDL_Window* window;
    struct SDL_Renderer* renderer;
    bool button_pressed;
    cell_type_t spawn_type;
    SDL_AppResult quit;
};

struct world* world_init(struct SDL_Window* win, struct SDL_Renderer* renderer);
void world_update(struct world* world);
void world_handle_input(struct world* world, union SDL_Event* event);
void world_render(struct world* world);
void world_cell_move(struct world* world, const struct world_pos src, const struct world_pos dst);
bool world_cell_is_empty(struct world* world, const int x, const int y);
cell_type_t world_cell_type(struct world* world, const int x, const int y);
