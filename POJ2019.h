//
// Created by proverbs on 6/3/17.
//

#ifndef POJ_POJ2019_H
#define POJ_POJ2019_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

namespace POJ2019 {
    using namespace std;

#define N 260
#define LN 9

    int rmax[N][LN][N][LN], rmin[N][LN][N][LN];
    int lg[N];
    int n, b, q;
    int a[N][N];

    void init_rmq() {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                rmax[i][0][j][0] = rmin[i][0][j][0] = a[i][j];

        for (int k = 1; (1 << k) <= n; k++)
            for (int p = 1; (1 << p) <= n; p++)
                for (int i = 1; i + (1 << k) - 1 <= n; i++)
                    for (int j = 1; j + (1 << p) - 1 <= n; j++) {
                        rmax[i][k][j][p] = max(max(rmax[i][k - 1][j][p - 1], rmax[i][k - 1][j + (1 << (p - 1))][p - 1]), max(rmax[i + (1 << (k - 1))][k - 1][j][p - 1], rmax[i + (1 << (k - 1))][k - 1][j + (1 << (p - 1))][p - 1]));
                        rmin[i][k][j][p] = min(min(rmin[i][k - 1][j][p - 1], rmin[i][k - 1][j + (1 << (p - 1))][p - 1]), min(rmin[i + (1 << (k - 1))][k - 1][j][p - 1], rmin[i + (1 << (k - 1))][k - 1][j + (1 << (p - 1))][p - 1]));
                    }
    }

    int ask_rmq_max(int lx, int ly, int rx, int ry) {
        int dx = lg[rx - lx + 1];
        int dy = lg[ry - ly + 1];
        return max(max(rmax[lx][dx][ly][dy], rmax[lx][dx][ry - (1 << dy) + 1][dy]), max(rmax[rx - (1 << dx) + 1][dx][ly][dy], rmax[rx - (1 << dx) + 1][dx][ry - (1 << dy) + 1][dy]));
    }

    int ask_rmq_min(int lx, int ly, int rx, int ry) {
        int dx = lg[rx - lx + 1];
        int dy = lg[ry - ly + 1];
        return min(min(rmin[lx][dx][ly][dy], rmin[lx][dx][ry - (1 << dy) + 1][dy]), min(rmin[rx - (1 << dx) + 1][dx][ly][dy], rmin[rx - (1 << dx) + 1][dx][ry - (1 << dy) + 1][dy]));
    }

    void solve() {
        for (int i = 1; i < N; i++) {
            lg[i] = i >> lg[i - 1] + 1 ? lg[i - 1] + 1 : lg[i - 1];
        }
        while (scanf("%d%d%d", &n, &b, &q) != EOF) {
            for (int i = 1; i <= n; i++)
                for (int j = 1; j <= n; j++)
                    scanf("%d", &a[i][j]);
            init_rmq();
            int x, y;
            while (q--) {
                scanf("%d%d", &x, &y);
                printf("%d\n", ask_rmq_max(x, y, x + b - 1, y + b - 1) - ask_rmq_min(x, y, x + b - 1, y + b - 1));
            }
        }
    }

}

#endif //POJ_POJ2019_H
