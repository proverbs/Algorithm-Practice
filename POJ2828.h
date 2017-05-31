//
// Created by proverbs on 5/31/17.
//

#ifndef POJ_POJ2828_H
#define POJ_POJ2828_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

namespace POJ2828 {
    using namespace std;

#define N 200010

    int n;
    int sum[N * 4];
    int val[N], pos[N];
    int ans[N];

    void pack(int u) {
        sum[u] = sum[u << 1] + sum[u << 1 | 1];
    }

    void build(int u, int l, int r) {
        // 这种不记录节点表示区间的线段树会牺牲一些时间效率
        if (l == r) {
            sum[u] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(u << 1, l, mid);
        build(u << 1 | 1, mid + 1, r);
        pack(u);
    }

    int query(int u, int L, int R, int x) {
        if (L == R) return L;
        int MID = (L + R) >> 1;
        if (sum[u << 1] < x) return query(u << 1 | 1, MID + 1, R, x - sum[u << 1]);
        else return query(u << 1, L, MID, x);
    }

    void update(int u, int L, int R, int x) {
        if (L == R) {
            sum[u] = 0;
            return;
        }
        int MID = (L + R) >> 1;
        if (MID < x) update(u << 1 | 1, MID + 1, R, x);
        else update(u << 1, L, MID, x);
        pack(u);
    }

    void solve() {
        while (scanf("%d", &n) != EOF) {
            for (int i = 0; i < n; i++) {
                scanf("%d%d", &pos[i], &val[i]);
            }
            build(1, 1, n);
            for (int i = n - 1, res; i >= 0; i--) {
                res = query(1, 1, n, pos[i] + 1);
                ans[res] = val[i];
                update(1, 1, n, res);
            }
            for (int i = 1; i < n; i++) printf("%d ", ans[i]);
            printf("%d\n", ans[n]);
        }
    }

}

#endif //POJ_POJ2828_H
