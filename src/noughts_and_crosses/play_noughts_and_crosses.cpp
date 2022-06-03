#include "play_noughts_and_crosses.hpp"
#include <p6/p6.h>
#include <iostream>

struct BoardCell {
    int _x;
    int _y;

    BoardCell(int x, int y)
        : _x(x), _y(y)
    {
    }
};

//draws a single cell
void draw_cell(const float& cell_size, const float& radius, const BoardCell& cell_index, p6::Context& ctx)
{
    ctx.square(p6::TopLeftCorner{-1.f + static_cast<float>(cell_index._x) * cell_size, 1.f - static_cast<float>(cell_index._y) * cell_size}, radius);
}

//draws the grid of the game
void draw_board(int size, p6::Context& ctx)
{
    const float cell_size = 2 / static_cast<float>(size);
    const float radius    = 1 / static_cast<float>(size);

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            const auto cell_index = BoardCell{x, y};
            draw_cell(cell_size, radius, cell_index, ctx);
        }
    }
}

//transforms the mouse position to the position of the cell (top left corner)
BoardCell transform_mouse_pos_to_cell_index(glm::vec2 mouse_pos, const int& board_size)
{
    glm::vec2 index = glm::vec2(std::floor(((mouse_pos.x + 1) / 2) * static_cast<float>(board_size)), board_size - 1 - std::floor(((mouse_pos.y + 1) / 2) * static_cast<float>(board_size)));

    const auto cell_index = BoardCell{static_cast<int>(index.x), static_cast<int>(index.y)};

    //std::cout << index.x << " ; " << index.y << std::endl;

    return cell_index;
}

//detects if a cell is being hovered, and if so which cell it is
std::optional<BoardCell> cell_is_hovered(glm::vec2 mouse_pos, const int& board_size)
{
    //if there is a hovered cell we return it, if not we return a null
    if (mouse_pos.x >= -1 && mouse_pos.x < 1 && mouse_pos.y >= -1 && mouse_pos.y < 1) {
        //the mouse is in the window
        return transform_mouse_pos_to_cell_index(mouse_pos, board_size);
    }
    else {
        return std::nullopt;
    }
}

//returns the center of a cell from its index
glm::vec2 find_cell_center(const float& cell_size, const BoardCell& cell_index)
{
    return glm::vec2(-1.f + cell_size / 2 + cell_index._x * cell_size, 1.f - cell_size / 2 - cell_index._y * cell_size);
}

void draw_circle(const float& cell_size, const float& radius, const BoardCell& cell_index, p6::Context& ctx)
{
    ctx.fill          = {0, 0, 0, 0};
    ctx.stroke_weight = 0.06f;

    const auto circle_center = p6::Center{find_cell_center(cell_size, cell_index)};
    const auto circle_radius = 0.8f * radius;

    ctx.circle(circle_center, circle_radius);
}

void draw_cross(const float& cell_size, const float& radius, const BoardCell& cell_index, p6::Context& ctx)
{
    ctx.fill          = {0, 0, 0, 0};
    ctx.stroke_weight = 0.06f;

    const auto rect_center   = p6::Center{find_cell_center(cell_size, cell_index)};
    const auto rect_radius   = p6::Radii{glm::vec2{.8f, 0.1f} * radius};
    const auto rect_rotation = p6::Rotation{0.125_turn};

    ctx.rectangle(rect_center, rect_radius, rect_rotation);
    ctx.rectangle(rect_center, rect_radius, -rect_rotation);
}

//main function to play the game
void play_noughts_and_crosses()
{
    static const int board_size = 3;

    auto ctx   = p6::Context{{1080, 1080, "NOUGHTS AND CROSSES"}};
    ctx.update = [&]() {
        ctx.background({0.1, 0., 0.2});
        ctx.stroke        = {0.1, 0., 0.2};
        ctx.stroke_weight = 0.02f;
        ctx.fill          = {.25, .22, .32};

        draw_board(board_size, ctx);

        const auto hovered_cell = cell_is_hovered(ctx.mouse(), board_size);

        if (hovered_cell.has_value()) {
            ctx.fill = {0.1f, 0.f, 0.2f, .24f};
            draw_cell(2 / static_cast<float>(board_size), 1 / static_cast<float>(board_size), *hovered_cell, ctx);
            draw_circle(2 / static_cast<float>(board_size), 1 / static_cast<float>(board_size), *hovered_cell, ctx);
            draw_cross(2 / static_cast<float>(board_size), 1 / static_cast<float>(board_size), *hovered_cell, ctx);
        }
    };

    ctx.start();
}