/*
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#include "Snake.h"
#include "PrintTerminal.hpp"
#include <stdlib.h>     /* srand, rand */

using namespace std;

PrintCanvas printCanvas;
PrintTable  printTable1( 3,  1);
PrintTable  printTable2( 3, 39);
PrintTable  printTable3(17,  1);
PrintTable  printTable4(17, 39);
PrintSquare printSquare0( 1,  1);
PrintSquare printSquare1( 2,  1);
PrintSquare printSquare2( 2, 39);
PrintSquare printSquare3(16,  1);
PrintSquare printSquare4(16, 39);

vector<Point> get_empty_field(Map map, SnakePosition snake)
{
    vector<Point> ret;
    while(!snake.empty())
    {
        map[snake.front()] = -1;
        snake.pop();
    }
    for(int i = 0;i < map.max_x();++i)
    {
        for(int j = 0;j < map.max_y();++j)
        {
            if(map[i][j] == 0)
                ret.push_back(Point{i, j});
        }
    }
    return ret;
}
void add_foods(Map& map, const SnakePosition& snake, int amount = 1)
{
    vector<Point> empty_field = get_empty_field(map, snake);
    while(amount--)
    {
        auto random_p = empty_field.begin() + (rand() % empty_field.size());
        map[*random_p] = (rand() % 10) + 10;
        empty_field.erase(random_p);
    }
}

int main()
{
    SnakePosition pos { queue<Point>({ {5, 1}, {5, 2}, {5, 3}, {4, 3}}) };

    Map map { vector<vector<int>> {
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
        {-1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
        {-1,  0, -1, -1, -1,  0,  0,  0,  0,  0, -1},
        {-1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
        {-1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
        {-1, -1, -1, -1, -1,  0,  0,  0,  0,  0, -1},
        {-1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
        {-1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
        {-1,  0,  0,  0,  0,  0,  0,  0,  0,  0, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
    } };

    add_foods(map, pos, 2);
    Snake snake(pos.convert_to_tuple());
    cin.get(); // pause

    while(true)
    {
        SnakePosition pos_new = snake.nextPosition(map.convert_to_vector());
        cin.get(); // pause

        Point& head_new = pos_new.back();
        Map map_o(map);
        Solver::snake_body_as_obstacle(map_o, pos_new);
        if(map_o[head_new] == -1)
        {
            break;
        }
        if(map[head_new] != 0)
        {
            map[head_new] = 0;
            add_foods(map, pos_new);
        }
        pos = pos_new;
    }

    return 0;
}

