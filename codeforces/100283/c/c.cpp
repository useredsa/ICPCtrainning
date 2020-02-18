#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 1e9+7;
const int INF = 1e9+7;
const int MAXN = 102;


int t, n, m, s, pi, pj;
ll dp[3*MAXN][3*MAXN];
ll sdp[3*MAXN][3*MAXN];

inline ll sum(int i, int j, int d) {
	ll r = sdp[i+d][j]+sdp[i+d-1][j];
	r -= sdp[i][j+d]+sdp[i][j+d-1];
	r -= sdp[i][j-d]+sdp[i][j-d+1];
	r += sdp[i-d][j]+sdp[i-d+1][j];
	return (r+4*MOD)%MOD;
}

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
	#ifdef ONLINE_JUDGE
	freopen("treasures.in", "r", stdin);
	#endif
	cin >> t;
	for (int numcase = 1; numcase <= t; numcase++) {
		cin >> n >> m >> s >> pi >> pj;
		pi--, pj--;
		memset(dp, 0, sizeof dp);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> dp[MAXN+i][MAXN+j];
			}
		}

		for (int time = 2; time <= s; time++) {
			memset(sdp, 0, sizeof sdp);
			for (int i = 0; i < 3*MAXN-1; i++) {
				for (int j = 0; j < 3*MAXN-1; j++) {
					sdp[i+1][j] = sdp[i][j+1]+dp[i][j];
					if (j) sdp[i+1][j] += sdp[i][j-1];
					if (i && j) sdp[i+1][j] -= sdp[i-1][j];
					sdp[i+1][j] = (sdp[i+1][j]+MOD)%MOD;
				}
			}

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					dp[MAXN+i][MAXN+j] = sum(MAXN+i, MAXN+j, time);
				}
			}
		}

		cout << "Case " << numcase << ": " << dp[MAXN+pi][MAXN+pj] << endl;
	}
}
