#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const int INF = 1e9+9;
const int MAXN = 100000008;
const int MAXP = 6000006;


ll MOD;
int n, t;
int primes[MAXP], nump;
bool isPrime[MAXN];


void precalc() {
    for (int i = 2; i < MAXN; i++) {
        if (isPrime[i] == false) {
            // if (nump < MAXP)
            if (i!=2)
	            primes[nump++] = i;
            for (int j = i; j < MAXN; j+=i) {
                isPrime[j] = true;
            }
        }
    }
    // cerr << nump << endl;
}

ll binPow(ll b, ll e) {
    ll r = 1;
    while (e > 0) {
        if (e&1) {
            r=r*b%MOD;
        }
        b=b*b%MOD;
        e>>=1;
    }
    return r;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    precalc();
    cin >> t;
    while (t--) {
        cin >> n >> MOD;
        if (n == 0) n = 1;
        ll ans = 1;

		int sqn = sqrt(n);
		// cerr << sqn << endl;
        for (int mul = 1; n/mul > sqn; mul++) {
            int cnt = upper_bound(primes, primes+nump, n/mul)-
                      upper_bound(primes, primes+nump, max(n/(mul+1), sqn));
            ans = ans*binPow(mul+1, cnt)%MOD;
        }
        for (int i = 0; primes[i]<=sqn; i++) {
            int sum = 1;
            for (int m = n; m > 0; m/=primes[i]) {
                sum+=m/primes[i];
            }
            if (primes[i] > n) break;
            ans=ans*sum%MOD;
        }
        cout << (ans+MOD-1)%MOD << endl;
    }
}

