#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

float g = 9.81;

float el_1(string str)
{
    string str1;
    int i = 0;
    while (str[i] != char(32)) { str1 += str[i]; i += 1; }
    return stof(str1);
}

float el_2(string str)
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
        float vx = el_1(str); float vy = el_2(str);

        int n = 0;
        vector<float> xk = { 0 }; vector<float> hk = { 0 };
        while (getline(file, str))
        {
            n = n + 1;
            xk.push_back(el_1(str)); hk.push_back(el_2(str));
        }

        int gran = 0;

        float x = 0; float y = h0;
        bool flag = 0;

        float itx = 0; float ity = 0;

        for (float k = 0; k < xk.size(); k = k + 0.001)
        {
            itx += k * vx; ity += k * vy;
        }

        while (true)
        {
            flag = 0;

            if (vx == 0) { break; }

            if (vx > 0) {
                for (int i = gran + 1; i < xk.size(); i++) {
                    if (y_x(x, y, vx, vy, xk[i]) >= 0 && y_x(x, y, vx, vy, xk[i]) <= hk[i]) {
                        flag = 1;
                        y = y_x(x, y, vx, vy, xk[i]);
                        vy = v_y(x, vx, vy, xk[i]);
                        vx = -vx;
                        gran = i;
                        x = xk[i];
                    }
                    if (flag == 1) { break; }
                }
                if (y == 0) { break; }
            }

            else {
                if (vx < 0) {
                    if (x == 0 || x == xk[1]) { gran = 0; break; }
                    else {
                        for (int i = gran - 1; i > 0; i--) {
                            if (y_x(x, y, vx, vy, xk[i]) >= 0 && y_x(x, y, vx, vy, xk[i]) <= hk[i]) {
                                flag = 1;
                                y = y_x(x, y, vx, vy, xk[i]);
                                vy = v_y(x, vx, vy, xk[i]);
                                vx = -vx;
                                gran = i;
                                x = xk[i];
                            }
                            if (flag == 1) { break; }
                        }
                        if (y == 0) { break; }
                    }
                }
            }

            bool flag1 = 0;

            if (flag == 0) {
                if (vx > 0) {
                    if (gran != xk.size() - 1) {
                        for (int i = gran; i < xk.size() - 1; i++) {
                            if (y_x(x, y, vx, vy, xk[i]) * y_x(x, y, vx, vy, xk[i + 1]) < 0) {
                                gran = i;
                                flag1 = 1;
                                break;
                            }
                        }
                        if (flag1 == 0) { gran = xk.size() - 1; }
                    }
                    else { gran = xk.size() - 1; }
                }

                if (vx < 0) {
                    if (xk.size() > 2) {
                        for (int i = gran; i > 1; i--) {
                            if (y_x(x, y, vx, vy, xk[i]) * y_x(x, y, vx, vy, xk[i - 1]) < 0) {
                                gran = i - 1;
                                flag1 = 1;
                                break;
                            }
                        }
                        if (flag1 == 0) { gran = 0; }
                    }
                }

                break;
            }

        }

        cout << gran;
    }
    else{
        cout << "The incorrect number of the arguments." << endl;
    }

    return 0;
}
