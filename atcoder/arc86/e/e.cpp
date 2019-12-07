#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 1e9+7;
const int INF = 1e9+9;
const int MAXN = 200005;


int n, p[MAXN];
vi children[MAXN];
ll siz[MAXN], good[MAXN], bad[MAXN], sum[MAXN], prod[MAXN], in[MAXN], h[MAXN];

inline ll binPow(ll base, ll e) {
  ll r = 1;
  while (e>0) {
    if (e&1) {
      r=r*base%MOD;
    }
    base=base*base%MOD;
    e>>=1;
  }
  return r;
}

inline ll inverse(ll n) {return binPow(n, MOD-2);}

struct cmp {
  inline bool operator()(int u, int v) {
    return h[u] < h[v];
  }
};


int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
    h[i] = h[p[i]]+1;
    children[p[i]].push_back(i);
  }

  vi level(1, 0), nextLevel;
  priority_queue<int, vi, cmp> myq;
  ll ans = 0;

  while (!level.empty()) {
    for (int u : level) {
      myq.push(p[u]);
      if (in[p[u]] == 0) {
        in[p[u]] = 1;
        myq.push(p[u]);
      }
    }
    while(!myq.empty()) {
      int u = myq.top();
      myq.pop();
      in[u] = 0;
      siz[u] = prod[u] = 1;
      sum[u] = 0;
      if (u && in[p[u]] == 0) {
        in[p[u]] = 1;
        myq.push(p[u]);
      }
    }
    for (int u : level) {
      sum[u] = prod[u] = 1;
      siz[u] = 2;
      in[u] = 1;
      myq.push(u);
    }
    while (!myq.empty()) {
      int u = myq.top();
      myq.pop();
      in[u] = 0;
      good[u] = sum[u]*prod[u]%MOD;
      bad[u] = (siz[u]-good[u]+MOD)%MOD;
      assert((good[u]+bad[u])%MOD==siz[u]);
      //cerr << u << "->  " << p[u] << " " << good[u] << " " << bad[u] << endl;
      if (u == 0) break;
      sum[p[u]] = (sum[p[u]]+good[u]*inverse(bad[u])%MOD)%MOD;
      prod[p[u]] = prod[p[u]]*bad[u]%MOD;
      siz[p[u]] = siz[p[u]]*siz[u]%MOD;
      if (in[p[u]] == 0) {
        in[p[u]] = 1;
        myq.push(p[u]);
      }
    }
    ans = (ans+good[0]*binPow(2, n+1-level.size())%MOD)%MOD;
    //cerr << "ans: " << good[0] << ' ' << n+1-level.size() << ' ' << ans << endl;

    nextLevel.clear();
    for (int u : level) {
      while (p[u] && siz[p[u]]==2) p[u] = p[p[u]];
      for (int v : children[u]) {
        nextLevel.push_back(v);
      }
    }
    swap(level, nextLevel);
  }

  
  cout << ans << endl;
}
