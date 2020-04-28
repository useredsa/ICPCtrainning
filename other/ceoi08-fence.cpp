#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 102;

using T = double;
const T EPS = 1e-7;

struct point {
    T x, y;
    point() { x=y=0; }
    point(point a, point b) : x(b.x-a.x), y(b.y-a.y) {}
    bool operator == (const point &rhs) const {
        return ((fabs(x-rhs.x)<EPS) and (fabs(y-rhs.y) < EPS));
    }
};

ostream& operator<<(ostream&os, const point& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

T hypot(T dx, T dy) { return sqrt(dx*dx+dy*dy); }
T dist(point p, point q) { return hypot(p.x-q.x, p.y-q.y); }
T cross(point p, point q) { return p.x*q.y-p.y*q.x; }
bool ccw(point p, point q, point r) {
    return cross(point(p, q), point(p, r)) >= 0;
}

point pivot;
bool angleCmp(point p, point q) {
    if (ccw(pivot, p, q) == ccw(pivot, q, p))
        return dist(pivot, p) < dist(pivot, q);
    T d1x = p.x-pivot.x, d1y = p.y-pivot.y;
    T d2x = q.x-pivot.x, d2y = q.y-pivot.y;
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

vector<point> CH (vector<point> P) {
    int i, j, n = (int) P.size();
    if (n <= 3) {
        if (!(P[0] == P[n-1])) P.push_back(P[0]);
        return P;
    }

    int P0 = 0;
    for (i = 1; i < n; ++i) {
        if (P[i].y < P[P0].y or (P[i].y == P[P0].y and P[i].x > P[P0].x))
            P0 = i;
    }
    swap(P[P0], P[0]);

    pivot = P[0];
    sort(++P.begin(), P.end(), angleCmp);

    vector<point> S;
    S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]);
    i = 2;
    while (i < n) {
        j = (int) S.size()-1;
        if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);
        else S.pop_back();
    }
    return S;
}

vector<point> modifiedCH(vector<point> P) {
    int i, j, n = (int) P.size();
    if (n <= 3) {
        if (!(P[0] == P[n-1])) P.push_back(P[0]);
        return P;
    }

    int P0 = 0;
    for (i = 1; i < n; ++i) {
        if (P[i].y < P[P0].y or (P[i].y == P[P0].y and P[i].x > P[P0].x))
            P0 = i;
    }
    swap(P[P0], P[0]);

    pivot = P[0];
    sort(++P.begin(), P.end(), angleCmp);

    vector<point> S;
    S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]);
    i = 2;
    while (i < n) {
        j = (int) S.size()-1;
        if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);
        else S.pop_back();
    }
    return S;
}

int n, m;
bool in[MAXN];
vector<point> posts, ch, trees;

int d[MAXN][MAXN];

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    posts.resize(n);
    trees.resize(m);
    for (int i = 0; i < n; ++i) {
        cin >> posts[i].x >> posts[i].y;
    }
    for (int i = 0; i < m; ++i) {
        cin >> trees[i].x >> trees[i].y;
    }

    ch = CH(posts);
    int cost = 0, k = 0;
    for (int i = 0; i < m; ++i) {
        bool in = true;
        for (int j = 1; j < (int)ch.size(); ++j) {
            if (!ccw(ch[j-1], ch[j], trees[i])) {
                in = false;
                break;
            }
        }
        if (in) {
            trees[i-k] = trees[i];
        } else {
            cost += 111;
            k++;
        }
    }
    m -= k;
    if (m == 0) {
        cout << cost << "\n";
        return 0;
    }

    memset(d, 0x3F, sizeof d);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            bool edge = true;
            for (int k = 0; k < m; ++k) {
                if (!ccw(posts[i], posts[j], trees[k])) {
                    edge = false;
                    break;
                }
            }
            if (edge) {
                d[i][j] = 1;
            }
        }
    }

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
            }
        }
    }


    int mini = 200;
    for (int i = 0; i < n; ++i) {
        mini = min(mini, d[i][i]);
    }
    cout << cost+mini*20 << "\n";
}
