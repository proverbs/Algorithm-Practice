//
// Created by proverbs on 5/30/17.
//

#ifndef POJ_POJ3321_H
#define POJ_POJ3321_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace POJ3321 {
    using namespace std;

#define N 100010
#define lowbit(x) x&-x

    int head[N], nxt[N], to[N];
    int c[N];
    int cnt, num;
    int n, m;
    int in[N], out[N];

    void update(int x, int ad) {
        for (; x <= n; x += lowbit(x)) c[x] += ad;
    }

    int getsum(int x) {
        int sum = 0;
        for (; x ;x -= lowbit(x)) sum += c[x];
        return sum;
    }

    void add(int u, int v) {
        to[cnt] = v; nxt[cnt] = head[u]; head[u] = cnt++;
    }

    void dfs(int x) {
        in[x] = num;
        for (int i = head[x]; ~i; i = nxt[i]) {
            update(++num, 1);
            dfs(to[i]);
        }
        out[x] = num;
    }

    void solve() {
        memset(head, -1, sizeof head);
        memset(nxt, -1, sizeof nxt);
        cnt = num = 0;
        scanf("%d", &n);
        for (int i = 1, a, b; i < n; i++) {
            scanf("%d%d", &a, &b);
            add(a, b);
        }
        update(++num, 1);
        dfs(1);

        scanf("%d", &m);
        char str[5];
        int x;
        getchar();
        while (m--) {
            scanf("%s%d", str, &x);
            if (str[0] == 'Q') {
                printf("%d\n", getsum(out[x]) - getsum(in[x] - 1));
            }
            else {
                if (getsum(in[x]) - getsum(in[x] - 1) == 1)
                    update(in[x], -1);
                else
                    update(in[x], 1);
            }
        }
    }
}

#endif //POJ_POJ3321_H
