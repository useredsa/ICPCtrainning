#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
const int INF = 1e9+7;
const ll MOD = 1e9+7;
const int MAXN = 1000006;

int t, x, p, k;
int spf[MAXN];
vi primes;

int phiP;
vi fac;

void sieve() {
    for (int i = 2; i < MAXN; ++i) {
        if (!spf[i]) {
            for (int j = i; j < MAXN; j+=i) {
                if (!spf[j])
                    spf[j] = i;
            }
        }
    }
}

int bef(int num) {
    int num1 = num/p, num2 = num%p;
    int befNum = num1*phiP;
    int numFac = fac.size();
    for (int msk = 1; msk < (1 << numFac); ++msk) {
        int prod = 1;
        int sum = -1;
        for (int i = 0; i < numFac; i++) {
            if (msk & (1 << i)) {
                prod *= fac[i];
                sum = -sum;
            }
        }
        befNum += sum * (num2 - num2 / prod);
    }
    return befNum;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    sieve();
    cin >> t;
    while (t--) {
        cin >> x >> p >> k;
        int newP = 1;
        phiP = 1;
        fac.clear();
        while (p > 1) {
            int d = spf[p];
            fac.push_back(d);
            newP*=d;
            phiP*=d-1;
            while (p%d==0) p/=d;
        }
        p = newP;

        
        
        // cerr << bef(x) << endl;

        k = bef(x)+k;

        int lo = 1, hi = 1e8;
        while (lo+1 < hi) {
            int med = (lo+hi)/2;
            if (bef(med) < k) lo = med;
            else hi = med;
        }
        cout << hi << endl;
    }

}

