#include <vector>
#include <iostream>
#include <Windows.h>

using namespace std;

const int INF = 99999999;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int n = 10;
    vector<vector<int>> d(n, vector<int>(n, INF));

    d[0][1] = 3;
    d[0][2] = 4;
    d[0][3] = 2;
    d[1][5] = 3;
    d[2][5] = 6;
    d[3][4] = 5;
    d[3][5] = 2;
    d[4][6] = 6;
    d[4][8] = 12;
    d[5][4] = 1;
    d[5][6] = 8;
    d[5][7] = 7;
    d[6][9] = 4;
    d[7][9] = 3;
    d[8][7] = 6;
    d[8][9] = 11;

    vector<vector<int>> next(n, vector<int>(n, -1));
    for (int u = 0; u < n; ++u) {
        for (int v = 0; v < n; ++v) {
            if (d[u][v] != INF) {
                next[u][v] = v;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (d[u][i] != INF && d[i][v] != INF && d[u][i] + d[i][v] < d[u][v]) {
                    d[u][v] = d[u][i] + d[i][v];
                    next[u][v] = next[u][i];
                }
            }
        }
    }

    int from = 0, to = 9;
    if (d[from][to] == INF) {
        cout << "Путь не найден" << "\n";
        return -1;
    }

    cout << "Кратчайший путь из " << (from + 1) << " в " << (to + 1) << ": ";
    while (from != to) {
        cout << (from + 1) << " -> ";
        from = next[from][to];
    }
    cout << (to + 1) << "\n";

    return 0;
}