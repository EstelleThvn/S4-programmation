#include "play_noughts_and_crosses.hpp"
#include <p6/p6.h>
#include <iostream>

struct BoardCell {
    int x;
    int y;
    int size;
};

void draw_board(int size, p6::Context& ctx)
{
    const float cell_size = 2 / static_cast<float>(size);
    const float radius    = 1 / static_cast<float>(size);

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            ctx.square(p6::TopLeftCorner{-ctx.aspect_ratio() + static_cast<float>(x) * cell_size, 1.f - static_cast<float>(y) * cell_size}, radius);
        }
    }
}

void play_noughts_and_crosses()
{
    auto ctx   = p6::Context{{1080, 1080, "NOUGHTS AND CROSSES"}};
    ctx.update = [&]() {
        ctx.background({0.1, 0., 0.2});
        ctx.stroke        = {0.1, 0., 0.2};
        ctx.stroke_weight = 0.02f;
        ctx.fill          = {.25, .22, .32};
        draw_board(3, ctx);
    };
    ctx.start();
}