#include "../gameplay/position.hpp"

int chainlength(Position& position, 
    int column, int row, 
    int d_column, int d_row,
    int team
)
{
    int count = 1;

    for (int i=1; i < 4; i++)
    {
        if (
        (column + i*d_column < 0) or (column + i*d_column > cfg::grid_size.x - 1) 
        or
        (row + i*d_row < 0) or (row + i*d_row > cfg::grid_size.y - 1)
        )
            break;
        
        else if (
            position.squares[column][row].house != team
        )
            break;

        count += i;
    }

    for (int i=1; i < 4; i++)
    {
        i = -i; //reverse direction

        if (
        (column * i*d_column < 0) or (column + i*d_column > cfg::grid_size.x - 1) 
        or
        (row + i*d_row < 0) or (row + i*d_row > cfg::grid_size.y - 1)
        )
            break;
        
        else if (
            position.squares[column][row].house != team
        )
            break;

        count += i;
    }

    return count;
}

int chainlength(Position& position, 
    int column, int row,
    int team
)
{
    if (position.squares[column][row].house != team)
        return 0;

    int result = 0;

    result += chainlength(position, column, row, 1, 0, team);
    // result += chainlength(position, column, row, 0, 1, team)*chainlength(position, column, row, 0, 1, team);
    // result += chainlength(position, column, row, 1, 1, team)*chainlength(position, column, row, 1, 1, team);
    // result += chainlength(position, column, row, 1, -1, team)*chainlength(position, column, row, 1, -1, team);

    return result;
}

int chainlength(Position& position, int team)
{
    int eval = 0;

    for (int column = 0; column < cfg::grid_size.x; column++)
    {
        for (int row = 0; row < cfg::grid_size.y; row++)
        {
            eval += chainlength(position, column, row, team);
        }
    }

    return eval;
}

float evaluation(Position& position)
{
    float eval = 0; //positive means good for player 1, negative means good for player 2.

    // if (checkWin(position))
    //     eval += (3 - 2*position.turn.current) * 10000; //if player1 wins +10000 else if player2 wins -10000
    
    eval += chainlength(position, 1);
    eval -= chainlength(position, 2);
    
    return eval;
};




bool checkStreet(Position& position, 
    int column, int row, 
    int d_column, int d_row
)
{
    int count = 1;
    int required = cfg::win_condition;

    for (int i=1; i < count; i++)
    {
        if (
        column + i*d_column < 0 or column + i*d_column > cfg::grid_size.x 
        or
        row + i*d_row < 0 or row + i*d_row > cfg::grid_size.y
        )
            break;
        
        else if (
            position.squares[column][row].house != position.turn.current
        )
            break;

        count += 1;
    }

    for (int i=1; i < count; i++)
    {
        i = -i; //reverse direction

        if (
        column * i*d_column < 0 or column + i*d_column > cfg::grid_size.x 
        or
        row + i*d_row < 0 or row + i*d_row > cfg::grid_size.y
        )
            break;
        
        else if (
            position.squares[column][row].house != position.turn.current
        )
            break;

        count += 1;
    }

    return count > required - 1;
}

bool checkWinSquare(Position& position,
    int column, int row)
{
    if (position.squares[column][row].house != position.turn.current)
        return false;

    if (checkStreet(position, column, row, 1, 0)) //check horizontal
        return true;

    else if (checkStreet(position, column, row, 0, 1)) //check vertical
        return true;

    else if (checkStreet(position, column, row, 1, 1)) //check upleft - downright diagonal
        return true;

    else if (checkStreet(position, column, row, 1, -1)) //check downleft - upright diagonal
        return true;
    
    return false;
}

bool checkWin(Position& position)
{
    for (int column = 0; column < cfg::grid_size.x; column++)
    {
        for (int row = 0; row < cfg::grid_size.y; row++)
        {
            if (checkWinSquare(position, column, row))
                return true;
        }
    }

    return false;
}