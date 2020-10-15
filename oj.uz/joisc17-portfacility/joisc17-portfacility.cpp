#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 1e9+7;
const int INF = 1e9+9;
const int MAXN = 1000006;


template <class T, class Operations>
struct LzySegTree {
    int n, h;       // Size and height of the array
    vector<T> st;   // Segment tree (size 2n)
    Operations op;  // Update operation object

    void build(int L, int R) {
        int len = 2;
        for (L += n, R += n - 1; L > 1; len <<= 1) {
            L >>= 1, R >>= 1;
            for (int i = R; i >= L; --i) op.calc(i, len);
        }
    }

    void push(int L, int R) {
        int s = h, len = 1 << h;
        for (L += n, R += n - 1; s > 0; --s, len >>= 1)
            for (int i = L >> s; i <= R >> s; ++i) op.pushDelOps(i, len);
    }

    /**
     * @brief Perform update operation on the interval [L, R)
     * @param value
     */
    void update(int L, int R, typename Operations::UpdateObject value) {
        if (L < n) push(L, L + 1);
        if (R > 0) push(R - 1, R);
        int L0 = L, R0 = R, len = 1;
        for (L += n, R += n; L < R; L >>= 1, R >>= 1, len <<= 1) {
            if (L & 1) op.updateOp(L++, len, value);
            if (R & 1) op.updateOp(--R, len, value);
        }
        build(L0, L0 + 1), build(R0 - 1, R0);
    }

    /**
     * @brief Query on the interval [L, R)
     */
    T query(int L, int R) {
        if (L < n) push(L, L + 1);
        if (R > 0) push(R - 1, R);
        T resl = op.identity, resr = op.identity;
        for (L += n, R += n; L < R; L >>= 1, R >>= 1) {
            if (L & 1) resl = op.op(resl, st[L++]);
            if (R & 1) resr = op.op(st[--R], resr);
        }
        return op.op(resl, resr);
    }

    /**
     * @brief Construct a new Segment Tree object.
     *
     * @param A Array of elements
     */
    LzySegTree(const vector<T> &A)
        : n((int)A.size()),
          h(sizeof(int) * 8 - __builtin_clz(n)),
          st(n << 1),
          op(*this) {
        copy(A.begin(), A.end(), st.begin() + n);
        build(0, n);
    }
};

template<typename T>
struct SetForMinMax {
    const T identity = -INF;
    using UpdateObject = T;
    LzySegTree<int, SetForMinMax> &st; vector<int> d;

    SetForMinMax(LzySegTree<int, SetForMinMax> &st) : st(st), d(st.n, INF) {}

    static inline int op(int a, int b) {
        return max(a, b);
    }

    inline void calc(int p, int len) {
        st.st[p] = d[p] == INF? max(st.st[p<<1], st.st[p<<1|1]) : d[p];
    }

    inline void updateOp(int p, int len, int value) {
        st.st[p] = value;
        if (p < st.n) d[p] = value;
    }

    inline void pushDelOps(int p, int len) {
        if (d[p] != INF) {
            updateOp(p<<1, len>>1, d[p]);
            updateOp(p<<1|1, len>>1, d[p]);
            d[p] = INF;
        }
    }
};

using ST = LzySegTree<int, SetForMinMax<int>>;
int n, a[MAXN], b[MAXN], e[MAXN], ind[MAXN], col[MAXN];

void dfs(ST& segl, ST& segr, int u, int c) {
    segl.update(b[u], b[u]+1, -INF);
    segr.update(a[u], a[u]+1, -INF);
    col[u] = c;
    int l, r;
    while (r = segr.query(a[u]+1, b[u]), r != -INF and r > b[u]) {
        dfs(segl, segr, ind[r], 3-c);
    }
    while (l = -segl.query(a[u]+1, b[u]), l != INF and l < a[u]) {
        dfs(segl, segr, ind[l], 3-c);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    ST segl(vi(2*n, -INF));
    ST segr(vi(2*n, -INF));
    for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i]; --a[i], --b[i];
        ind[b[i]] = ind[a[i]] = i;
        segl.update(b[i], b[i]+1, -a[i]);
        segr.update(a[i], a[i]+1, b[i]);
    }
    ll ans = 1;
    for (int i = 1; i <= n; ++i) {
        if (!col[i]) {
            ans *= 2;
            if (ans >= MOD) ans -= MOD;
            dfs(segl, segr, i, 1);
        }
    }

    vi st[2];
    for (int i = 0; i < 2*n; ++i) {
        int v = ind[i], c = col[v]-1;
        if (i == a[v]) {
            st[c].push_back(v);
        } else {
            if (!st[c].empty() and st[c].back() == v) {
                st[c].pop_back();
            } else {
                ans = 0;
            }
        }
    }
    cout << ans << endl;
}
