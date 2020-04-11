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

int ind[MAXN], seen[MAXN];
vi pos[MAXN];
vll sum[MAXN];
ll dp[MAXN], negsum[MAXN];

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // Read and add 0 and n to the beginning and end of the seqs
    cin >> n; ++n;
    for (int i = 1; i < n; ++i)
        cin >> a[i];
    for (int i = 1; i < n; ++i)
        cin >> p[i];
    cin >> m; ++m;
    for (int i = 1; i < m; ++i)
        cin >> b[i];
    a[n] = n;
    b[m] = n;
    ++n, ++m;

    // Compress the data and precalc prefix sums
    for (int i = 0, j = 0; i < m; ++i) {
        while (j < b[i])
            ind[j++] = 2*i-1;
        ind[j++] = 2*i;
        sum[2*i] = sum[2*i+1] = vll(1);
    }
    for (int i = 0; i < n; ++i) {
        a[i] = ind[a[i]];
        pos[a[i]].push_back(i);
        ll prevsum = sum[a[i]].back();
        sum[a[i]].push_back(prevsum+max(p[i], 0));
        negsum[i+1] = negsum[i]+min(p[i], 0);
    }

    memset(seen, -1, sizeof seen);
    memset(ind, 0, sizeof ind);
    seen[0] = 0;
    for (int i = 1; i < n; ++i) {
        dp[i] = INF;
        if ((a[i]&1) == 0) {
            if (int x = seen[a[i]-2]; x != -1) {
                dp[i] = dp[x]
                      + sum[a[i]-1][ind[a[i]-1]] + sum[a[i]][ind[a[i]]]
                      + negsum[i] - negsum[x+1];
                if (x = seen[a[i]], x != -1)
                    dp[i] = min(dp[i], dp[x] + negsum[i+1]-negsum[x+1]);
            }
        }
        seen[a[i]] = i;
        ind[a[i]]++;
    }

    if (dp[n-1] >= INF/2)
        cout << "NO\n";
    else
        cout << "YES\n" << dp[n-1] << "\n";
}
