/*
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#ifndef SNAKE_H
#define SNAKE_H

#include <queue>
#include <tuple>
#include <vector>
#include <stack>
#include <utility> // pair, tuple
#include <list>

#ifdef SNAKE_TESTING
#include "PrintTerminal.hpp"
#endif // SNAKE_TESTING

using namespace std;

/* ---------- Base Element ---------- */
class Point
{
public:
    Point();
    Point(const int& x, const int& y);
    Point(const tuple<int, int>& p);
    Point operator+(const Point& p) const;
    Point operator-(const Point& p) const;
    bool operator==(const Point& p) const;
    int x, y;
};

class SnakePosition: public queue<Point>
{
public:
    SnakePosition();
    SnakePosition(queue<Point> qu);
    SnakePosition(queue<tuple<int, int>> qu);
    void reverse();
    queue<tuple<int, int>> convert_to_tuple() const;
#ifdef SNAKE_TESTING
    /* print */
    void print_on_table(PrintTable& table) const;
    void print_comment(PrintSquare& square) const;
#endif // SNAKE_TESTING
#ifdef GRADING_TESTING
    void print_comment() const;
#endif // GRADING_TESTING
};

class SnakePath: public list<Point> // begin: front
{
public:
    SnakePath();
#ifdef SNAKE_TESTING
    void print_on_table(PrintTable& table) const;
#endif // SNAKE_TESTING
};

class Map
{
public:
    Map(vector<vector<int>> data);
    vector<vector<int>> convert_to_vector() const;
    int max_x() const;
    int max_y() const;
    const int& operator[](const Point& p) const;
          int& operator[](const Point& p)      ;
    const vector<int>& operator[](const int& x) const;
          vector<int>& operator[](const int& x)      ;
#ifdef SNAKE_TESTING
    void print_on_table(PrintTable& table) const;
#endif // SNAKE_TESTING
#ifdef GRADING_TESTING
    void print_on_table() const;
#endif // GRADING_TESTING
private:
    vector<vector<int>> _data;
};

/* ---------- Snake ---------- */
class Snake
{
public:
    /* interface */
    Snake(const queue<tuple<int, int>>& startPosition);
    queue<tuple<int, int>> nextPosition(const vector<vector<int>>& currentMap); // return next snake

private:
    SnakePosition current_position;
};

/* ---------- Solver ---------- */
namespace Solver
{
    using PointScore = pair<Point, int>;

    /* util class */
    class VisitMap // [TODO] make member variable static (consider different map size)
    {
    public:
        VisitMap(const int& x, const int& y);
        VisitMap(const Map& map);
        void visit(const Point& p);
        bool is_visited(const Point& p);
        void new_visit_round();
    private:
        vector<vector<int>> _visited;
        int _visit_n;
    };

    struct pointscore_distance_less // [TODO] check
    {
        inline bool operator() (const pair<PointScore, int>& A, const pair<PointScore, int>& B);
    };
    struct pointscore_score_more
    {
        inline bool operator() (const pair<PointScore, int>& A, const pair<PointScore, int>& B);
    };

    /* util functions */
    /* Map preparing */
    void snake_body_as_obstacle(Map& map, SnakePosition snake);
    void score_point_to_zero(Map& map);
    void obstacle_to_max(Map& map);
    void snake_as_order(Map& map, SnakePosition snake);

    /* about container */
    list<Point> stack_to_list(const stack<Point>& st);
    stack<Point> list_to_stack(const list<Point>& li);

    /* other */
    Map generate_step_map_bfs(Map map, const SnakePosition& snake); // using BFS calculate step to any block
    SnakePath track_path(const Map& step_map, Point p);
    vector<PointScore> find_all_score_point(const Map& map);
    SnakePosition get_virtual_snake(SnakePosition snake, const SnakePath& path, bool ate_food = false);
    SnakePath get_shortest_path(const Map& map, SnakePosition snake, const Point& t);
    SnakePath get_longest_path(const Map& map, SnakePosition snake, const Point& t);

    class BaseSolver
    {
    public:
        BaseSolver(const Map& current_map);
        virtual ~BaseSolver();
        virtual Point next_position(const SnakePosition& current_position) = 0;
    protected:
        Map current_map;
    };
    class BFSSolver: public BaseSolver
    {
    public:
        BFSSolver(const Map& current_map);
        Point next_position(const SnakePosition& current_position);
    private:
        SnakePath path_1;
    };
    class GreedySolver: public BaseSolver
    {
    public:
        GreedySolver(const Map& current_map);
        Point next_position(const SnakePosition& current_position);
    private:
        SnakePath path_1, path_2;
    };
}

#endif // SNAKE_H
