#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 2003;


int n, m, k, t[MAXN][MAXN];
ll s[MAXN][MAXN];

inline ll hs(int row, int l, int r) {
    return s[row+1][r]-s[row+1][l]-s[row][r]+s[row][l];
}
inline ll vs(int col, int d, int u) {
    return s[u][col+1]-s[d][col+1]-s[u][col]+s[d][col];
}

int solve(int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            s[i+1][j+1] = s[i+1][j]+s[i][j+1]-s[i][j]+t[i][j];
        }
    }

    int ans = INF;
    for (int lftCut = 0; lftCut < m; lftCut++) {
        int minRghtCut = 0;
        int d = 0, l = 0, u = n, r = m;
        while (l < r and d < u) {
            while (true) {
                if (d < u and hs(d, l, r) <= k) {
                    // cerr << "cut " << "down" << endl;
                    d++;
                    continue;
                }
                if (d < u and hs(u-1, l, r) <= k) {
                    // cerr << "cut " << "up" << endl;
                    u--;
                    continue;
                }
                if (l < lftCut and vs(l, d, u) <= k) {
                    // cerr << "cut " << "left" << endl;
                    l++;
                    continue;
                }
                break;
            }
            if (l < r and d < u) {
                if (vs(r-1, d, u) > k) {
                    minRghtCut = INF;
                    break;
                }
                // cerr << "cut " << "right" << endl;
                minRghtCut++;
                r--;
            }
        }
        // cerr << lftCut << " ans is " << minRghtCut << endl;
        if (minRghtCut != INF)
            ans = min(ans, n+m-(r-l)-(u-d));
    }
    return ans;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> k >> m >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> t[i][j];
        }
    }

    int ans = solve(n, m);
    int N = max(n, m);
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            swap(t[i][j], t[j][i]);
        }
    }
    ans = min(ans, solve(m, n));
    cout << ans << endl;
}
