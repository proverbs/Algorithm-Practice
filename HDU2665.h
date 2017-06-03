//
// Created by proverbs on 6/3/17.
//

#ifndef POJ_HDU2665_H
#define POJ_HDU2665_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <algorithm>

namespace HDU2665 {
    using namespace std;

#define N 100010
#define LN 17

    int cas;
    int n, m;
    int a[N], b[N], rt[N];
    int uni_num;
    int sum[N * LN + 4 * N], ls[N * LN + 4 * N], rs[N * LN + 4 * N];
    int cnt;

    int newnode(int l, int r, int s) {
        cnt++;
        ls[cnt] = l;
        rs[cnt] = r;
        sum[cnt] = s;
        return cnt;
    }

    void build(int l, int r, int &x) {
        x = newnode(0, 0, 0);
        if (l == r) return;
        int mid = (l + r) >> 1;
        build(l, mid, ls[x]);
        build(mid + 1, r, rs[x]);
    }

    void update(int l, int r, int &x, int px, int val) {
        x = newnode(ls[px], rs[px], sum[px] + 1);
        if (l == r) return;
        int mid = (l + r) >> 1;
        if (val > mid ) update(mid + 1, r, rs[x], rs[px], val);
        else update(l, mid, ls[x], ls[px], val);
    }

    int query(int l, int r, int y, int x, int k) {
        if (l == r) return l;
        int mid = (l + r) >> 1;
        int dt = sum[ls[y]] - sum[ls[x]];
        if (dt < k) return query(mid + 1, r, rs[y], rs[x], k - dt);
        return query(l, mid, ls[y], ls[x], k);
    }

    void solve() {
        scanf("%d", &cas);
        while (cas--) {
            scanf("%d%d", &n, &m);
            for (int i = 1; i <= n; i++) {
                scanf("%d", &a[i]);
                b[i] = a[i];
            }
            // 离散化
            sort(b + 1, b + 1 + n);
            uni_num = unique(b + 1, b + 1 + n) - b - 1;
            for (int i = 1; i <= n; i++)
                a[i] = lower_bound(b + 1, b + 1 + uni_num, a[i]) - b;
            // 建立可持久化线段树
            cnt = 0;
            build(1, uni_num, rt[0]);
            for (int i = 1; i <= n; i++)
                update(1, uni_num, rt[i], rt[i - 1], a[i]);
            int s, t, k;
            while (m--) {
                scanf("%d%d%d", &s, &t, &k);
                printf("%d\n", b[query(1, uni_num, rt[t], rt[s - 1], k)]);
            }
        }
    }
}

#endif //POJ_HDU2665_H
