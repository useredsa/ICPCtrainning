#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 100005;

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
        for (int len = 2; p > 1; len >>= 1) p >>= 1, op.calc(p, len);
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
        for (int s = h, len = 1 << (h - 1); s > 0; --s, len >>= 1)
            op.pushDelOps(p >> s, len);
    }

    /**
     * @brief Perform update operation on the interval [L, R)
     * @param value
     */
    void update(int L, int R, typename Operations::UpdateObject value) {
        if (L < n) push(L, L + 1);
				push(R - 1, R);
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
        push(L, L + 1), push(R - 1, R);
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
		template <class iterator>
    LazySegmentTree(iterator l, iterator r)
        : n((int)distance(l, r)),
          h(sizeof(int) * 8 - __builtin_clz(n)),
          st(n << 1),
          op(*this) {
        copy(l, r, st.begin() + n);
        build(0, n);
    }
};

template <class T>
struct SumForMinMax {
    const T identity = -INF;  // Change for Min
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
				if (p >= st.n) {
					cerr << "fuck " << p << endl;
					// exit(-1);
				}

        updateOp(p << 1, len >> 1, d[p]);
        updateOp(p << 1 | 1, len >> 1, d[p]);
        d[p] = 0;
    }
};





int n, m, k;
int arr[55][MAXN], sarr[55][MAXN];

int dp[MAXN];

int main () {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> arr[i][j];
			sarr[i][j+1] = arr[i][j]+sarr[i][j];
		}
	}

	LazySegmentTree<int, SumForMinMax<int>> st(arr[0], arr[0]+m-k+1);
	for (int i = 0; i <= n; i++) {
		st.push(0, st.n);
		for (int j = 0; j+k <= m; j++) {
			st.st[st.n+j] = dp[j];
			if (i > 0 && j < k && j <= st.n) {
				st.st[st.n+j] -= sarr[i][k]-sarr[i][j];
			}
		}
		st.build(0, st.n);

		for (int j = 0; j+k <= m; j++) {
			dp[j] = st.query(0, st.n) + sarr[i][j+k]-sarr[i][j]+sarr[i+1][j+k]-sarr[i+1][j];
			if (i > 0) {
				st.update(j+1, min(j+k+1, st.n), -arr[i][j+k]);
				st.update(max(j-k+1, 0), j+1, arr[i][j]);
			}
		}
	}
	cout << dp[0] << endl;
  
}
