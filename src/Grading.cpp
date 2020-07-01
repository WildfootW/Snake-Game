#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
#include <cmath>
#include <sstream>
#include <fstream>
#include <cstring>
#include <ctime>

#include "Snake.h"

using namespace std;

void loadmaps(vector<vector<int>> map[101]) {
    //    vector<vector<int>> map[101]; //maps
    fstream file;
    char buffer[150];
    string fname;
    for (int i = 1; i < 101; i++) {
        if (i < 10)
            fname = "00" + to_string(i);
        else if (i < 100)
            fname = "0" + to_string(i);
        else
            fname = to_string(i);
        file.open("./Data/maps/map_" + fname, ios::in);
        if (!file) {
            cout << "no file" << endl;
        }
        else {
            do {
                vector<int> tempv;
                file.getline(buffer, sizeof(buffer));
                const char* d = " "; //分割依據
                char *row; //儲存每次分割結果
                row = strtok(buffer, d);
                while (row) {
                    string s = row;
                    int temp = stoi(s);
                    tempv.push_back(temp);
                    row = strtok(NULL, d);
                }
                map[i].push_back(tempv);
            } while (!file.eof());
        }
        file.close();
    }
}

//(所有地圖,下一張地圖,蛇的位置)
vector<vector<int>> generate_map(vector<vector<int>> map[101], int mapindex, queue<tuple<int, int>> snack) {
    tuple<int, int> position;
    int row, col;
    int flag3 = 0;
    int flag5 = 0;
    int flag7 = 0;
    int flagall = 0;

    //尋找地圖得分點位置
    for (int m = 0; m < 50; m++) {
        for (int n = 0; n < 50; n++) {
            if (map[mapindex][m][n] == 1) {
                row = m;
                col = n;
                position = make_tuple(m, n);
            }
        }
    }

    //判斷得分點有沒有在蛇身上
    int flag = 0;
    queue<tuple<int, int>> tempsnack = snack;
    while (!tempsnack.empty() && flag == 0) {
        if (tempsnack.front() == position) {
            flag = 1;
        }
        tempsnack.pop();
    }
    if (flag == 0)
        return map[mapindex];
    else {
        //      3*3找新得分點
        for (int i = row - 1; i < row + 2; i++) {
            if (i > 0 && i < 49 && flag3 == 0) {
                for (int j = col - 1; j < col + 2; j++) {
                    if (j > 0 && j < 49 && flag3 == 0) {
                        tempsnack = snack;
                        flag = 0;
                        position = make_tuple(i, j);
                        //每一個點跟蛇的位置比較，有找到
                        while (!tempsnack.empty() && flag == 0) {
                            if (tempsnack.front() == position) {
                                flag = 1;
                            }
                            tempsnack.pop();
                        }
                        if (flag == 0) {
                            flag3 = 1;//在3*3中找到可以放點的地方
                            row = i;//新點index
                            col = j;
                            break;
                        }
                    }
                    if (flag3 == 1)
                        break;
                }
            }
            if (flag3 == 1) {
                break;
            }
        }
        if (flag3 == 1) {  //3*3找到
            vector<vector<int>> newmap;
            for (int i = 0; i < 50; i++) {
                vector<int> tempv;
                for (int j = 0; j < 50; j++) {
                    if (i == 0 || i == 49) {
                        tempv.push_back(-1);
                    }
                    else {
                        if (i == row && j == col) {
                            tempv.push_back(1);
                        }
                        else if (j == 0 || j == 49)
                            tempv.push_back(-1);
                        else
                            tempv.push_back(0);
                    }
                }
                newmap.push_back(tempv);
            }
            return newmap;
        }
        else if (flag3 == 0 && flag5 == 0) { //5*5找得分點
            for (int i = row - 2; i < row + 3; i++) {
                if (i > 0 && i < 49 && flag5 == 0) {
                    for (int j = col - 2; j < col + 3; j++) {
                        if (j > 0 && j < 49 && flag5 == 0) {
                            tempsnack = snack;
                            flag = 0;
                            position = make_tuple(i, j);
                            //每一個點跟蛇的位置比較，有找到
                            while (!tempsnack.empty() && flag == 0) {
                                if (tempsnack.front() == position) {
                                    flag = 1;
                                }
                                tempsnack.pop();
                            }
                            if (flag == 0) {
                                flag5 = 1;//在5*5中找到可以放點的地方
                                row = i;
                                col = j;
                                break;
                            }
                        }
                        if (flag5 == 1)
                            break;
                    }
                }
                if (flag5 == 1) {
                    break;
                }
            }
        }
        if (flag5 == 1) {  //5*5找到
            vector<vector<int>> newmap;
            for (int i = 0; i < 50; i++) {
                vector<int> tempv;
                for (int j = 0; j < 50; j++) {
                    if (i == 0 || i == 49) {
                        tempv.push_back(-1);
                    }
                    else {
                        if (i == row && j == col) {
                            tempv.push_back(1);
                        }
                        else if (j == 0 || j == 49)
                            tempv.push_back(-1);
                        else
                            tempv.push_back(0);
                    }
                }
                newmap.push_back(tempv);
            }
            return newmap;
        }
        else if (flag3 == 0 && flag5 == 0 && flagall == 0) {
            for (int i = 0; i < 50; i++) {
                if (i > 0 && i < 49 && flagall == 0) {
                    for (int j = 0; j < 50; j++) {
                        if (j > 0 && j < 49 && flagall == 0) {
                            tempsnack = snack;
                            flag = 0;
                            position = make_tuple(i, j);
                            //每一個點跟蛇的位置比較，有找到
                            while (!tempsnack.empty() && flag == 0) {
                                if (tempsnack.front() == position) {
                                    flag = 1;
                                }
                                tempsnack.pop();
                            }
                            if (flag == 0) {
                                flag5 = 1;//在5*5中找到可以放點的地方
                                row = i;
                                col = j;
                                break;
                            }
                        }
                        if (flagall == 1)
                            break;
                    }
                }
                if (flagall == 1) {
                    break;
                }
            }
        }
        if (flagall == 1) {
            vector<vector<int>> newmap;
            for (int i = 0; i < 50; i++) {
                vector<int> tempv;
                for (int j = 0; j < 50; j++) {
                    if (i == 0 || i == 49) {
                        tempv.push_back(-1);
                    }
                    else {
                        if (i == row && j == col) {
                            tempv.push_back(1);
                        }
                        else if (j == 0 || j == 49)
                            tempv.push_back(-1);
                        else
                            tempv.push_back(0);
                    }
                }
                newmap.push_back(tempv);
            }
            return newmap;
        }
    }
    return map[mapindex];
}

queue<tuple<int, int>> get_start_position() {
    queue<tuple<int, int>> re;

    tuple<int, int> pos1(1, 1);
    tuple<int, int> pos2(1, 2);
    tuple<int, int> pos3(1, 3);
    tuple<int, int> pos4(1, 4);
    tuple<int, int> pos5(1, 5);

    re.push(pos1);
    re.push(pos2);
    re.push(pos3);
    re.push(pos4);
    re.push(pos5);

    return re;
}

void loadmaps2(vector<vector<int>> map[101]) {
    fstream file;
    char buffer[150];
    string fname;
    for (int i = 101; i < 201; i++) {
        if (i < 10)
            fname = "00" + to_string(i);
        else if (i < 100)
            fname = "0" + to_string(i);
        else
            fname = to_string(i);
        file.open("./Data/maps/map_" + fname, ios::in);
        if (!file) {
            cout << "no file" << endl;
        }
        else {
            do {
                vector<int> tempv;
                file.getline(buffer, sizeof(buffer));
                const char* d = " "; //分割依據
                char *row; //儲存每次分割結果
                row = strtok(buffer, d);
                while (row) {
                    string s = row;
                    int temp = stoi(s);
                    tempv.push_back(temp);
                    row = strtok(NULL, d);
                }
                map[i-100].push_back(tempv);
            } while (!file.eof());
        }
        file.close();
    }
}
vector<int> findthree(int row, int col, queue<tuple<int, int>> snack) {
    int flag3 = 0;
    int flag = 0;
    vector<int> result;
    tuple<int, int> position; //暫時的點
    queue<tuple<int, int>> tempsnack = snack;
    for (int i = row - 1; i < row + 2; i++) { //原本點的3*3為範圍
        if (i > 0 && i < 49 && flag3 == 0) {
            for (int j = col - 1; j < col + 2; j++) {
                if (j > 0 && j < 49 && flag3 == 0) {
                    tempsnack = snack;
                    flag = 0;
                    position = make_tuple(i, j);
                    //每一個點跟蛇的位置比較，有找到
                    while (!tempsnack.empty() && flag == 0) {
                        if (tempsnack.front() == position) {
                            flag = 1;
                        }
                        tempsnack.pop();
                    }
                    if (flag == 0) {
                        flag3 = 1;//在3*3中找到可以放點的地方
                        row = i;//新點index
                        col = j;
                        break;
                    }
                }
            }
            if (flag3 == 1)
                break;
        }
    }
    if (flag3 == 1) {
        result.push_back(flag3);
        result.push_back(row);
        result.push_back(col);
    }
    else if (flag3 == 0) {
        result.push_back(flag3);
        result.push_back(0);
        result.push_back(0);
    }
    return result;
}
vector<int> findfive(int row, int col, queue<tuple<int, int>> snack) {
    int flag5 = 0;
    int flag = 0;
    vector<int> result;
    tuple<int, int> position; //暫時的點
    queue<tuple<int, int>> tempsnack = snack;
    for (int i = row - 2; i < row + 3; i++) { //原本點的3*3為範圍
        if (i > 0 && i < 49 && flag5 == 0) {
            for (int j = col - 2; j < col + 3; j++) {
                if (j > 0 && j < 49 && flag5 == 0) {
                    tempsnack = snack;
                    flag = 0;
                    position = make_tuple(i, j);
                    //每一個點跟蛇的位置比較，有找到
                    while (!tempsnack.empty() && flag == 0) {
                        if (tempsnack.front() == position) {
                            flag = 1;
                        }
                        tempsnack.pop();
                    }
                    if (flag == 0) {
                        flag5 = 1;//在5*5中找到可以放點的地方
                        row = i;//新點index
                        col = j;
                        break;
                    }
                }
            }
            if (flag5 == 1)
                break;
        }
    }
    if (flag5 == 1) {
        result.push_back(flag5);
        result.push_back(row);
        result.push_back(col);
    }
    else if (flag5 == 0) {
        result.push_back(flag5);
        result.push_back(0);
        result.push_back(0);
    }
    return result;
}
vector<int> findall(int row, int col, queue<tuple<int, int>> snack) {
    int flagall = 0;
    int flag = 0;
    vector<int> result;
    tuple<int, int> position; //暫時的點
    queue<tuple<int, int>> tempsnack = snack;
    for (int i = 0; i < 50; i++) { //原本點的3*3為範圍
        if (i > 0 && i < 49 && flagall == 0) {
            for (int j = 0; j < 50; j++) {
                if (j > 0 && j < 49 && flagall == 0) {
                    tempsnack = snack;
                    flag = 0;
                    position = make_tuple(i, j);
                    //每一個點跟蛇的位置比較，有找到
                    while (!tempsnack.empty() && flag == 0) {
                        if (tempsnack.front() == position) {
                            flag = 1;
                        }
                        tempsnack.pop();
                    }
                    if (flag == 0) {
                        flagall = 1;//在5*5中找到可以放點的地方
                        row = i;//新點index
                        col = j;
                        break;
                    }
                }
            }
            if (flagall == 1)
                break;
        }
    }
    if (flagall == 1) {
        result.push_back(flagall);
        result.push_back(row);
        result.push_back(col);
    }
    else if (flagall == 0) {
        result.push_back(flagall);
        result.push_back(0);
        result.push_back(0);
    }
    return result;
}
//(所有地圖,下一張地圖index,蛇的位置)
vector<vector<int>> generate_map2(vector<vector<int>> map[101], int mapindex, queue<tuple<int, int>> snack) {
    tuple<int, int> positionONE, positionTWO;
    int row1, row2, col1, col2;
    //    int flag3=0;
    //    int flag5=0;
    //    int flag7=0;
    //    int flagall=0;

    //尋找地圖兩個得分點位置
    for (int m = 0; m < 50; m++) {
        for (int n = 0; n < 50; n++) {
            if (map[mapindex][m][n] == 1) {
                row1 = m;
                col1 = n;
                positionONE = make_tuple(m, n);
            }
            if (map[mapindex][m][n] == 2) {
                row2 = m;
                col2 = n;
                positionTWO = make_tuple(m, n);
            }
        }
    }
    //先調整得分點2，再調整得分點1
    //判斷得分點有沒有在蛇身上
    int twoOnSnack = 0;
    int oneOnSnack = 0;
    vector<int> result;
    queue<tuple<int, int>> tempsnack = snack;
    while (!tempsnack.empty()) {
        if (tempsnack.front() == positionTWO) {
            twoOnSnack = 1;
            cout << "two on snack" << endl;
        }
        if (tempsnack.front() == positionONE) {
            oneOnSnack = 1;
            cout << "one on snack" << endl;
        }
        tempsnack.pop();
    }
    if (oneOnSnack == 0 && twoOnSnack == 0) { //兩個都不在蛇身上
        return map[mapindex];
    }
    if (twoOnSnack == 1) { //如果得分點2在蛇身上
        result = findthree(row2, col2, snack); //從3*3開始找
    if (result[0] == 1) {
        twoOnSnack = 0;
        row2 = result[1];
        col2 = result[2];
    }
    else if (result[0] == 0) {
        result = findfive(row2, col2, snack); //從5*5開始找
    if (result[0] == 1) {
        twoOnSnack = 0;
        row2 = result[1];
        col2 = result[2];
    }
    else if (result[0] == 0) {
        result = findall(row2, col2, snack); //全部找
        if (result[0] == 1) {
            twoOnSnack = 0;
            row2 = result[1];
            col2 = result[2];
        }
    }
}
}
if (oneOnSnack == 1) {
    result = findthree(row1, col1, snack); //從3*3開始找
    if (result[0] == 1) {
        oneOnSnack = 0;
        row1 = result[1];
        col1 = result[2];
    }
else if (result[0] == 0) {
    result = findfive(row1, col1, snack); //從5*5開始找
    if (result[0] == 1) {
        oneOnSnack = 0;
        row1 = result[1];
        col1 = result[2];
    }
else if (result[0] == 0) {
    result = findall(row1, col1, snack); //全部找
    if (result[0] == 1) {
        oneOnSnack = 0;
        row1 = result[1];
        col1 = result[2];
    }
}
}
}
if (oneOnSnack == 0 && twoOnSnack == 0) {  //得分點1、2都不在蛇身上
    vector<vector<int>> newmap;
    for (int i = 0; i < 50; i++) {
        vector<int> tempv;
        for (int j = 0; j < 50; j++) {
            if (i == 0 || i == 49) {
                tempv.push_back(-1);
            }
            else {
                if (i == row1 && j == col1) {
                    tempv.push_back(1);
                }
                else if (i == row2 && j == col2)
                    tempv.push_back(2);
                else if (j == 0 || j == 49)
                    tempv.push_back(-1);
                else
                    tempv.push_back(0);
            }
        }
        newmap.push_back(tempv);
    }
    return newmap;
}
return map[mapindex];
}

int main(int argc, char *argv[]) {
    queue<tuple<int, int>> ori_pos;
    queue<tuple<int, int>> new_pos = get_start_position();

    Snake snake(new_pos);

    vector<vector<int>> whole_map[101];//1~100存一百張地圖
    vector<vector<int>> whole_map2[101];//101~200存一百張地圖
    loadmaps(whole_map);//從檔案中讀取地圖資料
    loadmaps2(whole_map2);//從檔案中讀取地圖資料

    int cur_map_index = 1;
    vector<vector<int>> map = generate_map(whole_map, cur_map_index, new_pos);

    int step_limit = 8000;
    int point = 0;
    cout << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "|" << point << "\n";

    clock_t usedTime, limitTime;

    usedTime = 0;
    limitTime = 120000;

    try
    {
        for (int i = 0; i < step_limit; i++) {

            ori_pos = new_pos;

            clock_t tmpTime1, tmpTime2;

            tmpTime1 = clock();

            new_pos = snake.nextPosition(map);

            tmpTime2 = clock();

            usedTime += tmpTime2 - tmpTime1;

            if (usedTime > limitTime) {

                // Create and open a text file
                ofstream f(argv[2]);

                // Write to the file
                f << argv[1] << "," << point << "," << "TimeLimitExceed";

                // Close the file
                f.close();

                break;
            }

            int new_head_x = get<0>(new_pos.back());
            int new_head_y = get<1>(new_pos.back());

            if (i % 1000 == 0) {
                cout << i << ": " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "|" << map[new_head_x][new_head_y] << "$" << point << "\n";
            }
            cout << i << ": map " << cur_map_index << " | " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "|" << map[new_head_x][new_head_y] << "$" << point << "\n";

            // Walk one step
            int one_step_limit = 1;
            one_step_limit -= abs(get<0>(ori_pos.back()) - new_head_x);
            one_step_limit -= abs(get<1>(ori_pos.back()) - new_head_y);
            if (one_step_limit != 0) {
                cout << argv[1] << " A: Invalid step... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";

                // Create and open a text file
                ofstream f(argv[2]);

                // Write to the file
                f << argv[1] << "," << point << "," << "InvalidStep";

                // Close the file
                f.close();

                break;
            }

            // Hit wall
            if (map[new_head_x][new_head_y] == -1) {
                cout << argv[1] << " B: GAME OVER! Hit wall... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";

                // Create and open a text file
                ofstream f(argv[2]);

                // Write to the file
                f << argv[1] << "," << point << "," << "HitWall";

                // Close the file
                f.close();

                break;
            }

            // Hit self
            queue<tuple<int, int>> tmp_queue = new_pos;
            bool ifGameOver = false;
            for (int i = 0; i < new_pos.size() - 1; i++) {
                if (get<0>(tmp_queue.front()) == new_head_x && get<1>(tmp_queue.front()) == new_head_y) {
                    cout << argv[1] << " C: GAME OVER! Hit yourself... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";

                    // Create and open a text file
                    ofstream f(argv[2]);

                    // Write to the file
                    f << argv[1] << "," << point << "," << "HitSelf";

                    // Close the file
                    f.close();

                    ifGameOver = true;
                    break;
                }
                tmp_queue.pop();
            }
            if (ifGameOver)
                break;
            // Check teleport
            // TBD...

            // Count point and check eat longer
            if (map[new_head_x][new_head_y] > 0) {
                if (new_pos.size() != ori_pos.size() + 1) {
                    cout << argv[1] << " D: Invalid eat length... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";

                    // Create and open a text file
                    ofstream f(argv[2]);

                    // Write to the file
                    f << argv[1] << "," << point << "," << "InvalidEatLength";

                    // Close the file
                    f.close();

                    break;
                }

                point += map[new_head_x][new_head_y];

                // Create and open a text file
                ofstream f(argv[2]);

                // Write to the file
                f << argv[1] << "," << point << "," << "ErrorInterruption";

                // Close the file
                f.close();

                if (cur_map_index >= 200) {

                    // Create and open a text file
                    ofstream f(argv[2]);

                    // Write to the file
                    f << argv[1] << "," << point << "," << "Finish";

                    // Close the file
                    f.close();

                    break;
                }
                if (cur_map_index < 100) {
                    map = generate_map(whole_map, ++cur_map_index, new_pos);
                }
                else if (cur_map_index < 200) {
                    map = generate_map2(whole_map2, (++cur_map_index) - 100, new_pos);
                }
            }
            else {
                if (new_pos.size() != ori_pos.size()) {
                    cout << argv[1] << " E: Invalid length... " << get<0>(new_pos.back()) << ", " << get<1>(new_pos.back()) << "\n";

                    // Create and open a text file
                    ofstream f(argv[2]);

                    // Write to the file
                    f << argv[1] << "," << point << "," << "InvalidLength";

                    // Close the file
                    f.close();

                    break;
                }
            }

            if (i == step_limit - 1) {
                // Create and open a text file
                ofstream f(argv[2]);

                // Write to the file
                f << argv[1] << "," << point << "," << "OverStepLimit";

                // Close the file
                f.close();
            }
        }
    }
    catch (const exception& e)
    {
        cout << "Error" << e.what() << "\n";

        // Create and open a text file
        ofstream f(argv[2]);

        // Write to the file
        f << argv[1] << "," << point << "," << "Error";

        // Close the file
        f.close();
    }

    cout << argv[1] << " | Final: " << "$" << point << "\n";

    //system("pause");

    return 0;
}
