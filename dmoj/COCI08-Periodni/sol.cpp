#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 1000000007;
const int INF = 1e9+9;
const int MAXN = 502;




const int MAXT = 1000006;
ll fac[MAXT], ifac[MAXT];
ll nck(int n, int k) {
	return fac[n]*ifac[n-k]%MOD*ifac[k]%MOD;
}

ll binPow(ll b, int e) {
	ll r = 1;
	while (e > 0) {
		if (e&1) {
			r = r*b%MOD;
		}
		b = b*b%MOD;
		e >>= 1;
	}
	return r;
}

inline ll inv(ll n) { return binPow(n, MOD-2); }









int n, k, arr[MAXN];

int l[MAXN], r[MAXN], size[MAXN], lc[MAXN], rc[MAXN];
ll aux[MAXN], dp[MAXN][MAXN];

void solve(int p) {
	if (p == n) return;
	solve(lc[p]);
	solve(rc[p]);

	for (int i = 0; i <= k; i++) {
		aux[i] = 0;
	}
	for (int i = 0; i <= k; i++) {
		for (int j = 0; j <= k-i; j++) {
			aux[i+j] = (aux[i+j]+dp[lc[p]][i]*dp[rc[p]][j]%MOD)%MOD;
		}
	}
	for (int i = 0; i <= r[p]-l[p]; i++) {
		for (int j = 0; i+j <= r[p]-l[p] and j <= size[p] and j <= k-i; j++) {
			dp[p][i+j] = (dp[p][i+j]+aux[i]*nck(size[p], j)%MOD*nck(r[p]-l[p]-i, j)%MOD*fac[j]%MOD)%MOD;
		}
	}
	// cerr << p << endl;
	// for (int i = 0; i <= k; i++) {
	// 	cerr << aux[i] << ' ' << dp[p][i] << endl;
	// }
	// cerr << endl;
}


int numNodes = 0;
int build_graph(int L, int R, int offset = 0) {
	int i = min_element(arr+L, arr+R)-arr;
	int p = numNodes++;
	size[p] = arr[i]-offset;
	l[p] = L, r[p] = R;
	lc[p] = i > L? build_graph(L, i, arr[i]) : n;
	rc[p] = i+1 < R? build_graph(i+1, R, arr[i]) : n;
	return p;
}

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	fac[0] = 1;
	for (int i = 1; i < MAXT; i++) {
		fac[i] = i*fac[i-1]%MOD;
	}
	ifac[MAXT-1] = inv(fac[MAXT-1]);
	for (int i = MAXT-2; i >= 0; i--) {
		ifac[i] = (i+1)*ifac[i+1]%MOD;
	}
  build_graph(0, n);
	
	dp[n][0] = 1;
	// ITERATIVE
	for (int p = numNodes-1; p >= 0; p--) {

		// cerr << p << ' ' << l[p] << ' ' << r[p] << endl;
		for (int i = 0; i <= r[p]-l[p]; i++) {
			aux[i] = 0;
			for (int j = 0; j <= i; j++) {
				aux[i] = (aux[i]+dp[lc[p]][j]*dp[rc[p]][i-j]%MOD)%MOD;
			}
		}

		for (int i = 0; i <= r[p]-l[p]; i++) {
			dp[p][i] = 0;
			for (int j = 0; j <= i and j <= size[p]; j++) {
				dp[p][i] = (dp[p][i] +
					aux[i-j]*nck(size[p], j)%MOD*fac[r[p]-l[p]-i+j]%MOD*ifac[r[p]-l[p]-i]%MOD)%MOD;
			}
			// cerr << aux[i] << " " << dp[p][i] << endl;
		}
	}
	// solve(0);

	cout << dp[0][k] << endl;
}
