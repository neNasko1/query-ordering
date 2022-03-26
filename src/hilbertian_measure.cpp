#include <bits/stdc++.h>

long long getIndex2d(int l, int r, long long n) {
    if(n == 1) {
        assert(l == 0 && r == 0);
        return 0;
    }
    bool lsmall = l < n / 2, rsmall = r < n / 2;
    const long long I = n / 2 - 1;
    l %= n / 2;
    r %= n / 2;
    long long delta = n * n / 4;
    if(lsmall && rsmall) {
        return getIndex2d(r, l, n - 1);
    } else if(!lsmall && rsmall) {
        return getIndex2d(l, r, n - 1) + delta;
    } else if(!lsmall && !rsmall) {
        return getIndex2d(l, r, n - 1) + 2ll * delta;
    } else {
        return getIndex2d(I - r, I - l, n - 1) + 3ll * delta;
    }
}

long long getIndex2d3(int l, int r, long long n) {
    if(n == 3) {
        int index[3][3] = {{0, 7, 8}, {1, 6, 5}, {2, 3, 4}};
        return index[l][r];
    }
    bool lsmall = l < n / 2, rsmall = r < n / 2;
    const long long I = n / 2 - 1;
    l %= n / 2;
    r %= n / 2;
    long long delta = n * n / 4;
    if(lsmall && rsmall) {
        return getIndex2d(r, l, n - 1);
    } else if(!lsmall && rsmall) {
        return getIndex2d(l, r, n - 1) + delta;
    } else if(!lsmall && !rsmall) {
        return getIndex2d(l, r, n - 1) + 2ll * delta;
    } else {
        return getIndex2d(I - r, I - l, n - 1) + 3ll * delta;
    }
}

long long getIndex2d5(int l, int r, long long n) {
    if(n == 5) {
        int index[5][5] = {0, 1, 22, 23, 24, 3, 2, 21, 20, 19, 4, 5, 12, 13, 18, 7, 6, 11, 14, 17, 8, 9, 10, 15, 16};
        return index[l][r];
    }
    bool lsmall = l < n / 2, rsmall = r < n / 2;
    const long long I = n / 2 - 1;
    l %= n / 2;
    r %= n / 2;
    long long delta = n * n / 4;
    if(lsmall && rsmall) {
        return getIndex2d(r, l, n - 1);
    } else if(!lsmall && rsmall) {
        return getIndex2d(l, r, n - 1) + delta;
    } else if(!lsmall && !rsmall) {
        return getIndex2d(l, r, n - 1) + 2ll * delta;
    } else {
        return getIndex2d(I - r, I - l, n - 1) + 3ll * delta;
    }
}

signed main() {
    int PW = 10;
    int n = 5 * (1 << PW) / 8;
    int k = 3 * n;
    long long sum1 = 0, sum2 = 0;
    for(int i = 0; i < 1000; i ++) {
        std::vector<std::pair<int, int> > points;
        int total = rand() % (2 * n);
        for(int j = 0; j < total; j ++) {
            points.emplace_back(rand() % n, rand() % n);
        }
        std::sort(points.begin(), points.end(), [&](auto a, auto b) {
            return getIndex2d(a.first, a.second, (1 << PW)) < getIndex2d(b.first, b.second, (1 << PW));
        });
        for(int i = 1; i < points.size(); i ++) {
            sum1 += (points[i].first - points[i - 1].first) + (points[i].second - points[i - 1].second);
        }
        std::sort(points.begin(), points.end(), [&](auto a, auto b) {
            return getIndex2d5(a.first, a.second, n) < getIndex2d3(b.first, b.second, n);
        });
        for(int i = 1; i < points.size(); i ++) {
            sum2 += (points[i].first - points[i - 1].first) + (points[i].second - points[i - 1].second);
        }
        std::cout << sum1 << " " << sum2 << std::endl;
    }

    return 0;
}

