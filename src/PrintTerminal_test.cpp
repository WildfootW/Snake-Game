/*
 * PrintTable.hpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#include <vector>
#include "PrintTerminal.hpp"

using namespace std;

int main(void)
{
    PrintCanvas print_canvas;

    PrintTable print_table(3, 3, 3);
    vector<vector<int>> table = {
        {-1, -1, -1, -1, -1},
        {-1,  0,  0,  0, -1},
        {-1,  0,  0,  0, -1},
        {-1,  0,  2,  2, -1},
        {-1,  0,  0,  0, -1},
        {-1, -1, -1, -1, -1},
    };
    print_table.set_max_column_row(table.size(), table[0].size());
    for(int i = 0;i < table.size();++i)
    {
        for(int j = 0;j < table[0].size();++j)
        {
            print_table.modify_cell(i, j, table[i][j]);
        }
    }

    PrintSquare print_square(10, 5);
    print_square.print("Copyleft (C) 2020 WildfootW all rights reversed\nTest Comment");

    return 0;
}
