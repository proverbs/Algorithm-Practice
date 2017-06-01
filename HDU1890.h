//
// Created by proverbs on 6/1/17.
//

#ifndef POJ_HDU1890_H
#define POJ_HDU1890_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>

namespace HDU1890 {
    using namespace std;

#define N 100010

    struct PX {
        int va, id;
    }px[N];

    int rk[N], pos[N];
    int son[N][2], fa[N], rev[N], sz[N];
    int cnt, root, n;

    bool cmp(const PX &a, const PX &b) {
        if (a.va == b.va) return a.id < b.id;
        return a.va < b.va;
    }

    bool cmp1(const PX &a, const PX &b) {
        return a.id < b.id;
    }

    void newnode(int y, int &x) {
        x = ++cnt;
        fa[x] = y;
        sz[x] = 1;
        rev[x] = false;
        son[x][0] = son[x][1] = 0;
    }

    void init() {
        cnt = 0;
        // 加入首尾节点方便提取区间
        newnode(0, root);// 1为首节点
        newnode(root, son[root][1]);// 2为末节点
        sz[root] = 2;
    }

    void reverse(int x) {
        if (!x) return;
        rev[x] ^= 1;// lazy
    }

    void pushup(int x) {
        sz[x] = sz[son[x][0]] + sz[son[x][1]] + 1;
    }

    void pushdown(int x) {
        if (!x || !rev[x]) return;
        rev[x] = false;
        reverse(son[x][0]);
        reverse(son[x][1]);
        swap(son[x][0], son[x][1]);
    }

    void build(int &x, int l, int r, int g) {
        if (l > r) return;
        int mid = (l + r) >> 1;
        newnode(g, x);
        pos[rk[mid]] = x; // pos[i]排名为i的数字对应splay中的节点号
        build(son[x][0], l, mid - 1, x);
        build(son[x][1], mid + 1, r, x);
        pushup(x);
    }

    void link(int x, int y, int c) {
        fa[x] = y;
        son[y][c] = x;
    }

    void rotate(int x, int c) {
        int y = fa[x];
        pushdown(y);
        pushdown(x);
        link(x, fa[y], son[fa[y]][1] == y);
        link(son[x][!c], y, c);
        link(y, x, !c);
        pushup(y);
    }

    void splay(int x, int g) {
        pushdown(x);
        int y, cy, cx;
        while (fa[x] != g) {
            y = fa[x];
            pushdown(fa[y]);
            pushdown(y);
            pushdown(x);
            cy = son[fa[y]][1] == y;
            cx = son[y][1] == x;
            if (fa[y] == g) rotate(x, cx);
            else {
                if (cx == cy) rotate(y, cy);
                else rotate(x, cx);
                rotate(x, cy);
            }
        }
        pushup(x);
        if (!g) root = x;
    }

    int getmax(int x) {
        // 从上向下必须pushdown
        pushdown(x);
        while (son[x][1]) {
            x = son[x][1];
            pushdown(x);
        }
        return x;
    }

    void del() {
        int x = root;
        if (son[x][0] && son[x][1]) {
            int y = getmax(son[x][0]);
            splay(y, x);
            fa[y] = 0;
            root = y;
            fa[son[x][1]] = y;
            son[y][1] = son[x][1];
            pushup(y);
        }
        else if (son[x][0]) fa[son[x][0]] = x, root = son[x][0];
        else fa[son[x][1]] = x, root = son[x][1];
    }

    void solve() {
        while (scanf("%d", &n), n) {
            for (int i = 1; i <= n; i++) {
                scanf("%d", &px[i].va);
                px[i].id = i;
            }
            sort(px + 1, px + 1 + n, cmp);
            for (int i = 1; i <= n; i++)
                rk[px[i].id] = i;// rk[x]表示原数组中索引为x的数的排名
            sort(px + 1, px + 1 + n, cmp1);
            init();
            build(son[son[root][1]][0], 1, n, son[root][1]);
            pushup(son[root][1]);
            pushup(root);
            for (int i = 1; i <= n; i++) {
                splay(pos[i], 0);
                splay(1, pos[i]);// root == pos[i]
                printf("%d", i + sz[son[1][1]]);
                if (i < n) printf(" ");
                rev[son[1][1]] ^= 1;
                del();// 对root操作不需要向上pushup
            }
            puts("");
        }
    }

}

#endif //POJ_HDU1890_H
