#pragma once

struct Move
{
    int square;

    Move(): square(-1) {}
    Move(int input_id): square(input_id) {}
};
