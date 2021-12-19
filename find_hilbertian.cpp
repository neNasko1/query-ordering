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

const int MAX_N = 4;

typedef array<array<int, MAX_N>, MAX_N> Path;
typedef vector<pair<int, int> > Points;
Points generate(int k) {
    Points ret = {};
    for(int i = 0; i < k; i ++) {
        ret.push_back({rand() % MAX_N, rand() % MAX_N});
    }
    return ret;
}

bool isCorrect(Path &path) {
    if(path[0][0] != 0) { return false; }
    if(path[0][MAX_N - 1] != MAX_N * MAX_N - 1) { return false; }
    for(int i = 0; i < MAX_N; i ++) {
        for(int j = 0; j < MAX_N; j ++) {
            if(path[i][j] == 0) {continue;}
            if(i != 0 && path[i - 1][j] == path[i][j] - 1) {continue;}
            if(j != 0 && path[i][j - 1] == path[i][j] - 1) {continue;}
            if(i != MAX_N - 1 && path[i + 1][j] == path[i][j] - 1) {continue;}
            if(j != MAX_N - 1 && path[i][j + 1] == path[i][j] - 1) {continue;}
            return false;
        }
    }
    return true;
}

int measure(Points &points, Path &path) {
    int ret = 0;
    sort(points.begin(), points.end(), [&](const auto &a, const auto &b) {
        return path[a.first][a.second] < path[b.first][b.second];
    });
    for(int i = 0; i < points.size() - 1; i ++) {
        ret += abs(points[i + 1].first - points[i].first) + abs(points[i + 1].second - points[i].second);
    }
    return ret;
}

Path best;
int score = 1e9;
vector<Points> points;


int cnt = 0;
Path path;

bool used[MAX_N][MAX_N];

bool broken() {
    for(int i = 0; i < MAX_N; i ++) {
        for(int j = 0; j < MAX_N; j ++) {
            used[i][j] = false;
        }
    }
    queue<pair<int, int> > q;
    q.push({0, MAX_N - 1});
    used[0][MAX_N - 1] = true;
    while(!q.empty()) {
        auto curr = q.front(); q.pop();
        if(curr.first != 0 && !used[curr.first - 1][curr.second] && path[curr.first - 1][curr.second] == -1) {
            q.push({curr.first - 1, curr.second});
            used[curr.first - 1][curr.second] = true;
        }
        if(curr.first != MAX_N - 1 && !used[curr.first + 1][curr.second] && path[curr.first + 1][curr.second] == -1) {
            q.push({curr.first + 1, curr.second});
            used[curr.first + 1][curr.second] = true;
        }
        if(curr.second != 0 && !used[curr.first][curr.second - 1] && path[curr.first][curr.second - 1] == -1) {
            q.push({curr.first, curr.second - 1});
            used[curr.first][curr.second - 1] = true;
        }
        if(curr.second != MAX_N - 1 && !used[curr.first][curr.second + 1] && path[curr.first][curr.second + 1] == -1) {
            q.push({curr.first, curr.second + 1});
            used[curr.first][curr.second + 1] = true;
        }
    }
    for(int i = 0; i < MAX_N; i ++) {
        for(int j = 0; j < MAX_N; j ++) {
            if(path[i][j] == -1 && !used[i][j]) {
                return true;
            }
        }
    }
    return false;
}

void dfs(int x, int y, int ind) {
    if(path[x][y] != -1) {return;}
    path[x][y] = ind;
    if(x == 0 && y == MAX_N - 1) {
        if(ind == MAX_N * MAX_N - 1) {
            int nowScore = 0;
            for(int i = 0; i < points.size(); i ++) {
                nowScore += measure(points[i], path);
            }

            if(nowScore < score) {
                score = nowScore;
                best = path;
            }
            cnt ++;
            if(cnt % 10000 == 0) {
                cout << cnt << " " << clock() << endl;
                cout << score << endl;
                for(int i = 0; i < MAX_N; i ++) {
                    for(int j = 0; j < MAX_N; j ++) {
                        cout << best[i][j] << " ";
                    }
                    cout << endl;
                }
            }
        }
        path[x][y] = -1;
        return;
    }
    if(broken()) {
        path[x][y] = -1;
        return;
    }
    if(ind == MAX_N * MAX_N - 1) {
        path[x][y] = -1;
        return;
    }
    vector<int> dir = {0, 1, 2, 3};
    random_shuffle(dir.begin(), dir.end());
    for(auto d : dir) {
        if(d == 0 && x != 0) { dfs(x - 1, y, ind + 1); }
        if(d == 1 && y != 0) { dfs(x, y - 1, ind + 1); }
        if(d == 2 && x != MAX_N - 1) { dfs(x + 1, y, ind + 1); }
        if(d == 3 && y != MAX_N - 1) { dfs(x, y + 1, ind + 1); }
    }
    path[x][y] = -1;
}

signed main() {
    for(int i = 0; i < MAX_N; i ++) {
        for(int j = 0; j < MAX_N; j ++) {
            path[i][j] = -1;
        }
    }

    for(int i = 0; i < 100; i ++) {
        points.push_back(generate(rand() % 4 + 4));
    }

    dfs(0, 0, 0);

    cout << cnt << endl;
    cout << score << endl;
    for(int i = 0; i < MAX_N; i ++) {
        for(int j = 0; j < MAX_N; j ++) {
            cout << best[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
