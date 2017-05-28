//
// Created by proverbs on 5/26/17.
// kmp
//

#ifndef POJ_POJ2185_H
#define POJ_POJ2185_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>


namespace POJ2185 {
    using namespace std;
#define N 10010
#define M 80
    int n, m;
    char a[N][M];
    int p[N];

    bool is_col_equ(int x, int y) {
        for (int i = 0; i < n; i++)
            if (a[i][x] != a[i][y]) return false;
        return true;
    }

    bool is_row_equ(int x, int y) {
        for (int i = 0; i < m; i++)
            if (a[x][i] != a[y][i]) return false;
        return true;
    }

    int get_row_p() {
        p[0] = 0;
        for (int i = 1, len = 0; i < m; i++) {
            while (len && !is_col_equ(i, len)) len = p[len - 1];
            if (is_col_equ(i, len)) len++;
            p[i] = len;
        }
        return m - p[m - 1];
    }

    int get_col_p() {
        p[0] = 0;
        for (int i = 1, len = 0; i < n; i++) {
            while (len && !is_row_equ(i, len)) len = p[len - 1];
            if (is_row_equ(i, len)) len++;
            p[i] = len;
        }
        return n - p[n - 1];
    }

    void solve() {
        while (scanf("%d%d", &n, &m) != EOF) {
            for (int i = 0; i < n; i++) {
                scanf("%s", a[i]);
            }
            int rowp = get_row_p();
            int colp = get_col_p();
            printf("%d\n", rowp * colp);
        }
    }
}


#endif //POJ_POJ2185_H
