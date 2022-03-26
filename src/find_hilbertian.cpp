#include <bits/stdc++.h>

const int MAX_N = 4;

typedef std::array<std::array<int, MAX_N>, MAX_N> Path;
typedef std::vector<std::pair<int, int> > Points;
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
    std::sort(points.begin(), points.end(), [&](const auto &a, const auto &b) {
        return path[a.first][a.second] < path[b.first][b.second];
    });
    for(int i = 0; i < points.size() - 1; i ++) {
        ret += abs(points[i + 1].first - points[i].first) + abs(points[i + 1].second - points[i].second);
    }
    return ret;
}

Path best;
int score = 1e9;
std::vector<Points> points;

int cnt = 0;
Path path;

bool used[MAX_N][MAX_N];

bool broken() {
    for(int i = 0; i < MAX_N; i ++) {
        for(int j = 0; j < MAX_N; j ++) {
            used[i][j] = false;
        }
    }
    std::queue<std::pair<int, int> > q;
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
                std::cout << cnt << " " << clock() << std::endl;
                std::cout << score << std::endl;
                for(int i = 0; i < MAX_N; i ++) {
                    for(int j = 0; j < MAX_N; j ++) {
                        std::cout << best[i][j] << " ";
                    }
                    std::cout << std::endl;
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
    std::vector<int> dir = {0, 1, 2, 3};
    std::random_shuffle(dir.begin(), dir.end());
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

    std::cout << cnt << std::endl;
    std::cout << score << std::endl;
    for(int i = 0; i < MAX_N; i ++) {
        for(int j = 0; j < MAX_N; j ++) {
            std::cout << best[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
