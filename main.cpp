#include <iostream>
#include <vector>
#include <map>
#include <set>

#include "QuerySolvers.h"
    
struct SumContainer {
private:
    long long sum;

public:
    SumContainer() {
        sum = 0;
    }

    void change(int ind, long long oldVal, long long newVal) {
        sum = sum - oldVal + newVal;
    }

    void add(int ind, long long val) {
        sum = sum + val;
    }

    void remove(int ind, long long val) {
        sum = sum - val;
    }

    long long get() {
        return sum;
    }
};

struct MexContainer {
private:
    std::map<int, int> mp;
    std::set<std::pair<int, int> > st;

    void merge(int val) {
        std::pair<int, int> inter = {val, val};
        auto small = st.lower_bound(inter);
        if(small != st.begin()) {
            small --;
            if((*small).second == val - 1) {
                inter.first = (*small).first;
                st.erase(small);
            }
        }
        auto big = st.lower_bound(inter);
        if(big != st.end()) {
            if((*big).first == val + 1) {
                inter.second = (*big).second;
                st.erase(big);
            }
        }
        st.insert(inter);
    }

    void split(long long val) {
        auto interIt = st.lower_bound({val, 1e9});
        interIt --; // This has to exist;
        auto inter = (*interIt);
        st.erase(interIt);
        if(inter.first != val) {
            st.insert({inter.first, val - 1});
        }
        if(inter.second != val) {
            st.insert({val + 1, inter.second});
        }
    }

public:
    MexContainer() {}

    void change(int ind, long long oldVal, long long newVal) {
        remove(ind, oldVal);
        add(ind, newVal);
    }

    void add(int ind, long long val) {
        mp[val] += 1;
        if(mp[val] == 1) {
            merge(val);
        }
    }

    void remove(int ind, long long val) {
        mp[val] -= 1;
        if(mp[val] == 0) {
            split(val); 
        }
    }

    long long get() {
        if(st.empty()) {
            return 0;
        }
        auto it = st.begin();
        if((*it).first == 0) {
            return (*it).second + 1;
        } else {
            return 0;
        }
    }
};




void input() {
    std::cin >> n >> q;
    for(int i = 0; i < n; i ++) {
        std::cin >> arr[i];
        orig[i] = arr[i];    
    }

    for(int i = 0; i < q; i ++) {
        int type;
        std::cin >> type;
        if(type == 1) { // Query;
            int l, r;
            std::cin >> l >> r;

            Query newQuery(l, r, update.size(), query.size());
            query.push_back(newQuery);
        } else if(type == 2) {
            int ind;
            long long val;
            std::cin >> ind >> val;

            Update newUpdate(ind, val, arr[ind]);
            arr[ind] = val;
            update.push_back(newUpdate);
        }
    }

    for(int i = 0; i < n; i ++) {
        arr[i] = orig[i];
    }
    std::cout << "here" << std::endl;
}

void output() {
    long long ret = 0;
    long long mod = 1e9 + 7;
    long long base = 27;
    std::cout << query.size() << std::endl;
    for(int i = 0; i < query.size(); i ++) {
        ret = (ret * base + ans[i]) % mod;
        //std::cout << ans[i] << "\n"; 
    }
    std::cout << ret << std::endl;
}

int main(int argc, char **argv) {
    int algorithmNmb = 0;
    if(argc == 2) {
        algorithmNmb = atoi(argv[1]);
    } else if(argc > 2) {
        std::cerr << "Too many command line arguments, maybe there was an error?" << std::endl;
        return -1;
    }

    input();

    switch(algorithmNmb) {
        case 0: {
            Naive::solve<SumContainer>();
            break;
        }
        case 1: {
            SqrtDecomposition::solve<SumContainer>();
            break;
        }
        case 2: {
            HilbertOrderNoUpdate::solve<SumContainer>();
            break;
        }
        case 3: {
            HilbertOrderUpdate::solve<SumContainer>();
            break;
        }
        case 4: {
            SegmentTree::solve();
            break;
        }
        default: {
            std::cerr << "Unknwon algorithm - " << algorithmNmb << std::endl;
            return 2;
        }
    }

    output();
    return 0;
}
