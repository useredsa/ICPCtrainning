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


int R, S;
vii LE[MAXN], RE[MAXN];
string r[MAXN];
int dp[MAXN], olddp[MAXN], adp[MAXN][MAXN];

void calc_adp() {
    for (int i = 1; i <= S; ++i) {
        for (auto [L, v] : RE[i-1]) {
            adp[i-1][i] += v;
            if (L > 0) adp[L-1][i] -= v;
        }
        for (int j = i-1; j >= 0; --j) {
            adp[j][i] += adp[j+1][i];
        }
        for (int j = i-1; j >= 0; --j) {
            adp[j][i] += adp[j][i-1];
        }
    }
}

void solve(int L, int R, int optL, int optR) {
    if (R <= L) return;
    int m = (L+R)/2, opt = m;
    dp[m] = 0;
    for (int i = max(m+1, optL); i <= optR; ++i) {
        if (olddp[i]+adp[m][i] > dp[m]) {
            dp[m] = olddp[i]+adp[m][i];
            opt = i;
        }
    }
    solve(L, m, optL, opt);
    solve(m+1, R, opt, optR);
}


int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> R >> S;
    for (int i = 0; i < R; ++i) {
        cin >> r[i];
    }

    queue<ii> myq;
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < S; ++j) {
            if (r[i][j] != '.') {
                int sum = r[i][j]-'0';
                int IL = j, IR = j;
                r[i][j] = '.';
                myq.emplace(i, j);
                while (!myq.empty()) {
                    auto [ii, jj] = myq.front();
                    myq.pop();
                    static const vii mov = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                    for (auto [vi, vj] : mov) {
                        int iii = ii+vi, jjj = jj+vj;
                        if (iii >= 0 and iii < R and
                            jjj >= 0 and jjj < S and
                            r[iii][jjj] != '.') {
                            sum += r[iii][jjj]-'0';
                            r[iii][jjj] = '.';
                            myq.emplace(iii, jjj);
                            IL = min(IL, jjj);
                            IR = max(IR, jjj);
                        }
                    }
                }
                LE[IL].emplace_back(IR, sum);
                RE[IR].emplace_back(IL, sum);
                // cerr << IL << ", " << IR << " " << sum << endl;
            }
        }
    }

    calc_adp();
    for (int k = 0; k < S; ++k) {
        for (int i = 0; i < S; ++i) {
            olddp[i] = dp[i];
        }
        solve(0, S, 0, S);
        // for (int i = 0; i <= S; ++i) {
        //     cerr << dp[i] << ' ';
        // }
        // cerr << endl;
        cout << *max_element(dp, dp+S) << '\n';
    }
}
