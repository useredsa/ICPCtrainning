#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 500005;


int n, q, p, x, arr[MAXN], in[MAXN];
ll ans;
int spf[MAXN];

map<int, int> divNum;
vi primes;

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  spf[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    if (!spf[i]) {
      for (int j = i; j < MAXN; j+=i) {
        if (!spf[j])
          spf[j] = i;
      }
    }
  }

  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }
  while (q--) {
    cin >> p;
    x = arr[--p];
    primes.clear();
    while (x > 1) {
      int d = spf[x];
      primes.push_back(d);
      while (x%d==0) x/=d;
    }

    int m = primes.size();
    for (int pat = 0; pat < (1<<m); pat++) {
      int mul = 1, pop = 0;
      for (int i = 0; i < m; i++) {
        if (pat&(1<<i)) {
          mul*=primes[i];
          pop++;
        }
      }

      auto &ref = divNum[mul];
      if (in[p])
        ref--;
      if ((in[p]+pop)%2) {
        ans-=ref;
      } else {
        ans+=ref;
      }
      if (!in[p])
        ref++;
    }
    in[p] = 1-in[p];
    cout << ans << '\n';
  }
}
