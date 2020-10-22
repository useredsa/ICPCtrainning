#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 305;


int n, m, l[MAXN*MAXN], r[MAXN*MAXN], w[MAXN*MAXN];
int val[MAXN][MAXN], maxw[MAXN][MAXN][MAXN];
ll mem[MAXN][MAXN];

ll dp(int L, int R) {
    if (mem[L][R] != -1) return mem[L][R];
    mem[L][R] = 0;
    for (int p = L; p < R; ++p) {
        mem[L][R] = max(mem[L][R], maxw[L][R][p]+dp(L, p)+dp(p+1,R));
    }
    return mem[L][R];
}

int main () {
    freopen("pieaters.in", "r", stdin);
    freopen("pieaters.out", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> w[i] >> l[i] >> r[i]; --l[i];
        val[l[i]][r[i]] = w[i];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j+i <= n; ++j) {
            for (int k = j; k < j+i; ++k) {
                maxw[j][j+i][k] =
                  max(val[j][j+i], max(maxw[j+1][j+i][k], maxw[j][j+i-1][k]));
            }
        }
    }

    memset(mem, -1, sizeof(mem));
    cout << dp(0, n) << endl;
}

