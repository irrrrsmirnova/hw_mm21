#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

float g = 9.81;

float get_the_first(string str)
{
    string str1;
    int i = 0;
    while (str[i] != char(32)) { str1 += str[i]; i += 1; }
    return stof(str1);
}

float get_the_second(string str)
{
    string str2;
    int i = 0;
    while (str[i] != char(32)) { i += 1; }
    i += 1;
    while (i < str.size()) { str2 += str[i]; i += 1; }
    return stof(str2);
}

float y_x(float x, float y, float vx, float vy, float x_add) {
    return y + vy / vx * (x_add - x) - g / (2 * vx * vx) * (x_add - x) * (x_add - x);
}

float v_y(float x, float vx, float vy, float x_add) {
    return vy - g * (x_add - x) / vx;
}

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        ifstream file(argv[1]);

        string str;
        getline(file, str);
        float h0 = stof(str);

        getline(file, str);
        float vx = get_the_first(str); float vy = get_the_second(str);

        int n = 0;
        vector <float> coord = { 0 }; vector <float> height = { h0 };
        while (getline(file, str))
        {
            n = n + 1;
            coord.push_back(get_the_first(str)); height.push_back(get_the_second(str));
        }

        int area = 0;

        float x = 0; float y = h0;
        bool ind = 0;

        while (true)
        {
            ind = 0;

            if (vx == 0) { break; }

            if (vx > 0) {
                for (int i = area + 1; i < coord.size(); i++) {
                    if (y_x(x, y, vx, vy, coord[i]) >= 0 && y_x(x, y, vx, vy, coord[i]) <= height[i]) {
                        ind = 1;
                        y = y_x(x, y, vx, vy, coord[i]);
                        vy = v_y(x, vx, vy, coord[i]);
                        vx = -vx;
                        area = i;
                        x = coord[i];
                    }
                    if (ind == 1) { break; }
                }
                if (y == 0) { break; }
            }

            else {
                if (vx < 0) {
                    if (x == 0 || x == coord[1]) { area = 0; break; }
                    else {
                        for (int i = area - 1; i > 0; i--) {
                            if (y_x(x, y, vx, vy, coord[i]) >= 0 && y_x(x, y, vx, vy, coord[i]) <= height[i]) {
                                ind = 1;
                                y = y_x(x, y, vx, vy, coord[i]);
                                vy = v_y(x, vx, vy, coord[i]);
                                vx = -vx;
                                area = i;
                                x = coord[i];
                            }
                            if (ind == 1) { break; }
                        }
                        if (y == 0) { break; }
                    }
                }
            }

            bool ind1 = 0;

            if (ind == 0) {
                if (vx > 0) {
                    if (area != coord.size() - 1) {
                        for (int i = area; i < coord.size() - 1; i++) {
                            if (y_x(x, y, vx, vy, coord[i]) * y_x(x, y, vx, vy, coord[i + 1]) < 0) {
                                area = i;
                                ind1 = 1;
                                break;
                            }
                        }
                        if (ind1 == 0) { area = coord.size() - 1; }
                    }
                    else { area = coord.size() - 1; }
                }

                if (vx < 0) {
                    if (coord.size() > 2) {
                        for (int i = area; i > 1; i--) {
                            if (y_x(x, y, vx, vy, coord[i]) * y_x(x, y, vx, vy, coord[i - 1]) < 0) {
                                area = i - 1;
                                ind1 = 1;
                                break;
                            }
                        }
                        if (ind1 == 0) { area = 0; }
                    }
                }

                break;
            }

        }

        cout << area;
    }
    
    else{
        cout << "The incorrect number of the arguments." << endl;
    }

    return 0;
}
