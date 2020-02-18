#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 1e9 + 7;
const int INF = 1e9+9;
const int MAXN = 20;


int n;
ll dp[2][1 << MAXN];

ll binPow(ll b, int e) {
	ll r = 1;
	while (e > 0) {
		if (e&1) r = r*b%MOD;
		b = b*b%MOD;
		e>>=1;
	}
	return r;
}

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
	for (int i = 0, x; i < n; i++) {
		cin >> x;
		dp[0][x]++;
	}
	for (int j = 0; j < MAXN; j++) {
		for (int i = 0; i < (1<<MAXN); i++) {
			dp[1][i] = i&(1<<j)? dp[0][i] : (dp[0][i]+dp[0][i+(1<<j)])%MOD;
		}
		for (int i = 0; i < (1<<MAXN); i++) {
			dp[0][i] = dp[1][i];
		}
	}
	ll ans = 0;
	for (int i = 0; i < (1<<MAXN); i++) {
		ll p = binPow(2, dp[0][i]);
		ans = (ans+(__builtin_popcount(i)&1? -p+MOD : p))%MOD;
	}
	cout << ans << endl;
}
