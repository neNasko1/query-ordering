#include <iostream>
#include <random>
#include <time.h>
#include <assert.h>
#include <vector>
#include <algorithm>

#include "defines.h"

int main(int argc, char **argv) {
    bool updates = false;
    if(argc >= 2) {
        srand(atoi(argv[1]));
    }
    if(argc >= 3) {
        updates = (bool)(atoi(argv[2]));
    }
    srand(time(NULL));

    auto goodRand = [&]() {
        return (long long)rand() + ((long long)rand() << (long long)16);
    };

    int n = MAX_N, q = MAX_Q;
    //int n = goodRand() % MAX_N + 1, q = goodRand() % MAX_Q + 1;

    std::cout << n << " " << q << std::endl;

    for(int i = 0; i < n; i ++) {
        std::cout << goodRand() << " ";
    }
    std::cout << std::endl;

    std::vector<std::pair<int, std::pair<long long, long long> > > quer;

    for(int i = 0; i < q; i ++) {
        int l = goodRand() % n;
        int r = goodRand() % n;
        if(l > r) { std::swap(l, r); } 
        quer.push_back({1, {l, r}});
    }
    if(updates) {
        for(int i = 0; i < q; i ++) {
            int ind = goodRand() % n;
            int val = goodRand() % 200;
            quer.push_back({2, {ind, val}});
        }        
    }
    std::random_shuffle(quer.begin(), quer.end());
    for(auto it : quer) {
        std::cout << it.first << " " << it.second.first << " " << it.second.second << std::endl;
    }

    return 0;
}