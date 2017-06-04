//
// Created by proverbs on 6/4/17.
//

#ifndef POJ_HDU3966_H
#define POJ_HDU3966_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>


namespace HDU3966 {
    using namespace std;

#define N 50100
#define M 100010

    int n, m, p;
    int cnt, tot;
    int head[N], nxt[M], to[M];
    int det[N << 2];
    int ind[N];
    int fa[N], top[N], dep[N], sz[N], son[N];
    int q[N];
    int a[N];

    void add(int u, int v) {
        to[cnt] = v; nxt[cnt] = head[u]; head[u] = cnt++;
    }

    void init() {
        memset(son, 0, sizeof son);
        memset(head, -1, sizeof head);
        tot = cnt = 0;
    }

    void preprocess() {
        // 获取fa, dep
        int h = 1, t = 2, sta;
        q[1] = 1;
        dep[1] = 1;
        fa[1] = 0;
        while (h < t) {
            sta = q[h++];
            sz[sta] = 1;
            for (int i = head[sta]; ~i; i = nxt[i]) {
                if (fa[sta] != to[i]) {
                    fa[to[i]] = sta;
                    dep[to[i]] = dep[sta] + 1;
                    q[t++] = to[i];
                }
            }
        }
        // 使用bfs队列模拟dfs，避免爆栈
        // 计算sz， son
        for (int j = t - 1; j >= 1; j--) {
            sta = q[j];
            for (int i = head[sta]; ~i; i = nxt[i]) {
                if (fa[sta] != to[i]) {
                    sz[sta] += sz[to[i]];
                    if (sz[to[i]] > sz[son[sta]])
                        son[sta] = to[i];// sz[0] == 0
                }
            }
        }
        // 计算top
        top[1] = 1;
        for (int i = 2; i < t; i++) {
            sta = q[i];
            if (sta == son[fa[sta]]) top[sta] = top[fa[sta]];
            else top[sta] = sta;
        }
        // 将树拍扁，求ind
        for (int j = 1; j <= n; j++) {
            if (top[j] == j) {
                for (int i = j; i; i = son[i])
                    ind[i] = ++tot;
            }
        }
    }

    void pushdown(int u) {
        det[u << 1] += det[u];
        det[u << 1 | 1] += det[u];
        det[u] = 0;
    }

    void build(int u, int L, int R) {
        det[u] = 0;
        if (L == R) return;
        int MID = (L + R) >> 1;
        build(u << 1, L, MID);
        build(u << 1 | 1, MID + 1, R);
    }

    int query(int u, int L, int R, int p) {
        if (L == R) return det[u];
        if (det[u] != 0) pushdown(u);
        int MID = (L + R) >> 1;
        if (p <= MID) return query(u << 1, L, MID, p);
        return query(u << 1 | 1, MID + 1, R, p);
    }

    void update(int u, int L, int R, int l, int r, int k) {
        if (l <= L && r >= R) {
            det[u] += k;
            return;
        }
        int MID = (L + R) >> 1;
        if (l <= MID) update(u << 1, L, MID, l, r, k);
        if (r > MID) update(u << 1 | 1, MID + 1, R, l, r, k);
    }

    void update_range(int x, int y, int k) {
        while (top[x] != top[y]) {
            if (dep[top[x]] < dep[top[y]]) swap(x, y);
            update(1, 1, tot, ind[top[x]], ind[x], k);
            x = fa[top[x]];
        }
        if (ind[x] > ind[y]) swap(x, y);// 在一条重链上
        update(1, 1, tot, ind[x], ind[y], k);
    }

    void solve() {
        while (scanf("%d%d%d", &n, &m, &p) != EOF) {
            int x, y, z;
            char qu[3];
            init();
            for (int i = 1; i <= n; i++)
                scanf("%d", &a[i]);
            for (int i = 1; i <= m; i++) {
                scanf("%d%d", &x, &y);
                add(x, y);
                add(y, x);
            }
            preprocess();
            build(1, 1, tot);
            while (p--) {
                scanf("%s", qu);
                if (qu[0] == 'Q') {
                    scanf("%d", &x);
                    // 单点查询
                    printf("%d\n", a[x] + query(1, 1, tot, ind[x]));
                }
                else {
                    scanf("%d%d%d", &x, &y, &z);
                    // 区间更新
                    if (qu[0] == 'D') update_range(x, y, -z);
                    else update_range(x, y, z);
                }
            }
        }
    }

}

#endif //POJ_HDU3966_H
