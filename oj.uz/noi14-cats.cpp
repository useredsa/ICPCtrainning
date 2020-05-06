#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 1000006;


ll n, l, x, t;

ll f(ll n, ll l, ll x) {
    vi s1;
    ll s2 = 0;
    ll c = 0;
    while (x > 0) {
        if (s1.empty())
            s1.push_back(c);
        s2 = s1.back();
        s1.pop_back();
        for (auto& v : s1) {
            v ^= 1;
        }
        c ^= 1;
        if (s2 > l) {
            if (--x == 0) {
                return s2;
            }
        } else {
            s2 += 2*n;
            s1.push_back(s2);
            s1.push_back(s2);
        }
    }
    return 0;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t;
    while (t--) {
        cin >> x >> l >> n;
        // cerr << f(n, l, x) << "\n";
        n<<=1;
        --x;
        ll k = l/n+1;
        ll zeros = k+2+(k&1);
        if (k <= 60)
            x = x&((1LL<<(k+1))-1);
        zeros -= __builtin_popcountll(x);
        cout << k*n+(zeros&1) << "\n";
    }
}
