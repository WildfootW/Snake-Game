/*
 * Author: WildfootW
 * GitHub: github.com/WildfootW
 * Copyleft (C) 2020 WildfootW all rights reversed
 */

#include "Snake.h"
#include <string>
#include <limits>
#include <algorithm>

#ifdef SNAKE_TESTING
extern PrintTable  printTable1;
extern PrintTable  printTable2;
extern PrintTable  printTable3;
extern PrintTable  printTable4;
extern PrintSquare printSquare0;
extern PrintSquare printSquare1;
extern PrintSquare printSquare2;
extern PrintSquare printSquare3;
extern PrintSquare printSquare4;
#endif // SNAKE_TESTING

#ifdef GRADING_TESTING
#include <iostream>
#endif // GRADING_TESTING

/* Base Element */
/* ---------- class Point ---------- */
Point::Point() {}
Point::Point(const int& x, const int& y): x(x), y(y) {}
Point::Point(const tuple<int, int>& p): x(get<0>(p)), y(get<1>(p)) {}
Point Point::operator+(const Point& p) const { Point ret(*this); ret.x += p.x; ret.y += p.y; return ret; }
Point Point::operator-(const Point& p) const { Point ret(*this); ret.x -= p.x; ret.y -= p.y; return ret; }
bool Point::operator==(const Point& p) const { return (x == p.x && y == p.y); }

/* ---------- class SnakePosition ---------- */
SnakePosition::SnakePosition() {}
SnakePosition::SnakePosition(queue<Point> qu): queue<Point>(qu) {}
SnakePosition::SnakePosition(queue<tuple<int, int>> qu)
{
    while(!qu.empty())
    {
        push(Point(qu.front()));
        qu.pop();
    }
    //reverse();
}
void SnakePosition::reverse()
{
    stack<Point> st;
    while(!empty())
    {
        st.push(front());
        pop();
    }
    while(!st.empty())
    {
        push(st.top());
        st.pop();
    }
}
queue<tuple<int, int>> SnakePosition::convert_to_tuple() const
{
    queue<tuple<int, int>> ret;
    SnakePosition tmp(*this);
    //tmp.reverse();
    while(!tmp.empty())
    {
        ret.push(make_tuple(tmp.front().x, tmp.front().y));
        tmp.pop();
    }
    return ret;
}
#ifdef SNAKE_TESTING
void SnakePosition::print_on_table(PrintTable& table) const
{
    SnakePosition position(*this);
    int i = 0;
    while(!position.empty())
    {
        table.modify_cell(position.front().x, position.front().y, "S" + to_string(i++));
        position.pop();
    }
}
void SnakePosition::print_comment(PrintSquare& square) const
{
    SnakePosition position(*this);
    string comment;
    comment.append("tail {");
    while(!position.empty())
    {
        comment.append("(");
        comment.append(to_string(position.front().x));
        comment.append(", ");
        comment.append(to_string(position.front().y));
        comment.append(")");
        position.pop();
    }
    comment.append("} head");
    square.print(comment);
}
#endif // SNAKE_TESTING
#ifdef GRADING_TESTING
void SnakePosition::print_comment() const
{
    SnakePosition position(*this);
    cout << "tail {";
    while(!position.empty())
    {
        cout << "(" << position.front().x << ", " << position.front().y << ")";
        position.pop();
    }
    cout << "} head" << endl;
}
#endif // GRADING_TESTING

/* ---------- class SnakePath ---------- */
SnakePath::SnakePath(){}
#ifdef SNAKE_TESTING
void SnakePath::print_on_table(PrintTable& table) const
{
    int i = 0;
    for(auto it = begin();it != end();++it)
    {
        table.modify_cell((*it).x, (*it).y, "P" + to_string(i++));
    }
}
#endif // SNAKE_TESTING

/* ---------- class Map ---------- */
Map::Map(vector<vector<int>> data): _data(data){}
vector<vector<int>> Map::convert_to_vector() const
{
    return _data;
}
int Map::max_x() const { return _data.size(); }
int Map::max_y() const { return _data[0].size(); }
const int& Map::operator[](const Point& p) const { return _data[p.x][p.y]; }
      int& Map::operator[](const Point& p)       { return _data[p.x][p.y]; }
const vector<int>& Map::operator[](const int& x) const { return _data[x]; }
      vector<int>& Map::operator[](const int& x)       { return _data[x]; }
#ifdef SNAKE_TESTING
void Map::print_on_table(PrintTable& table) const
{
    table.set_max_column_row(max_x(), max_y());
    for(int i = 0; i < max_x(); ++i)
    {
        for(int j = 0; j < max_y(); ++j)
        {
            table.modify_cell(i, j, _data[i][j]);
        }
    }
}
#endif // SNAKE_TESTING
#ifdef GRADING_TESTING
void Map::print_on_table() const
{
    for(int i = 0; i < max_x(); ++i)
    {
        for(int j = 0; j < max_y(); ++j)
        {
            cout << _data[i][j] << " ";
        }
        cout << endl;
    }
}
#endif // GRADING_TESTING


/* ---------- class Snake ---------- */
    /* interface */
Snake::Snake(const queue<tuple<int, int>>& startPosition): current_position(startPosition)
{
#ifdef SNAKE_TESTING
    current_position.print_comment(printSquare1);
#endif // SNAKE_TESTING
#ifdef GRADING_TESTING
    current_position.print_comment();
#endif // GRADING_TESTING
}

queue<tuple<int, int>> Snake::nextPosition(const vector<vector<int>>& currentMap) // return next snake
{
#ifdef GRADING_TESTING
    cout << "---------- new round ----------" << endl;
#endif // GRADING_TESTING
    Map current_map(currentMap);

    static Solver::BaseSolver* solver = nullptr;
    if(solver == nullptr)
        solver = new Solver::GreedySolver(current_map);
        //solver = new Solver::BFSSolver(current_map);
    Point new_head = solver->next_position(current_position);

    /* execute */
    current_position.push(new_head);
    if(current_map[new_head] == 0) // doesn't get score
    {
        current_position.pop();
    }
    else
    {
        delete solver;
        solver = nullptr;
    }
#ifdef SNAKE_TESTING
    current_map.print_on_table(printTable1);
    current_position.print_on_table(printTable1);
    current_position.print_comment(printSquare1);
#endif // SNAKE_TESTING
#ifdef GRADING_TESTING
    current_map.print_on_table();
    current_position.print_comment();
#endif // GRADING_TESTING

    return current_position.convert_to_tuple();
}

/* Solver */
namespace Solver
{
/* util class */
VisitMap::VisitMap(const int& x, const int& y): _visited(x, vector<int>(y, 0)), _visit_n(0) {}
VisitMap::VisitMap(const Map& map): VisitMap(map.max_x(), map.max_y()) {}
void VisitMap::visit(const Point& p) { _visited[p.x][p.y] = _visit_n; }
bool VisitMap::is_visited(const Point& p) { return _visited[p.x][p.y] == _visit_n; }
void VisitMap::new_visit_round() { ++_visit_n; }

inline bool pointscore_distance_less::operator() (const pair<PointScore, int>& A, const pair<PointScore, int>& B)
{
    return (A.second < B.second);
}
inline bool pointscore_score_more::operator() (const pair<PointScore, int>& A, const pair<PointScore, int>& B)
{
    return (A.first.second < B.first.second);
}

/* util functions */
void snake_body_as_obstacle(Map& map, SnakePosition snake)
{
    while(snake.size() != 1) // reserve snake head
    {
        Point tu = snake.front();
        map[tu] = -1;
        snake.pop();
    }
}
void score_point_to_zero(Map& map)
{
    for(int i = 0;i < map.max_x();++i)
        for(int j = 0;j < map.max_y();++j)
            if(map[i][j] != 0 && map[i][j] != -1)
                map[i][j] = 0;
}
void obstacle_to_max(Map& map)
{
    for(int i = 0;i < map.max_x();++i)
        for(int j = 0;j < map.max_y();++j)
            if(map[i][j] == -1)
                map[i][j] = numeric_limits<int>::max();
}
void snake_as_order(Map& map, SnakePosition snake)
{
    for(int i = 0;!snake.empty();++i) // tail as 0
    {
        Point tu = snake.front();
        map[tu] = i;
        snake.pop();
    }
}

list<Point> stack_to_list(const stack<Point>& st)
{
     const Point* end   = &st.top() + 1;
     const Point* begin = end - st.size();
     return list<Point>(begin, end);
}

stack<Point> list_to_stack(const list<Point>& li)
{
    stack<Point> ret;
    for(auto e:li)
    {
        ret.push(e);
    }
    return ret;
}

Map generate_step_map_bfs(Map ret, const SnakePosition& snake)
{
    // prepare map (map_s record visit and obstacle)
    score_point_to_zero(ret);
    Map map_s(ret);
    snake_as_order(map_s, snake);
    obstacle_to_max(map_s);

    // generate (BFS)
    Point head = snake.back();
    queue<Point> qu;
    qu.push(head);
    map_s[head] = numeric_limits<int>::max();
    ret[head] = 0;
    while(!qu.empty())
    {
        Point dp[4] = {Point(-1, 0), Point(0, -1), Point(1, 0), Point(0, 1)};
        Point current = qu.front();
        qu.pop();
        for(int i = 0;i < 4;++i)
        {
            Point near = current + dp[i];
            if(map_s[near] > ret[current]) continue;
            ret[near] = ret[current] + 1;
            qu.push(near);
            map_s[near] = numeric_limits<int>::max();
        }
    }
    return ret;
}

SnakePath track_path(const Map& step_map, Point p)
{
    SnakePath ret;
    Point dp[4] = {Point(-1, 0), Point(0, -1), Point(1, 0), Point(0, 1)};
    while(step_map[p] != 0)
    {
        ret.push_front(p);
        for(int i = 0;i < 4;++i)
        {
            Point near = p + dp[i];
            if(step_map[near] == (step_map[p] - 1))
            {
                p = near;
                break;
            }
        }
    }
    return ret;
}

vector<PointScore> find_all_score_point(const Map& map)
{
    vector<PointScore> ret;
    for(int i = 0;i < map.max_x();++i)
        for(int j = 0;j < map.max_y();++j)
            if(map[i][j] > 0) ret.push_back(make_pair(Point(i, j), map[i][j]));
    return ret;
}

SnakePosition get_virtual_snake(SnakePosition snake, const SnakePath& path, bool ate_food)
{
    auto it = path.begin();
    if(ate_food) // eat first
    {
        snake.push(*path.begin());
        it = next(it);
    }
    for(;it != path.end();++it)
    {
        snake.push(*it);
        snake.pop();
    }
    return snake;
}

SnakePath get_shortest_path(const Map& map, SnakePosition snake, const Point& t)
{
    return track_path(generate_step_map_bfs(map, snake), t);
}

SnakePath get_longest_path(const Map& map, SnakePosition snake, const Point& t)
{
    SnakePath path = get_shortest_path(map, snake, t);
    if(path.empty()) // not reachable
        return path;
    path.push_front(snake.back()); // add snake head

    Map map_s(map); // special map for check if path can through
    // confirm path and obstacle become max & snake's order
    snake_as_order(map_s, snake);
    for(auto e:path)
        map_s[e] = -1;
    obstacle_to_max(map_s);

#ifdef SNAKE_TESTING
    map_s.print_on_table(printTable3);
#endif // SNAKE_TESTING

    auto it = path.begin();
    int idx = 0;
    while(it != prev(path.end()))
    {
        const Point& c = *(it);
        const Point& n = *(next(it, 1));
        pair<Point, Point> test[2]; // two side
        if(c.x == n.x)
        {
            test[0].first  = c + Point( 1, 0);
            test[0].second = n + Point( 1, 0);
            test[1].first  = c + Point(-1, 0);
            test[1].second = n + Point(-1, 0);
        }
        if(c.y == n.y)
        {
            test[0].first  = c + Point(0,  1);
            test[0].second = n + Point(0,  1);
            test[1].first  = c + Point(0, -1);
            test[1].second = n + Point(0, -1);
        }
        bool flag_append_success = false;
        for(int i = 0;i < 2;++i)
        {
            if(idx + 1 > map_s[test[i].first] && idx + 2 > map_s[test[i].second]) // pass the test
            {
                path.insert(next(it, 1), test[i].first );
                path.insert(next(it, 2), test[i].second);
                map_s[test[i].first ] = numeric_limits<int>::max();
                map_s[test[i].second] = numeric_limits<int>::max();
                flag_append_success = true;
                break;
            }
        }
        if(!flag_append_success) { ++it; ++idx; }
    }
    path.pop_front(); // remove snake head
    return path;
}


/* class Solver */
BaseSolver::BaseSolver(const Map& current_map): current_map(current_map) {}
BaseSolver::~BaseSolver() {}

BFSSolver::BFSSolver(const Map& current_map): BaseSolver(current_map){}

Point BFSSolver::next_position(const SnakePosition& current_position)
{
    Point new_head;
#ifdef SNAKE_TESTING
    Map print_empty_map(current_map);
    score_point_to_zero(print_empty_map);
#endif // SNAKE_TESTING

    /* Strategy 1 */
    /* go to nearest reachable PointScore */
    if(path_1.empty())
    {
        Map bfs_step_map = generate_step_map_bfs(current_map, current_position);
#ifdef SNAKE_TESTING
        print_empty_map.print_on_table(printTable2);
        bfs_step_map.print_on_table(printTable2);
#endif // SNAKE_TESTING

        vector<PointScore> score_set = find_all_score_point(current_map);
        vector<pair<PointScore, int>> score_step_set;
        for(auto e:score_set)
        {
            if(bfs_step_map[e.first] != 0)
                score_step_set.push_back(make_pair(e, bfs_step_map[e.first]));
        }
        if(!score_step_set.empty())
        {
            //sort(score_step_set.begin(), score_step_set.end(), pointscore_distance_less());
            sort(score_step_set.begin(), score_step_set.end(), pointscore_score_more());
            SnakePath path = track_path(bfs_step_map, score_step_set[0].first.first);
            path_1 = path;
        }
    }
    if(!path_1.empty()) // follow previous decided path
    {
#ifdef SNAKE_TESTING
        printSquare0.print("Strategy 1: {output} {input & path_1} {bfs step map}");
        print_empty_map.print_on_table(printTable3);
        current_position.print_on_table(printTable3);
        path_1.print_on_table(printTable3);
#endif // SNAKE_TESTING
        new_head = path_1.front();
        path_1.pop_front();
        return new_head;
    }

    /* Strategy 2 */
    /* Go to near empty block */
    new_head = current_position.back();
    Map virtual_map(current_map);
    snake_body_as_obstacle(virtual_map, current_position);
    if(virtual_map[new_head.x - 1][new_head.y] != -1) { --new_head.x; }
    else if(virtual_map[new_head.x][new_head.y - 1] != -1) { --new_head.y; }
    else if(virtual_map[new_head.x + 1][new_head.y] != -1) { ++new_head.x; }
    else { ++new_head.y; }
    return new_head;
}


GreedySolver::GreedySolver(const Map& current_map): BaseSolver(current_map){}

Point GreedySolver::next_position(const SnakePosition& current_position)
{
    Point new_head;
#ifdef SNAKE_TESTING
    Map print_empty_map(current_map);
    score_point_to_zero(print_empty_map);
#endif // SNAKE_TESTING

    /* Strategy 1 */
    /* find to nearest PointScore that can go to S2's tail */
    if(path_1.empty())
    {
        Map bfs_step_map = generate_step_map_bfs(current_map, current_position);
#ifdef SNAKE_TESTING
        print_empty_map.print_on_table(printTable4);
        bfs_step_map.print_on_table(printTable4);
#endif // SNAKE_TESTING

        vector<PointScore> score_set = find_all_score_point(current_map);
        vector<pair<PointScore, int>> score_step_set;
        for(auto e:score_set)
        {
            score_step_set.push_back(make_pair(e, bfs_step_map[e.first]));
        }
        //sort(score_step_set.begin(), score_step_set.end(), pointscore_distance_less());
        sort(score_step_set.begin(), score_step_set.end(), pointscore_score_more());
        for(auto e:score_step_set)
        {
            SnakePath path = track_path(bfs_step_map, e.first.first);
            if(path.empty())
                continue;
            SnakePosition virtual_snake = get_virtual_snake(current_position, path, true);
            SnakePath virtual_path = get_shortest_path(current_map, virtual_snake, virtual_snake.front());
            if(!virtual_path.empty())
            {
#ifdef SNAKE_TESTING
                print_empty_map.print_on_table(printTable3);
                virtual_snake.print_on_table(printTable3);
                virtual_path.print_on_table(printTable3);
#endif // SNAKE_TESTING
                path_1 = path;
            }
        }
    }
    if(!path_1.empty()) // follow previous decided path
    {
#ifdef SNAKE_TESTING
        printSquare0.print("Strategy 1: {output} {input & path_1} {virtual snake & path} {bfs step map}");
        print_empty_map.print_on_table(printTable2);
        current_position.print_on_table(printTable2);
        path_1.print_on_table(printTable2);
#endif // SNAKE_TESTING
        new_head = path_1.front();
        path_1.pop_front();
        return new_head;
    }

    /* Strategy 2 */
    /* logest path to its own tail */
    if(path_2.empty())
    {
#ifdef SNAKE_TESTING
        print_empty_map.print_on_table(printTable3);
#endif // SNAKE_TESTING
        SnakePath path = get_longest_path(current_map, current_position, current_position.front());
        path_2 = path;
    }
    if(!path_2.empty())  // follow previous decided path
    {
#ifdef SNAKE_TESTING
        printSquare0.print("Strategy 2: {output} {input & path_2} {map_s               } {bfs step map}");
        print_empty_map.print_on_table(printTable2);
        current_position.print_on_table(printTable2);
        path_2.print_on_table(printTable2);
#endif // SNAKE_TESTING
        new_head = path_2.front();
        path_2.pop_front();
        return new_head;
    }

    /* Strategy 3 */
    /* Go to near empty block */ /* farthest from the food [TODO] */
    new_head = current_position.back();
    Map virtual_map(current_map);
    snake_body_as_obstacle(virtual_map, current_position);
    if(virtual_map[new_head.x - 1][new_head.y] != -1) { --new_head.x; }
    else if(virtual_map[new_head.x][new_head.y - 1] != -1) { --new_head.y; }
    else if(virtual_map[new_head.x + 1][new_head.y] != -1) { ++new_head.x; }
    else { ++new_head.y; }
    return new_head;
}

}
