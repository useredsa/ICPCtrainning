#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 1100006;

#include "doll.h"

int sm[MAXN], add[MAXN], nxt[MAXN];

void create_circuit(int M, vector<int> A) {
    vi C(M+1, -1), X, Y, gr;
    for (int i = 1; i < (int) A.size(); ++i) {
        gr.push_back(A[i]);
    }
    gr.push_back(0);
    C[0] = A[0];

    int n = 2;
    while (n < (int)gr.size())
        n<<=1;
    int extra = n-(int)gr.size();

    sm[1] = 0;
    add[1] = 1;
    // This is like radix sort (in case anyone is interested)
    for (int j = 1; j < n; ++j) {
        sm[j<<1] = sm[j];
        sm[j<<1|1] = sm[j]+add[j];
        add[j<<1] = add[j<<1|1] = add[j]<<1;
    }
    for (int j = 0, erased = 0; j < n; ++j) {
        if (sm[n+j] < extra) erased++;
        else nxt[sm[n+j]] = gr[j-erased];
    }

    sm[0] = 0;
    add[0] = n>>1;
    X.emplace_back(), Y.emplace_back();
    for (int s = 0; s < (int) X.size(); ++s) {
        if (add[s] == 1) {
            X[s] = sm[s] < extra? -1 : nxt[sm[s]];
            Y[s] = nxt[sm[s]+1];
            continue;
        }
        if (sm[s]+add[s] <= extra) {
            X[s] = -1;
        } else {
            X[s] = -X.size()-1;
            sm[X.size()] = sm[s];
            add[X.size()] = add[s]>>1;
            X.emplace_back(), Y.emplace_back();
        }
        Y[s] = -X.size()-1;
        sm[X.size()] = sm[s]+add[s];
        add[X.size()] = add[s]>>1;
        X.emplace_back(), Y.emplace_back();
    }

    answer(C, X, Y);
}
