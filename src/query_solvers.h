#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cassert>
#include <fstream>

#include "defines.h"

struct Query {
    int l, r, upd;
    int ind;
    long long ord;
    Query(int l, int r, int upd, int ind) : l(l), r(r), upd(upd), ind(ind) {}
};

struct Update {
    int ind;
    long long val, old;
    Update(int ind, long long val, long long old) : ind(ind), val(val), old(old) {}
};

int n, q;
long long arr[MAX_N];
long long orig[MAX_N];
long long ans[MAX_Q];
std::vector<Query> query;
std::vector<Update> update;

void print() {
    std::ofstream out("outputs/ordering.xyz");
    long long sum = 0;
    for(int i = 0; i < query.size() - 1; i ++) {
        sum += abs(query[i].l - query[i + 1].l) + abs(query[i].r - query[i + 1].r);
        out << query[i].l << " " << query[i].r << " " << query[i].upd << " " << i << " " << std::endl;
    }
    out.close();
}

namespace Naive {

template<class GenericContainer>
void solve() {
    int updatesDone = 0;

    for(int i = 0; i < query.size(); i ++) {
        assert(i == 0 || query[i].upd >= query[i - 1].upd);

        while(updatesDone < query[i].upd) {
            arr[update[updatesDone].ind] = update[updatesDone].val;
            updatesDone ++;
        }

        GenericContainer cont;
        for(int el = query[i].l; el <= query[i].r; el ++) {
            cont.add(el, arr[el]);
        }
        ans[query[i].ind] = cont.get();
    }
}

};

namespace SqrtDecomposition {

template<class GenericContainer>
void solve() {
    auto cmp = [](const Query &a, const Query &b) {
        if(a.l / SQRT == b.l / SQRT) {
            if(a.upd / SQRT == b.upd / SQRT) {
                return a.r < b.r;
            }
            return a.upd < b.upd;
        }
        return a.l < b.l;
    };
    std::sort(query.begin(), query.end(), cmp);

    std::cout << "here" << std::endl;
    
    GenericContainer cont;

    int l = 0, r = -1, u = 0;
    for(int i = 0; i < query.size(); i ++) {
        int ql = query[i].l, qr = query[i].r, qu = query[i].upd;
    
        while(l > ql) { cont.add(l - 1, arr[l - 1]); l --; }
        while(r < qr) { cont.add(r + 1, arr[r + 1]); r ++; }
        while(l < ql) { cont.remove(l, arr[l]); l ++; }
        while(r > qr) { cont.remove(r, arr[r]); r --; }
        while(u < qu) { 
            if(l <= update[u].ind && update[u].ind <= r) {
                cont.change(update[u].ind, update[u].old, update[u].val); 
            }
            arr[update[u].ind] = update[u].val; 
            u ++; 
        }
        while(u > qu) { 
            if(l <= update[u - 1].ind && update[u - 1].ind <= r) {
                cont.change(update[u - 1].ind, update[u - 1].val, update[u - 1].old); 
            }
            arr[update[u - 1].ind] = update[u - 1].old; 
            u --; 
        }

        ans[query[i].ind] = cont.get();
    }
}

};

namespace HilbertOrderNoUpdate {

long long getIndex2d(int l, int r, long long n) {
    if(n == 0) {
        assert(l == 0 && r == 0);
        return 0;
    }
    bool lsmall = l < (1 << (n-1)), rsmall = r < (1ll << (n-1));
    const long long I = (1ll << (n-1ll)) - 1;
    l %= (1 << (n-1));
    r %= (1 << (n-1));
    long long delta = (1ll << (2ll*n-2ll));
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

bool cmp(const Query &a, const Query &b) {
    return a.ord < b.ord;
} 

template<class GenericContainer>
void solve() {
    for(auto &quer : query) {
        quer.ord = getIndex2d(quer.l, quer.r, MAX_LOG_N);
    }
    std::sort(query.begin(), query.end(), cmp);
    
    GenericContainer cont;

    int l = 0, r = - 1;
    for(int i = 0; i < query.size(); i ++) {
        int ql = query[i].l, qr = query[i].r;
        while(l > ql) { cont.add(l - 1, arr[l - 1]); l --; }
        while(r < qr) { cont.add(r + 1, arr[r + 1]); r ++; }
        while(l < ql) { cont.remove(l, arr[l]); l ++;}
        while(r > qr) { cont.remove(r, arr[r]); r --;}

        ans[query[i].ind] = cont.get();
    }
}

};

namespace HilbertOrderUpdate {

long long getIndex3d(int x, int y, int z, long long n) {
    if(n == 0) {
        assert(x == 0 && y == 0 && z == 0);
        return 0;
    }
    bool xsmall = x < (1ll << (n-1ll)), ysmall = y < (1ll << (n-1ll)), zsmall = z < (1ll << (n-1ll));
    const long long I = (1ll << (n-1ll)) - 1;
    x %= (1 << (n-1));
    y %= (1 << (n-1));
    z %= (1 << (n-1));
    long long delta = (1ll << (3ll*n-3ll));
    if(xsmall && ysmall && zsmall) {
        return getIndex3d(z, y, x, n - 1);
    } else if(xsmall && ysmall && !zsmall) {
        return getIndex3d(y, x, z, n - 1) + delta; 
    } else if(xsmall && !ysmall && !zsmall) { 
        return getIndex3d(y, x, z, n - 1) + 2ll * delta; 
    } else if(xsmall && !ysmall && zsmall) {
        return getIndex3d(x, I - y, I - z, n - 1) + 3ll * delta;
    } else if(!xsmall && !ysmall && zsmall) {
        return getIndex3d(x, I - y, I - z, n - 1) + 4ll * delta;
    } else if(!xsmall && !ysmall && !zsmall) {
        return getIndex3d(I - y, I - x, z, n - 1) + 5ll * delta;
    } else if(!xsmall && ysmall && !zsmall) {
        return getIndex3d(I - y, I - x, z, n - 1) + 6ll * delta;
    } else {
        return getIndex3d(I - z, y, I - x, n - 1) + 7ll * delta;
    }
}

bool cmp(const Query &a, const Query &b) {
    return a.ord < b.ord;
} 

template<class GenericContainer>
void solve() {
    for(auto &quer : query) {
        quer.ord = getIndex3d(quer.l, quer.r, quer.upd, MAX_LOG_N);
    }
    std::sort(query.begin(), query.end(), cmp);

    GenericContainer cont;

    int l = 0, r = -1, u = 0;
    for(int i = 0; i < query.size(); i ++) {
        int ql = query[i].l, qr = query[i].r, qu = query[i].upd;
    
        while(l > ql) { cont.add(l - 1, arr[l - 1]); l --; }
        while(r < qr) { cont.add(r + 1, arr[r + 1]); r ++; }
        while(l < ql) { cont.remove(l, arr[l]); l ++; }
        while(r > qr) { cont.remove(r, arr[r]); r --; }

        while(u < qu) { 
            if(l <= update[u].ind && update[u].ind <= r) {
                cont.change(update[u].ind, update[u].old, update[u].val); 
            }
            arr[update[u].ind] = update[u].val; 
            u ++; 
        }

        while(u > qu) { 
            if(l <= update[u - 1].ind && update[u - 1].ind <= r) {
                cont.change(update[u - 1].ind, update[u - 1].val, update[u - 1].old); 
            }
            arr[update[u - 1].ind] = update[u - 1].old; 
            u --; 
        }

        ans[query[i].ind] = cont.get();
    }
}

};

namespace SegmentTree {

// https://algorithmica.org/en/eytzinger
const int BLOCK_SIZE = 64 / sizeof(long long);

struct SegmentTree {
    long long tree[2 * MAX_N];
    SegmentTree() {
        for(int i = 0; i < 2 * MAX_N; i ++) {
            tree[i] = 0;
        }
    }
    void upd(int curr, int l, int r, int ind, long long val) {
        if(l == r && l == ind) {
            tree[curr] = val;
            return;
        } else if(l > ind || r < ind) {
            return;
        }
        int m = (l + r) / 2ll;
        upd(curr * 2, l, m, ind, val);
        upd(curr * 2 + 1, m + 1, r, ind, val);
        tree[curr] = tree[curr * 2] + tree[curr * 2 + 1];
    }
    long long sum(int curr, int l, int r, int ql, int qr) {
        if(ql <= l && r <= qr) {
            //__builtin_prefetch(tree + curr * BLOCK_SIZE);
            return tree[curr];
        } else if(ql > r || qr < l) {
            return 0;
        }
        int m = (l + r) / 2ll;
        return sum(curr * 2, l, m, ql, qr) + sum(curr * 2 + 1, m + 1, r, ql, qr);
    }
};

SegmentTree st;
void solve() {
    int updatesDone = 0;

    for(int i = 0; i < n; i ++) {
        st.upd(1, 0, MAX_N - 1, i, arr[i]);
    }

    for(int i = 0; i < query.size(); i ++) {
        assert(i == 0 || query[i].upd >= query[i - 1].upd);

        while(updatesDone < query[i].upd) {
            st.upd(1, 0, MAX_N - 1, update[updatesDone].ind, update[updatesDone].val);
            updatesDone ++;
        }

        ans[query[i].ind] = st.sum(1, 0, MAX_N - 1, query[i].l, query[i].r);
    }
}

};