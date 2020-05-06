#include<bits/stdc++.h>
using namespace std;
using ll = long long;

ll n, l, x, t;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t;
    while (t--) {
        cin >> x >> l >> n;
        n<<=1;
        ll k = l/n+1, zeros = k+2+(k&1);
        --x;
        if (k <= 60) x = x&((1LL<<(k+1))-1);
        zeros -= __builtin_popcountll(x);
        cout << k*n+(zeros&1) << "\n";
    }
}
