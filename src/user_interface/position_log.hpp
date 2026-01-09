
#include "input.hpp"

#include "../config.hpp"

#include "../gameplay/position.hpp"
#include "../gameplay/move.hpp"

#include "../engine/evaluation.hpp"
#include "../engine/find_best_move.hpp"


struct ColumnRow
{
    int column;
    int row;

    ColumnRow(): column(-1), row(-1) {}

    ColumnRow(sf::Vector2i position)
    {
        column = position.x / cfg::square_size.x;
        row = position.y / cfg::square_size.y;
    }

    char square_id()
    {
        return column + cfg::grid_size.x * row;
    }
};

class Position_Log
{

public:

    std::vector<Position> positions;   
    Position displayed_position;

    int turns_played;
    int displayed_position_id;   

    Position_Log():
        turns_played(0),
        displayed_position_id(0)
    {
        positions.push_back(Position());
        displayed_position = positions[displayed_position_id];
    }

    void processEvents(sf::RenderWindow& window, Input& input)
    {
        if (input.mouseClicked and not (displayed_position_id == turns_played))
        {
            input.mouseClicked = false;
            displayed_position_id = turns_played;
        }
        
        else if (input.mouseClicked and displayed_position_id == turns_played) // if clicked
        {   
            ColumnRow clicked_square = ColumnRow(sf::Mouse::getPosition(window));
            displayed_position.makeMove(Move(clicked_square.column + cfg::grid_size.x * clicked_square.row));
            
            positions.push_back(displayed_position);
            turns_played += 1;
            displayed_position_id = turns_played;
            input.mouseClicked = false;

            if (displayed_position.turn.current == 2)
            {            
                int depth = 2;
                
                Move bestMove = findBestMove(displayed_position, depth);
                displayed_position.makeMove(bestMove);

                positions.push_back(displayed_position);
                turns_played += 1;
                displayed_position_id = turns_played;

                bestMove = findBestMove(displayed_position, depth);
                displayed_position.makeMove(bestMove);

                positions.push_back(displayed_position);
                turns_played += 1;
                displayed_position_id = turns_played;

                // int eval = -negamax(displayed_position, depth, -10000, 10000);
                int eval = evaluate(displayed_position);
                std::cout << eval << std::endl;
            }
        }
        
        if (input.downPressed and turns_played > 0)
        {   
            input.downPressed = false;
        
            displayed_position = positions[turns_played - 1];
            positions.pop_back();
        
            turns_played -= 1;
            displayed_position_id = turns_played;
        }
        
        if (input.leftPressed and displayed_position_id > 0)
        {   
            input.leftPressed = false;
        
            displayed_position_id -= 1;
        }
        
        if (input.rightPressed and displayed_position_id < turns_played)
        {    
            input.rightPressed = false;
        
            displayed_position_id += 1;
        }

        displayed_position = positions[displayed_position_id];
    }

};

