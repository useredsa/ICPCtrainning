#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 3000001;


int n, m;
int arr[MAXN];
ll cs[MAXN+1], ans[MAXN+1];

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    arr[x]++;
  }
  for (int i = MAXN-1; i >= 0; i--) {
    cs[i] = cs[i+1]+arr[i];
  }
  for (ll i = 1; i < MAXN; i++) {
    ans[min(i*i, (ll) MAXN)]+=(ll)arr[i]*(arr[i]-1);
    ll j;
    for (j = i+1; i*j < MAXN; j++) {
      ans[i*j]+=2*arr[i]*arr[j];
    }
    ans[MAXN]+=2*arr[i]*cs[j];
  }
  for (int i = MAXN-1; i >= 0; i--) {
    ans[i]+=ans[i+1];
  }

  cin >> m;
  for (int i = 0, x; i < m; i++) {
    cin >> x;
    cout << ans[x] << '\n';
  }
}
