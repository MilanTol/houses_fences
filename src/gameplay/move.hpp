#pragma once

struct Move
{
    char square_id;

    Move(): square_id(-1) {}
    Move(char input_id): square_id(input_id) {}
};
