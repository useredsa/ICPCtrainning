#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 50004;


enum direction{right = 0, up = 1, left = 2, down = 3};
int n, m, a[MAXN], b[MAXN];

int sparseA[MAXN][20], sparseB[MAXN][20];
void sparseTable() {
    for (int i = 0; i < n; i++) {
        sparseA[i][0] = i;
    }
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i+(1<<j) <= n; i++) {
            int &l = sparseA[i][j-1], &r = sparseA[i+(1<<(j-1))][j-1];
            sparseA[i][j] = a[l] > a[r]? l : r;
        }
    }
    for (int i = 0; i < m; i++) {
        sparseB[i][0] = i;
    }
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i+(1<<j) <= m; i++) {
            int &l = sparseB[i][j-1], &r = sparseB[i+(1<<(j-1))][j-1];
            sparseB[i][j] = b[l] > b[r]? l : r;
        }
    }
}

inline int maxa(int l, int r) {
    int logLen = 0;
    for (int i = r-l; i > 1; i>>=1) logLen++;
    int &L = sparseA[l][logLen], &R = sparseA[r-(1<<logLen)][logLen];
    return a[L] > a[R]? L : R;
}

inline int maxb(int l, int r) {
    int logLen = 0;
    for (int i = r-l; i > 1; i>>=1) logLen++;
    int &L = sparseB[l][logLen], &R = sparseB[r-(1<<logLen)][logLen];
    return b[L] > b[R]? L : R;
}

ll mid[4], midVal[4];
inline ll dist(direction dir, int id) {
    return midVal[dir] == -1? 0 : abs(2*id-mid[dir])/2+midVal[dir];
}

ll solve(int s, int t, direction dir) {
    if (s == -1 || s == n || t == -1 || t == m)
        return 0;
    
    using direction::right;
    using direction::left;
    int l = 0, r = m, d = 0, u = n;
    mid[0] = mid[1] = mid[2] = mid[3] = 0;
    midVal[0] = midVal[1] = midVal[2] = midVal[3] = -1;
    while (true) {
        // cerr << "it [" << d << ", " << u << "]x[" << l << ", " << r << "]" << endl;
        // for (int i = 0; i < 4; i++) {
        //    cerr << mid[i] << " " << midVal[i] << endl;
        // }
        int maxh = maxa(d, u);
        int maxv = maxb(l, r);

        if (b[maxv] > a[maxh]) {
            ll downVal = dist(down, maxv);
            ll upVal   = dist(up, maxv);
            // cerr << "downVal " << downVal << " upVal " << upVal << endl;
            if (maxv <= t) {
                l = maxv+1;
                mid[left] = d-downVal+u-1+upVal;
                midVal[left] = (-d+downVal+u+upVal+2)/2;
            } else {
                r = maxv;
                mid[right] = d-downVal+u-1+upVal;
                midVal[right] = (-d+downVal+u+upVal+2)/2;
            }

            if (maxv == t) {
                if (dir == down) {
                    return upVal+u-s;
                } else if (dir == up) {
                    return downVal+s-d+1;
                } else {
                    assert(max(upVal+u-s, downVal+s-d+1) == dist(left, s));
                    return dist(left, s);
                }
            }
        } else {
            ll leftVal = dist(left, maxh);
            ll rightVal = dist(right, maxh);
            // cerr << "leftVal " << leftVal << " rightVal " << rightVal << endl;
            if (maxh <= s) {
                d = maxh+1;
                mid[down] = l-leftVal+r-1+rightVal;
                midVal[down] = (-l+leftVal+r+rightVal+2)/2;
            } else {
                u = maxh;
                mid[up] = l-leftVal+r-1+rightVal;
                midVal[up] = (-l+leftVal+r+rightVal+2)/2;
            }
            if (maxh == s) {
                if (dir == left) {
                    return rightVal+r-t;
                } else if (dir == right) {
                    return leftVal+t-l+1;
                } else {
                    assert(max(rightVal+r-t, leftVal+t-l+1) == dist(down, t));
                    return dist(down, t);
                }
            }
        }
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q, s, t;
    ll ans;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sparseTable();

    while (q--) {
        cin >> s >> t;
        s--, t--;
        using direction::right;
        using direction::left;
        if (a[s] < b[t]) {
            ans = max(solve(s, t-1, right), solve(s, t+1, left));
            ans = max(solve(s, t, right)-1, ans);
        } else {
            ans = max(solve(s-1, t, up), solve(s+1, t, down));
            ans = max(solve(s, t, up)-1, ans);
        }
        cout << ans << '\n';
        // break;
    }
}

