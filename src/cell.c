#include "cell.h"
#include "world.h"

void cell_action_sand(struct world* world, const int x, const int y)
{
    cell_type_t bc      = world_cell_type(world, x, y + 1);
    cell_type_t lb_cell = world_cell_type(world, x - 1, y + 1);
    cell_type_t rb_cell = world_cell_type(world, x + 1, y + 1);

    if (bc == CT_EMPTY || bc == CT_WATER)
    {
        const struct world_pos src = {x, y};
        const struct world_pos dst = {x, y + 1};
        world_cell_move(world, src, dst);
    } else if (lb_cell == CT_EMPTY || lb_cell == CT_WATER)
    {
        const struct world_pos src = {x, y};
        const struct world_pos dst = {x - 1, y + 1};
        world_cell_move(world, src, dst);
    } else if (rb_cell == CT_EMPTY || rb_cell == CT_WATER)
    {
        const struct world_pos src = {x, y};
        const struct world_pos dst = {x + 1, y + 1};
        world_cell_move(world, src, dst);
    }
}

void cell_action_water(struct world* world, const int x, const int y)
{

    cell_type_t b_cell = world_cell_type(world, x, y + 1);
    cell_type_t lb_cell = world_cell_type(world, x - 1, y + 1);
    cell_type_t rb_cell = world_cell_type(world, x + 1, y + 1);
    cell_type_t l_cell = world_cell_type(world, x - 1, y);
    cell_type_t r_cell = world_cell_type(world, x + 1, y);

    if (b_cell == CT_EMPTY)
    {
        const struct world_pos src = {x, y};
        const struct world_pos dst = {x, y + 1};
        world_cell_move(world, src, dst);
    } else if (lb_cell == CT_EMPTY)
    {
        const struct world_pos src = {x, y};
        const struct world_pos dst = {x - 1, y + 1};
        world_cell_move(world, src, dst);
    } else if (rb_cell == CT_EMPTY)
    {
        const struct world_pos src = {x, y};
        const struct world_pos dst = {x + 1, y + 1};
        world_cell_move(world, src, dst);
    } else if (l_cell == CT_EMPTY)
    {
        const struct world_pos src = {x, y};
        const struct world_pos dst = {x - 1, y};
        world_cell_move(world, src, dst);
    } else if (r_cell == CT_EMPTY)
    {
        const struct world_pos src = {x, y};
        const struct world_pos dst = {x + 1, y};
        world_cell_move(world, src, dst);
    }
}
