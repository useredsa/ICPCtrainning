/**
 * O(QN+NlogN) (assuming N>=M)
 * 
 * We want to calculate the maximum ammount of movements to get out of grid if we are at
 * position (s, t) and came from a given direction. If we can do that, we can solve the
 * problem by choosing the best option out of the 4 possible movements (you can reduce it
 * to 3 if you see that you can say you started in the cell and then you could go in two
 * directions).
 * 
 * Ok, so now, we will solve: maximum ammount of movements to get out from (s, t) when coming
 * from direction dir (left, right, down or up).
 * 
 * Start with the whole square.
 * Take the avenue with the greatest value in the current square.
 * If (s, t) lies in that avenue, then you can find the answer easily.
 * If (s, t) is not in the avenue, you could find the answer for all of the values on this
 * avenue and reduce the problem to a smaller square.
 * 
 * However, that'd take too long. Fortunately, it's not necessary. Notice that the values
 * along the edge of your square are something like this:  (9 8 7 7 8) or (5 4 3 4 5), you
 * just need to calculate the middle point and the value at that point to know the values of
 * the whole side. And that's basically what I do. To do it:
 * If for example the highest valued is a vertical street to the left of our point, take the
 * values of the two intersection points with the upper part and lower part of your square
 * (the corners if you substitute the left side by this side). With this values you can figure
 * out the values of this side (in particular, the middle value and where it is).
 * For more info: look at the code.
 */
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

struct SparseTable {
    int *arr;
    int sp[MAXN][20];

    void build(int *arr, int n) {
        this->arr = arr;
        for (int i = 0; i < n; i++) {
            sp[i][0] = i;
        }
        for (int j = 1; j < 20; j++) {
            for (int i = 0; i+(1<<j) <= n; i++) {
                int &l = sp[i][j-1], &r = sp[i+(1<<(j-1))][j-1];
                sp[i][j] = arr[l] > arr[r]? l : r;
            }
        }
    }

    int max(int l, int r) {
        int logLen = 0;
        for (int i = r-l; i > 1; i>>=1) logLen++;
        int &L = sp[l][logLen], &R = sp[r-(1<<logLen)][logLen];
        return arr[L] > arr[R]? L : R;
    }
} sparseA, sparseB;

ll mid[4], midVal[4];
inline ll dist(direction dir, int id) {
    return midVal[dir] == -1? 0 : abs(2*id-mid[dir])/2+midVal[dir];
}

ll solve(int s, int t, direction dir) {
    using direction::left;
    using direction::right;
    if (s == -1 || s == n || t == -1 || t == m)
        return 0;

    for (int i = 0; i < 4; i++) {
        mid[i] = 0;
        midVal[i] = -1;
    }
    int l = 0, r = m, d = 0, u = n;

    while (true) { // d < u and l < r
        // cerr << "it [" << d << ", " << u << "]x[" << l << ", " << r << "]" << endl;
        // for (int i = 0; i < 4; i++) {
        //    cerr << mid[i] << " " << midVal[i] << endl;
        // }
        int maxh = sparseA.max(d, u);
        int maxv = sparseB.max(l, r);

        if (b[maxv] > a[maxh]) {
            ll downVal = dist(down, maxv);
            ll upVal   = dist(up, maxv);
            // cerr << "downVal " << downVal << " upVal " << upVal << endl;
            if (maxv < t) {
                l = maxv+1;
                mid[left] = d-downVal+u-1+upVal;
                midVal[left] = (-d+downVal+u+upVal+2)/2;
            } else if (maxv > t) {
                r = maxv;
                mid[right] = d-downVal+u-1+upVal;
                midVal[right] = (-d+downVal+u+upVal+2)/2;
            } else {
                if (dir == down) {
                    return upVal+u-s;
                } else if (dir == up) {
                    return downVal+s-d+1;
                } else {
                    return max(upVal+u-s, downVal+s-d+1);
                }
            }
        } else {
            ll leftVal = dist(left, maxh);
            ll rightVal = dist(right, maxh);
            // cerr << "leftVal " << leftVal << " rightVal " << rightVal << endl;
            if (maxh < s) {
                d = maxh+1;
                mid[down] = l-leftVal+r-1+rightVal;
                midVal[down] = (-l+leftVal+r+rightVal+2)/2;
            } else if (maxh > s) {
                u = maxh;
                mid[up] = l-leftVal+r-1+rightVal;
                midVal[up] = (-l+leftVal+r+rightVal+2)/2;
            } else {
                if (dir == left) {
                    return rightVal+r-t;
                } else if (dir == right) {
                    return leftVal+t-l+1;
                } else {
                    return max(rightVal+r-t, leftVal+t-l+1);
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
    sparseA.build(a, n), sparseB.build(b, m);

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
    }
}

