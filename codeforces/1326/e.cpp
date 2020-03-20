#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 1000006;

template <class T, class Operations>
struct LazySegmentTree {
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

    /**
     * @brief Recalculate the values of all parents of node p, taking into
     * account delayed operations.
     */
    void build(int p) {
        // Find value from children, apply every delayed operation you have for
        // this node
        int len = 2;
        for (p+=n; p > 1; len <<= 1) p >>= 1, op.calc(p, len);
    }

    void push(int L, int R) {
        int s = h, len = 1 << h;
        for (L += n, R += n - 1; s > 0; --s, len >>= 1)
            for (int i = L >> s; i <= R >> s; ++i) op.pushDelOps(i, len);
    }

    /**
     * @brief Propagate changes from all parents of node p
     */
    void push(int p) {
        for (int s = h, len = 1 << h; s > 0; --s, len >>= 1)
            op.pushDelOps(p >> s, len);
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
        /*for (int i = 1; i < 2 * n; i++) {
            cout << i << ":  " << st[i] << " ";
            if (i < n) cout << op.d[i];
            cout << endl;
        }*/
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
    LazySegmentTree(const vector<T> &A)
        : n((int)A.size()),
          h(sizeof(int) * 8 - __builtin_clz(n)),
          st(n << 1),
          op(*this) {
        copy(A.begin(), A.end(), st.begin() + n);
        build(0, n);
    }
};

template <class T>
struct SumForMinMax {
    const T identity = -1e16;  // Change for Min
    LazySegmentTree<T, SumForMinMax> &st;
    vector<T> d;

    SumForMinMax(LazySegmentTree<T, SumForMinMax> &st) : st(st), d(st.n) {}

    /**
     * @brief Operation of the tree. In this case, maximum.
     */
    inline T op(T a, T b) { return max(a, b); }

    /**
     * @brief Calculate value for node p
     */
    inline void calc(int p, int len) {
        st.st[p] = max(st.st[p << 1], st.st[p << 1 | 1]) + d[p];
    }

    /**
     * @brief Update interval of node p
     */
    using UpdateObject = T;
    inline void updateOp(int p, int len, UpdateObject value) {
        st.st[p] += value;
        if (p < st.n) d[p] += value;
    }

    /**
     * @brief Push delayed operations of node p (p < n)
     */
    inline void pushDelOps(int p, int len) {
        updateOp(p << 1, len >> 1, d[p]);
        updateOp(p << 1 | 1, len >> 1, d[p]);
        d[p] = 0;
    }
};



int n, p[MAXN], rev[MAXN], q[MAXN];

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
        rev[p[i]] = i;
    }
    for (int i = 0; i < n; ++i) {
        cin >> q[i];
        --q[i];
    }

    LazySegmentTree<ll, SumForMinMax<ll>> st(vll(n, 0));

    int ans = n;
    for (int i = 0; i < n; ++i) {
        while (st.query(0, n) <= 0) {
            st.update(0, rev[--ans]+1, 1);
        }
        st.update(0, q[i]+1, -1);
        cout << ans+1 << ' ';
    }
    cout << endl;
}

