//
// Created by proverbs on 5/30/17.
//

#ifndef POJ_HDU2222_H
#define POJ_HDU2222_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

namespace HDU2222 {
    using namespace std;

#define N 10010
#define M 1000010
    struct TR {
        int son[26];
        int f;
        bool fg;// 为了保留Trie的原始形态，此处保留了fg，否则可以删除
        int ct;
    } tr[M];
    char a[M * 100];
    int cnt;
    int ans, n, cas;
    int q[M * 4];

    void insert(char *str) {
        int len = strlen(str);
        int now = 1; // root
        for (int i = 0, x; i < len; i++) {
            x = str[i] - 'a';
            if (!tr[now].son[x]) tr[now].son[x] = ++cnt;
            now = tr[now].son[x];
        }
        tr[now].fg = true;
        tr[now].ct++; //相同单词算两个
    }

    void build_trie() {
        int h = 1, t = 2, sta, ch, fl;
        q[1] = 1; // root
        while (h < t) {
            sta = q[h++];
            for (int i = 0; i < 26; i++) {
                ch = tr[sta].son[i];
                if (sta == 1) fl = 1;
                else fl = tr[tr[sta].f].son[i];
                if (!ch) tr[sta].son[i] = fl;
                else {
                    tr[ch].f = fl;
                    tr[ch].fg |= tr[fl].fg;
                    q[t++] = ch;
                }
            }
        }
    }

    void match() {
        int now = 1;
        int len = strlen(a);
        for (int i = 0, x, ch; i < len; i++) {
            x = a[i] - 'a';
            now = tr[now].son[x];
            if (tr[now].fg) {
                int up = now;
                while (tr[up].fg) {
                    ans += tr[up].ct;
                    tr[up].ct = 0;// 重复出现算一次
                    up = tr[up].f;
                }
            }
        }
    }

    void clear() {
        for (int i = 0; i <= cnt; i++) {
            for (int j = 0; j < 26; j++)
                tr[i].son[j] = 0;
            tr[i].ct = tr[i].f = 0;
            tr[i].fg = false;
        }
        ans = 0;
    }

    void solve() {
        scanf("%d", &cas);
        while (cas--) {
            cnt = 1;
            scanf("%d", &n);
            char str[55];
            for (int i = 0; i < n; i++) {
                scanf("%s", str);
                insert(str);
            }
            build_trie();
            scanf("%s", a);
            match();
            printf("%d\n", ans);
            clear();
        }
    }
}

#endif //POJ_HDU2222_H
