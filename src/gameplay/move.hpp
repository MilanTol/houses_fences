#pragma once

struct Move
{
    char square;

    Move(): square(-1) {}
    Move(char input_id): square(input_id) {}
};
