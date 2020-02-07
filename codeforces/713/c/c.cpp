#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 3002;


int n, m;
ll arr[MAXN], val[MAXN], dp[MAXN][MAXN];

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i]-=i;
        val[i] = arr[i];
        // cerr << arr[i] << " ";
    }
    val[n] = arr[n] = INF;
    // cerr << endl;

	sort(val, val+n+1);
	m = unique(val, val+n+1)-val-1;
	for (int i = 0; i < n; i++) {
    	dp[i][m] = 1e18;
	}
	// cerr << "\t";
	for (int i = 0; i <= m; i++) {
    	// cerr << val[m-i] << "\t";
    	dp[n][i] = 0;
	}
	// cerr << endl;
	for (int i = n-1; i >= 0; i--) {
    	// cerr << arr[i] << "\t";
    	for (int j = m-1; j >= 0; j--) {
        	dp[i][j] = min(abs(arr[i]-val[j])+dp[i+1][j], dp[i][j+1]);
        	// cerr << dp[i][j] << "\t";
    	}
    	// cerr << endl;
	}

    cout << dp[0][0] << endl;
  
}
