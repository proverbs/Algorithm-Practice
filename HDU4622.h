//
// Created by proverbs on 6/6/17.
//

#ifndef POJ_HDU4622_H
#define POJ_HDU4622_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace HDU4622 {
    using namespace std;

#define N 2010

    struct SAM {
        int son[26];
        int lm, fa;
        int right;
    }sam[N << 1];

    int cnt;
    int head, last;
    int sum[N][N];
    char a[N];

    int newnode() {
        ++cnt;
        for (int i = 0; i < 26; i++)
            sam[cnt].son[i] = -1;
        sam[cnt].fa = -1;
        sam[cnt].lm = 0;
        return cnt;
    }

    void init_sam() {
        cnt = 0;
        head = last = newnode();
    }

    int add(int x) {
        int p = last;
        int np = newnode();
        sam[np].lm = sam[p].lm + 1;
        for (; ~p && sam[p].son[x] == -1; p = sam[p].fa)
            sam[p].son[x] = np;
        if (p == -1) sam[np].fa = head;
        else {
            int q = sam[p].son[x];
            if (sam[p].lm + 1 == sam[q].lm)
                sam[np].fa = q;
            else {
                int nq = newnode();
                sam[nq] = sam[q];// 隐含sam[nq].fa = sam[q].fa
                sam[nq].lm = sam[p].lm + 1;
                sam[q].fa = sam[np].fa = nq;
                for (; ~p && sam[p].son[x] == q; p = sam[p].fa)
                    sam[p].son[x] = nq;
            }
        }
        last = np;
        // 设当前字符串为T，插入x，新增的字符串都是Tx的后缀
        // pa = sam[np].fa表示的right集合中包含非L+1的成分，也就是这个集合表示的（在min(pa)和max(pa)限制下的）Tx的后缀与之T中的某些（个）子串相同
        // 同理沿着fa到达的节点表示的Tx的后缀都是会逐渐缩小max的，所以只有比max(p)长的后缀才是新增加的，也就是下面这个式子了
        // 这个值的理解非常考验对SAM的理解
        return sam[np].lm - sam[sam[np].fa].lm;
    }

    void solve() {
        int cas, qu;
        cin >> cas;
        while (cas--) {
            scanf("%s", a + 1);
            int len = strlen(a + 1);

            for (int i = 1; i <= len; i++) {
                init_sam();
                sum[i][i] = add(a[i] - 'a');
                for (int j = i + 1; j <= len; j++) {
                    sum[i][j] = sum[i][j - 1] + add(a[j] - 'a');
                }
                //cout << i << endl;
            }

            scanf("%d", &qu);
            int x, y;
            while (qu--) {
                scanf("%d%d", &x, &y);
                printf("%d\n", sum[x][y]);
            }
        }
    }

}

#endif //POJ_HDU4622_H
