#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const ll INF = 1e15+9;
const int MAXN = 1000006;


int n, m, a[MAXN], p[MAXN], b[MAXN];
int rev[MAXN];
vi pos[MAXN];
vll sum[MAXN];
ll dp[MAXN], negsum[MAXN];

inline ll isum(int val, int R) {
    int index = lower_bound(pos[val].begin(), pos[val].end(), R)-pos[val].begin();
    return sum[val][index];
}


int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }
    cin >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> b[i];
    }
    a[n+1] = n+1;
    b[m+1] = n+1;
    ++n, ++m;

    for (int i = 0; i <= m; ++i) {
        sum[2*i+1] = sum[2*i] = vll(1);
    }
    for (int i = 0; i <= n; ++i) {
        int bi = lower_bound(b, b+m, a[i])-b;
        a[i] = 2*bi-(b[bi]!=a[i]);
        pos[a[i]].push_back(i);
        ll prevsum = sum[a[i]].back();
        sum[a[i]].push_back(prevsum+max(p[i], 0));
        negsum[i+1] = negsum[i]+min(p[i], 0);
    }

    for (int i = 1; i <= n; ++i) {
        if (a[i]&1) {
            dp[i] = INF;
            continue;
        }
        auto it = lower_bound(pos[a[i]-2].begin(), pos[a[i]-2].end(), i);
        if (it == pos[a[i]-2].begin()) {
            dp[i] = INF;
            continue;
        }
        --it;

        dp[i] = dp[*it] + isum(a[i]-1, i) + isum(a[i], i) + negsum[i] - negsum[*it+1];

        it = lower_bound(pos[a[i]].begin(), pos[a[i]].end(), i);
        if (it != pos[a[i]].begin()) {
            --it;
            dp[i] = min(dp[i], dp[*it] + negsum[i+1]-negsum[*it+1]);
        }
    }

    if (dp[n] >= INF/2) {
        cout << "NO\n";
    } else {
        cout << "YES\n" << dp[n] << "\n";
    }
}
