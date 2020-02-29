#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
using li = pair<ll, int>;
using vi = vector<int>;
using vli = vector<li>;
using vii = vector<ii>;
const ll INF = 1e14 + 7;
const ll MOD = 1e9 + 7;
const int MAXN = 2003;

using il = pair<ll, ll>;
using vil = vector<il>;
int n, m, used[MAXN], aux[MAXN];
ll d[MAXN][MAXN];
vil gr[MAXN];

void dijsktra() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      d[i][j] = INF;
    }
  }

  using ili = pair<il, int>;
  priority_queue<ili, vector<ili>, greater<ili>> myq;
  d[0][0] = 0;
  myq.emplace(il(0, 0), 0);
  while (!myq.empty()) {
    int u = myq.top().second;
    int k = myq.top().first.first;
    ll dist = myq.top().first.second;
    myq.pop();
    if (d[k][u] < dist) continue;
		if (k == n) continue;
    for (const auto& pp : gr[u]) {
      int v = pp.first;
      int w = pp.second;
      if (d[k + 1][v] > d[k][u] + w) {
				d[k+1][v] = d[k][u]+w;
        myq.emplace(il(k + 1, d[k][u] + w), v);
      }
    }
  }
}

void update_used(int k) {
  for (int i = 0; i < n; ++i) {
    aux[i] = false;
  }
  queue<ii> myq;
  myq.emplace(n - 1, k);
  aux[n - 1] = true;
  while (!myq.empty()) {
    int u = myq.front().first;
    int ku = myq.front().second;
    myq.pop();
		if (ku == 0) continue;
    for (const auto& pp : gr[u]) {
      int v = pp.first;
      int w = pp.second;
      if (!aux[v] && d[ku - 1][v] + w == d[ku][u]) {
        aux[v] = true;
        myq.emplace(v, ku - 1);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    used[i] |= aux[i];
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0, u, v, w; i < m; ++i) {
    cin >> u >> v >> w;
    u--, v--;
    gr[u].emplace_back(v, w);
    gr[v].emplace_back(u, w);
  }

  dijsktra();
  for (int i = 0; i < n; ++i) {
    if (d[i][n - 1] == INF) continue;
    ll n1 = -INF, d1 = 1;
    for (int j = 0; j < i; ++j) {
      if (d[j][n - 1] != INF &&
          (d[i][n - 1] - d[j][n - 1]) * d1 > n1 * (i - j)) {
        n1 = d[i][n - 1] - d[j][n - 1];
        d1 = i - j;
      }
    }
    ll n2 = INF, d2 = 1;
    for (int j = i + 1; j < n; ++j) {
      if ((d[j][n - 1] - d[i][n - 1]) * d2 < n2 * (j - i)) {
        n2 = d[j][n - 1] - d[i][n - 1];
        d2 = j - i;
      }
    }
    

    if (n1 * d1 <= 0 and n1 * d2 <= n2 * d1) {
      update_used(i);
    }
  }



  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (not used[i]) {
      ans++;
    }
  }
  cout << ans << endl;
  for (int i = 0; i < n; ++i) {
    if (not used[i]) {
      cout << i + 1 << ' ';
    }
  }
  cout << "a" << endl;
  if (ans) cout << endl;
}
