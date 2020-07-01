/*
 * PrintTable.hpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#include <iostream>
#include <iomanip>
#include "PrintTerminal.hpp"

using namespace std;

PrintElement::PrintElement(int start_x, int start_y): top_left_corner(start_x, start_y) {}
void PrintElement::_move_to(int relative_x, int relative_y)
{
    _move_to(PrintTerminalPosition(relative_x, relative_y));
}
void PrintElement::_move_to(PrintTerminalPosition relative)
{
    cout << "\e[" << top_left_corner.x + relative.x << ";" << top_left_corner.y + relative.y << "H";
}

/* PrintSquare */

PrintSquare::PrintSquare(int start_x, int start_y, int max_width, int max_length): PrintElement(start_x, start_y), max_width(max_width), max_length(max_length) {}
void PrintSquare::print(string str)
{
    _move_to(0, 0);
    cout << str;
}

/* PrintTable */

PrintTable::PrintTable(int start_x, int start_y, int cell_length): PrintElement(start_x, start_y), _cell_length(cell_length)
{
}

template <class Data>
inline void PrintTable::_print_fix_cell(Data data, ios_base &(*positioning)(ios_base &))
{
    cout << positioning << setw(_cell_length) << _fixstr(data);
}

void PrintTable::set_max_column_row(int max_column, int max_row)
{
    _max_column = max_column;
    _max_row = max_row;
    _move_to(0, 0);
    _print_fix_cell("");
    for(int i = 0;i < _max_column;++i)
    {
        _print_fix_cell(i);
    }
    for(int i = 0;i < _max_row;++i)
    {
        _move_to(i + 1, 0);
        _print_fix_cell(i, left);
    }
}

/* move to header */
template <class Data>
void PrintTable::modify_cell(int column, int row, Data data, bool fix_length)
{
    _move_to(row + 1, (column + 1) * _cell_length);
    _print_fix_cell(data);
}
/* ** implement ** */
template void PrintTable::modify_cell<int>(int column, int row, int data, bool fix_length);
template void PrintTable::modify_cell<char>(int column, int row, char data, bool fix_length);
template void PrintTable::modify_cell<string>(int column, int row, string data, bool fix_length);

inline string PrintTable::_fixstr(string para) const
{
//    para.resize(cell_length, ' ');
    return para;
}
inline string PrintTable::_fixstr(char para) const
{
    string ret = string(1, para);
    return _fixstr(ret);
}
inline string PrintTable::_fixstr(int para) const
{
    string ret = to_string(para);
//    if(para == INF) ret = "INF";
    return _fixstr(ret);
}

/* PrintCanvas */

PrintCanvas::PrintCanvas(): PrintElement(1, 1)
{
    cout << "\e[2J"; // claer screen
}
PrintCanvas::~PrintCanvas()
{
    _move_to(30, 0);
}

