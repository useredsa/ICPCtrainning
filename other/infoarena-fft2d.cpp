#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 33;


int F, T, Fmask;
vi gr[MAXN];
map<int, ll> dp[MAXN][MAXN];

int mask(int h1, int h2) {
    return Fmask^(Fmask>>h1)^(Fmask>>h2);
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("fft2d.in", "r", stdin);
    freopen("fft2d.out", "w", stdout);
    cin >> F >> T;
    F--;
    Fmask = (1<<F)-1;
    for (int i = 0, h, x; i < T; i++) {
        cin >> h >> x;
        gr[h].push_back(x);
    }
    ll ans = 1LL<<(2*F);
    for (int h = F; h >= 0; h--) {
        for (int x : gr[h]) {
            ll curans = 1<<(F-h); // number of white nodes blocked by this node
                                  // (being the last)
            for (int h2 = h+1; h2 <= F; h2++) {
                curans -= dp[h][h2][mask(h, h2) & x];
            }
            for (int h2 = 0; h2 < h; h2++) {
                dp[h2][h][mask(h2, h) & x] += curans;
            }
            ans -= curans<<h;
            // cerr << "map" << endl;
            // for (const auto &pp : dp) {
            //     if (pp.second == 0) continue;
            //     const iii& v = pp.first;
            //     cerr << v.f << " " << v.s << " " << v.t << "->" << pp.second << endl;
            // }
        }
    }
    cout << ans << endl;
}

