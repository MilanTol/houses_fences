
#include "../config.hpp"
#include "../gameplay/position.hpp"
#include "input.hpp"

struct ColumnRow
{
    int column;
    int row;

    ColumnRow(): column(-1), row(-1) {}

    ColumnRow(sf::Vector2i position)
    {
        column = position.x / cfg::square_size.x;
        row = position.y / cfg::square_size.y;

        std::cout << column << row << std::endl;
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
            std::cout << clicked_square.column << clicked_square.row << std::endl;

            displayed_position.playTurn(clicked_square.column, clicked_square.row);
            positions.push_back(displayed_position);
            turns_played += 1;
            displayed_position_id = turns_played;
            input.mouseClicked = false;
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

