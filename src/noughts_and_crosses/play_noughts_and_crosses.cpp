#include "play_noughts_and_crosses.hpp"
#include <p6/p6.h>
#include <iostream>
#include <string>

struct BoardCell {
    int _x;
    int _y;

    BoardCell(int x, int y)
        : _x(x), _y(y)
    {
    }
};

enum class Player {
    Noughts,
    Crosses,
};

template<int size>
class Board {
public:
    std::optional<Player>& operator[](BoardCell index)
    {
        return _cells[index._x][index._y];
    }

    const std::optional<Player>& operator[](BoardCell index) const
    {
        return _cells[index._x][index._y];
    }

private:
    std::array<std::array<std::optional<Player>, size>, size> _cells;
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

//draws a circle in the center of the cell
void draw_circle(const float& cell_size, const float& radius, const BoardCell& cell_index, p6::Context& ctx)
{
    ctx.fill          = {0, 0, 0, 0};
    ctx.stroke_weight = 0.06f;

    const auto circle_center = p6::Center{find_cell_center(cell_size, cell_index)};
    const auto circle_radius = 0.8f * radius;

    ctx.circle(circle_center, circle_radius);
}

//draws a cross in the center of the cell
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

//draws the noughts and crosses that have already been placed on the board
template<int size>
void draw_noughts_and_crosses(const Board<size>& board, p6::Context& ctx)
{
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            const auto board_cell = board[{x, y}];
            if (board_cell.has_value()) {
                if (*board_cell == Player::Noughts) {
                    draw_circle(2 / static_cast<float>(size), 1 / static_cast<float>(size), BoardCell(x, y), ctx);
                }
                else {
                    draw_cross(2 / static_cast<float>(size), 1 / static_cast<float>(size), BoardCell(x, y), ctx);
                }
            }
        }
    }
}

//swap the payer once one has clicked on a cell
void swap_player(Player& current_player)
{
    current_player = (current_player == Player::Crosses) ? Player::Noughts : Player::Crosses;
}

//check if the game is finished because the board is complete
template<int board_size>
bool board_is_complete(const Board<board_size>& board)
{
    int  number_of_taken_cells = 0;
    bool game_is_finished;

    for (int x = 0; x < board_size; x++) {
        for (int y = 0; y < board_size; y++) {
            if (board[{x, y}].has_value()) {
                number_of_taken_cells++;
            }
        }
    }

    game_is_finished = (number_of_taken_cells == board_size * board_size) ? true : false;

    if (game_is_finished) {
        std::cout << "No one wins! the board is full" << std::endl;
    }

    return game_is_finished;
}

//returns the name of the player : either Crosses or Noughts
std::string player_type_name(Player& current_player)
{
    std::string name = "";

    name = (current_player == Player::Noughts) ? "Noughts" : "Crosses";

    return name;
}

//check if a line is complete with the same symbol
//direction establishes if we look for a column, row or diagonal
//incremantation is for which row or column
template<int board_size>
bool line_is_complete(const Board<board_size>& board, Player& current_player, glm::vec2 direction, int incrementation)
{
    bool complete_line = true;
    for (int i = 0; i < board_size && complete_line; i++) {
        if (board[{i * static_cast<int>(direction.x) + static_cast<int>(direction.y) * incrementation, i * static_cast<int>(direction.y) + static_cast<int>(direction.x) * incrementation}] != current_player) {
            complete_line = false;
        }
    }

    return complete_line;
}

template<int board_size>
bool diagonal_2_line_is_complete(const Board<board_size>& board, Player& current_player)
{
    bool complete_line = true;
    for (int i = 0; i < board_size; i++) {
        if (board[{board_size - 1 - i, i}] != current_player) {
            complete_line = false;
        }
    }

    return complete_line;
}

//checks if the player who put a cross or a nought on the board won
template<int board_size>
bool player_has_won(const Board<board_size>& board, Player& current_player)
{
    bool player_has_won = false;

    //rows
    for (int x = 0; x < board_size && !player_has_won; x++) {
        player_has_won = line_is_complete(board, current_player, {1, 0}, x);
    }

    //columns
    for (int y = 0; y < board_size && !player_has_won; y++) {
        player_has_won = line_is_complete(board, current_player, {0, 1}, y);
    }

    //diagonal top left to bottom right
    if (!player_has_won) {
        player_has_won = line_is_complete(board, current_player, {1, 1}, 0);
    }

    //diagonal top right to bottom left
    if (!player_has_won) {
        player_has_won = diagonal_2_line_is_complete(board, current_player);
    }

    if (player_has_won) {
        std::cout << player_type_name(current_player)
                  << " player won the game!" << std::endl;
    }

    return player_has_won;
}

//main function to play the game
void play_noughts_and_crosses()
{
    auto ctx = p6::Context{{1080, 1080, "NOUGHTS AND CROSSES"}};

    static const int board_size     = 3;
    auto             board          = Board<board_size>{};
    auto             current_player = Player::Crosses;

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

            //show a cross or a circle depending on the current player
            (current_player == Player::Crosses) ? draw_cross(2 / static_cast<float>(board_size), 1 / static_cast<float>(board_size), *hovered_cell, ctx) : draw_circle(2 / static_cast<float>(board_size), 1 / static_cast<float>(board_size), *hovered_cell, ctx);
        }

        draw_noughts_and_crosses(board, ctx);
    };

    //when the player clicks on a cell
    ctx.mouse_pressed = [&](p6::MouseButton event) {
        const auto pressed_cell = cell_is_hovered(event.position, board_size);

        if (!board[*pressed_cell].has_value()) {
            board[*pressed_cell] = current_player;

            //stops the game if the game is now finished
            if (player_has_won(board, current_player) || board_is_complete(board)) {
                ctx.stop();
            }

            swap_player(current_player);
        }
    };

    ctx.start();
}