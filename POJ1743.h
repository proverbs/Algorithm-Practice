//
// Created by proverbs on 5/27/17.
//

#ifndef POJ_POJ1743_H
#define POJ_POJ1743_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

namespace POJ1743 {
    using namespace std;

# define N 20020

// sk中的两个元素可以相同，但是sa，sb中的不可以相同
// 所以，实际上sk和sa并不是互逆的
    int sk[N], rk[N], sa[N], sb[N], ht[N];
    int acc[N];

    int n, m, nn;
    int a[N];
    int b[N];

    void radix_sort() {
        // 原理是双关键字的基数排序
        // sk为第一关键字，sb为第二关键字排序
        // 其中，sb相当于上一轮的sa
        int i;
        for (i = 0; i < m; i++) acc[i] = 0;
        for (i = 0; i < n; i++) acc[sk[i]]++;
        for (i = 1; i < m; i++) acc[i] += acc[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--acc[sk[sb[i]]]] = sb[i];
    }

    bool cmp(int *f, int x, int y, int w) {
        // 比较字符串的大小，可以直接利用sk数组比较
        return f[x] == f[y] && f[x + w] == f[y + w];
    }

    void suffix_array(int *a) {
        for (int i = 0; i < n; i++) {
            sk[i] = a[i];
            // 为了一般性，最初设置一个基于位置的第二关键字
            sb[i] = i;
        }
        radix_sort();
        // 倍增
        // p=n时说明已经能够将n个后缀全部区分了
        for (int w = 1, p = 1, i; p < n; w <<= 1, m = p) {
            // 基数排序，求新的sa
            for (p = 0, i = n - w; i < n; i++)
                sb[p++] = i;
            for (i = 0; i < n; i++)
                if (sa[i] >= w) sb[p++] = sa[i] - w;
            radix_sort();
            // sb存放sk的一份拷贝，因为之后要利用当前sk更新之后的sk
            // 而且，在下一轮循环中，sb利用sk的值可以直接排序
            for (i = 0; i < n; i++) sb[i] = sk[i];
            // 更新sk
            p = 0;
            sk[sa[0]] = p++; // sa[0]永远都是n-1，即最后补上的0；而sk[sa[0]]即sk[n-1]=0
            for (i = 1; i < n; i++)
                // 此处的sb实际意义相当于sk
                sk[sa[i]] = cmp(sb, sa[i], sa[i - 1], w) ? p - 1 : p++;
        }
    }

    void get_ht() {
        int i, j, k = 0;
        // sk和sa是互逆的(rk[sa[0]]=0)
        for (i = 1; i <= nn; i++) rk[sa[i]] = i;
        // h[i] >= h[i-1]-1，其中h[i]=ht[rk[i]]
        for (i = 0; i < nn; ht[rk[i++]] = k)
            for (k ? k-- : 0, j = sa[rk[i] - 1]; b[i + k] == b[j + k]; k++);
    }

    bool check(int x) {
        int mx = sa[1], mn = sa[1];
        for (int i = 2; i < nn; i++) {
            if (ht[i] < x) mx = mn = sa[i];
            else {
                mx = max(mx, sa[i]);
                mn = min(mn, sa[i]);
                if (mx - mn >= x) return true;
            }
        }
        return false;
    }

    void solve() {
        while (scanf("%d", &nn), nn) {
            for (int i = 0; i < nn; i++) {
                scanf("%d", &a[i]);
            }
            nn -= 1;
            for (int i = 0; i < nn; i++) {
                b[i] = a[i] - a[i + 1] + 88;
            }
            m = 190;
            // 将字符串拓展一位，保证cmp函数中不会越界
            n = nn + 1;
            b[n - 1] = 0;
            suffix_array(b);
            get_ht();

            int ans = 0;
            int l = 4, r = nn / 2 + 1, mid;
            while (l <= r) {
                mid = (l + r) >> 1;
                if (check(mid)) ans = mid, l = mid + 1;
                else r = mid - 1;
            }
            if (ans < 4) puts("0");
            else printf("%d\n", ans + 1);
        }
    }
}


#endif //POJ_POJ1743_H
