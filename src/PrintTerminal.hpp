/*
 * PrintTable.hpp
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#ifndef PRINTTERMINAL_HPP
#define PRINTTERMINAL_HPP

#include <iostream>
#include <iomanip>

using namespace std;

// class PrintElement (Base)
//      class PrintTable
//      class PrintSquare

class PrintTerminalPosition
{
public:
    // x: row y: column
    PrintTerminalPosition(int x, int y): x(x), y(y) {}
    int x, y;
    PrintTerminalPosition operator+ (const PrintTerminalPosition& obj)
    {
        return PrintTerminalPosition(x + obj.x, y + obj.y);
    }
};

class PrintElement
{
public:
    PrintElement(int start_x, int start_y);
    void _move_to(int relative_x, int relative_y);
    void _move_to(PrintTerminalPosition relative);
protected:
    PrintTerminalPosition top_left_corner;
};

class PrintSquare: public PrintElement
{
public:
    PrintSquare(int start_x, int start_y, int max_width = -1, int max_length = -1);
    void print(string str);
private:
    int max_width; // -1 for infinite
    int max_length;
};

class PrintTable: public PrintElement
{
public:
    PrintTable(int start_x, int start_y, int cell_length = 3);

    void set_max_column_row(int max_column, int max_row);
    template <class Data>
    void modify_cell(int column, int row, Data data, bool fix_length = true);

private:
    int _max_column, _max_row;
    int _cell_length;

    template <class Data>
    inline void _print_fix_cell(Data str, ios_base &(*positioning)(ios_base &) = right);

    // cutomize print out message
    // z.B. print INF while int == 2147483647
    inline string _fixstr(string para) const;
    inline string _fixstr(char para) const;
    inline string _fixstr(int para) const;
};

class PrintCanvas: public PrintElement
{
public:
    PrintCanvas();
    ~PrintCanvas();
};

#endif // PRINTTERMINAL_HPP
