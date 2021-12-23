#include <iostream>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

float distance(float a, float b, float x, float y) {
    return abs(a * x + b * y) / sqrt(a * a + b * b);
}

float get_x(string str) {
    int whitespace = str.find(" ");
    string the_first = str.substr(0, whitespace);
    return stof(the_first);
}

float get_y(string str) {
    int whitespace = str.find(" ");
    string the_second = str.substr(whitespace + 1, str.size() - 1);
    return stof(the_second);
}

bool define_side(float a, float b, float x, float y) {
    float help = a * x + b * y;
    return (help >= 0);
}

int main()
{
    float x_left = 0; float y_left = 0;
    float x_right = 0; float y_right = 0;
    float distance_left = 0; float distance_right = 0;
    
    ifstream file("in.txt");

    string direct;
    getline(file, direct);
    float a = get_y(direct);
    float b = -get_x(direct);

    while (getline(file, direct)) {
        float x = get_x(direct);
        float y = get_y(direct);
        float distance_xy = distance(a, b, x, y);
        if (define_side(a, b, x, y)) {
            if (distance_xy >= distance_right) {
                distance_right = distance_xy;
                x_right = x;
                y_right = y;
            }
        }
        else {
            if (distance_xy >= distance_left) {
                distance_left = distance_xy;
                x_left = x;
                y_left = y;
            }
        }
    }

    cout << "The most left: " << x_left << " " << y_left << endl;
    cout << "The most right: " << x_right << " " << y_right << endl;
}
