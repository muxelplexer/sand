#include "world.h"
#include "raylib.h"
#include "assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PART_WIDTH 10

bool* world_cell(struct world* world, const int x, const int y)
{
    if (x >= GRID_SIZE || x < 0) return nullptr;
    else if(y >= GRID_SIZE || y < 0) return nullptr;
    else return &world->grid[(y * GRID_SIZE) + x];
}

bool world_cell_is_empty(struct world* world, const int x, const int y)
{
    if (x >= GRID_SIZE || x < 0) return false;
    else if(y >= GRID_SIZE || y < 0) return false;
    else return !(*world_cell(world, x, y));
}

void world_cell_set(struct world* world, const int x, const int y, const bool state)
{
    bool* cell = world_cell(world, x, y);
    assert(cell);
    *cell = state;
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
        world_cell_set(world, change->src_pos.x, change->src_pos.y, false);
        world_cell_set(world, change->dst_pos.x, change->dst_pos.y, true);
        free(change);
        change = temp;
    }
    list->head = nullptr;
    list->change = nullptr;
}

void world_update(struct world* world)
{
    for (int j = 0; j < GRID_SIZE; ++j)
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            if (!world_cell_is_empty(world, i, j))
            {
                bool below_cell = world_cell_is_empty(world, i, j + 1);
                bool lb_cell = world_cell_is_empty(world, i - 1, j + 1);
                bool rb_cell = world_cell_is_empty(world, i + 1, j + 1);

                if (below_cell)
                {
                    const struct world_pos src = {i, j};
                    const struct world_pos dst = {i, j + 1};
                    world_cell_move(world, src, dst);
                } else if (lb_cell)
                {
                    const struct world_pos src = {i, j};
                    const struct world_pos dst = {i - 1, j + 1};
                    world_cell_move(world, src, dst);
                } else if (rb_cell)
                {
                    const struct world_pos src = {i, j};
                    const struct world_pos dst = {i + 1, j + 1};
                    world_cell_move(world, src, dst);
                }
            }
        }
    }
    world_cell_commit(world);
}

void world_handle_input(struct world* world)
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        Vector2 mouse_pos = GetMousePosition();
        float ratio_x = (float)GetRenderWidth() / GRID_SIZE;
        float ratio_y = (float)GetRenderHeight() / GRID_SIZE;
        int x = (int)(mouse_pos.x / ratio_x);
        if (x >= 100)
            x = 99;
        else if (x < 0)
            x = 0;

        int y = (int)(mouse_pos.y / ratio_y);
        if (y >= 100)
            y = 99;
        else if (y < 0)
            y = 0;

#ifndef NDEBUG
        printf("Mouse Position Before: %f:%f\n", mouse_pos.x, mouse_pos.y);
        printf("Mouse Position: %d:%d\n", x, y);
#endif
        world_cell_set(world, x, y, true);
    }
}

void world_render(struct world* world)
{
    for (int j = 0; j < GRID_SIZE; ++j)
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            int ratio_x = GetRenderWidth() / GRID_SIZE;
            int ratio_y = GetRenderHeight() / GRID_SIZE;
            Color col;
            if (!world_cell_is_empty(world, i, j))
            {
                col = YELLOW;
            } else
            {
                col = RAYWHITE;
            }

            DrawRectangle(i * ratio_x, j * ratio_y, ratio_x, ratio_y, col);
        }
    }
}
