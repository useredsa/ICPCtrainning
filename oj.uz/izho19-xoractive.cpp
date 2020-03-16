#include <bits/stdc++.h>
#include "interactive.h"
using namespace std;

using vi = vector<int>;


// log2(100) => 7
vector<int> guess(int n) {
    vi query, pxor1, pxor2, ans(n);
    map<int, int> reverse, substract;
    ans[0] = ask(1);

    for (int i = 0; i < 7; i++) { 
        query.clear();
        substract.clear();
        for (int j = 0; j < n; j++) {
            if (j & (1<<i)) {
                query.push_back(j+1);
            }
        }
        if (query.empty()) continue;

        pxor1 = get_pairwise_xor(query);
        query.push_back(1);
        pxor2 = get_pairwise_xor(query);
        for (int v : pxor1) {
            substract[v]--;
        }
        substract[0]--; // for combination (0,0)
        for (int v : pxor2) {
            substract[v]++;
        }

        for (const auto& pp : substract) {
            if (pp.second != 0) {
                reverse[pp.first^ans[0]] |= (1<<i);
            }
        }
    }

    for (const auto& pp : reverse) {
        ans[pp.second] = pp.first;
    }
    return ans;
}

