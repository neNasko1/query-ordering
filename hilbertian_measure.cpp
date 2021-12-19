#include <bits/stdc++.h>
using namespace std;
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
#ifndef LOCAL
#define cerr if(false) cerr
#endif
#define endl "\n"
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x.size())
typedef long long ll;
template<class T, template<class T2, class A=allocator<T2> > class cont> inline ostream &operator <<(ostream &out, const cont<T> &x) { for(const auto &it : x) { out << it << " ";} return out;}
template<class T, template<class T2, class A=allocator<T2> > class cont> inline istream &operator >>(istream &in, cont<T> &x) { for(auto &it : x) { in >> it;} return in;}
template<class T, class T2> inline ostream &operator <<(ostream &out, const pair<T, T2> &x) { out << x.first << " " << x.second; return out;}
template<class T, class T2> inline istream &operator >>(istream &in, pair<T, T2> &x) { in >> x.first >> x.second; return in;}
template<class T, class T2> inline bool chkmax(T &x, const T2 &y) { return x < y ? x = y, 1 : 0; }
template<class T, class T2> inline bool chkmin(T &x, const T2 &y) { return x > y ? x = y, 1 : 0; }
const ll mod = 1e9 + 7;

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
        vector<pair<int, int> > points;
        int total = rand() % (2 * n);
        for(int j = 0; j < total; j ++) {
            points.emplace_back(rand() % n, rand() % n);
        }
        sort(points.begin(), points.end(), [&](auto a, auto b) {
            return getIndex2d(a.first, a.second, (1 << PW)) < getIndex2d(b.first, b.second, (1 << PW));
        });
        for(int i = 1; i < points.size(); i ++) {
            sum1 += (points[i].first - points[i - 1].first) + (points[i].second - points[i - 1].second);
        }
        sort(points.begin(), points.end(), [&](auto a, auto b) {
            return getIndex2d5(a.first, a.second, n) < getIndex2d3(b.first, b.second, n);
        });
        for(int i = 1; i < points.size(); i ++) {
            sum2 += (points[i].first - points[i - 1].first) + (points[i].second - points[i - 1].second);
        }
        cout << sum1 << " " << sum2 << endl;
    }

    return 0;
}

