#include "world.h"
#include "raylib.h"
#include "assert.h"
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

void world_render(struct world* world)
{
    for (int j = 0; j < GRID_SIZE; ++j)
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            Color col;
            if (!world_cell_is_empty(world, i, j))
            {
                col = BLACK;
            } else
            {
                col = RAYWHITE;
            }

            DrawRectangle(i * PART_WIDTH + (PART_WIDTH / 2), j * PART_WIDTH + (PART_WIDTH / 2), PART_WIDTH, PART_WIDTH, col);
        }
    }
}
