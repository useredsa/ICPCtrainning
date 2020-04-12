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


int n, a[MAXN], b[MAXN], par[MAXN];
vi gr[MAXN];
int dp[MAXN][2];

struct KMAX {
    int max1, max2;
    void push(int n) {
        if (n > max1)
            max2 = max1, max1 = n;
        else if (n > max2)
            max2 = n;
    }
    int query(int discard) {
        return (discard == max1? max2 : max1);
    }
} use[MAXN], nuse[MAXN];

void solve(int u, int p = -1) {
    par[u] = p;
    for (int v : gr[u]) {
        if (v == p) continue;
        solve(v, u);
        use[u].push(dp[v][1]);
        nuse[u].push(dp[v][0]);
    }
    dp[u][1] = nuse[u].query(0)+gr[u].size()-(p!=-1)-1;
    dp[u][0] = max(1+use[u].query(0), dp[u][1]);
}

int ans = 0;
void solve2(int u) {
    if (par[u] != -1) {
        use[u].push(dp[par[u]][1]);
        nuse[u].push(dp[par[u]][0]);
        ans = max(ans, nuse[u].query(0)+(int)gr[u].size()-1);
        ans = max(ans, 1+use[u].query(0));
    }
    for (int v : gr[u]) {
        if (v == par[u])
            continue;
        dp[u][1] = nuse[u].query(dp[v][0])+gr[u].size()-2;
        dp[u][0] = max(1+use[u].query(dp[v][1]), dp[u][1]);
        solve2(v);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 1; i < n; ++i) {
        cin >> a[i] >> b[i];
        --a[i], --b[i];
        gr[a[i]].push_back(b[i]);
        gr[b[i]].push_back(a[i]);
    }
    solve(0);
    solve2(0);
    cout << ans << '\n';
}
