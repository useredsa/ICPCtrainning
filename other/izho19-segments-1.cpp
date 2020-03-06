/**
 * Let a[i], 0 <= i < n, be the sequence of elements.
 * Let s[i], 0 <= i <= n, be the sequence of partial sums (s[i] = sum a[j] for 0 <= j < i).
 * 
 * The condition that a segment must be greater than the previous one can be rewritten as:
 * Given the two consecutive segments [i, j) and [j, k), 0 <= i < j < k <= n, it must follow
 * that
 * 
 * s[j]-s[i] <= s[k]-s[j]  <=> s[j] <= (s[i]+s[k])/2. (Convexity on the chosen subseq of s)
 * 
 * Let f(i, ans) be the smallest sum of the last segment when dividing into ans segments,
 * restricting the problem to the interval [0, i). One can prove that f is decreasing in the
 * second coordinate. That is, f(i, ans+1) <= f(i, ans) (given that ans and ans+1 are
 * possible answers). Because we want to maximize the answer, it is enough to keep for each i
 * the greatest achivable ans and the smallest sum for that value to use it in a dynamic
 * programming algorithm to create following answers. Why? Because you need the sum of the
 * last segment to be smaller than something, and after that, the answer to be as high as
 * possible. Because the sum is smaller as the answer grows, just keep the last value which
 * is always the best.
 * 
 * Therefore, we will store for each interval [0, i) two values.
 * ans[i] is the biggest number of segments in which it can be divided.
 * last[i] is the index where the last segment starts (the segment [j, i)).
 * We want to maximize the pair (ans[i], last[i]) with lexicographical comparation.
 * That is, maximize ans[i] and between all possible assignments, the one with greatest last.
 * 
 * How to do the dynamic programming?
 * If current position is i, maximize
 * 
 * (ans[i], last[i]) = (ans[j]+1, j) for j verifying s[i]-s[j] >= s[j] - s[last[j]]
 * 
 * The last inequality can be rewritten as s[i] >= 2s[j] - s[last[j]], leaving i alone in
 * one side. This means that we can use any type of binary search tree indexed by the values
 * s[j] - s[last[j]] to find the biggest (ans[j]+1, j) for values <= s[i].
 * After finding (ans[i], last[i]), you insert the pair (2s[i]-s[last[i]], (ans[i], i)) in
 * the tree and follow on with the next index. The solution is ans[n];
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vll = vector<ll>;
using vii = vector<ii>;
const ll MOD = 998244353;
const int INF = 1e9+9;
const int MAXN = 1000006;

// This is a treap for searching max val of nodes with key < threshold
struct item {
    ll key;
    int prior;
    ii val, max;
    item * l, * r;
    item() { }
    item (ll key, int prior, ii val) : key(key),
      prior(prior), val(val), max(val), l(NULL), r(NULL) {}
};

void upd(item* t) {
    if (!t) return;
    t->max = t->val;
    if (t->l && t->l->max > t->max)
        t->max = t->l->max;
    if (t->r && t->r->max > t->max)
        t->max = t->r->max;
}

void split (item* t, ll key, item* & l, item* & r) {
    if (!t)
        l = r = NULL;
    else if (key < t->key)
        split (t->l, key, l, t->l),  r = t;
    else
        split (t->r, key, t->r, r),  l = t;
    upd(t);
}

void insert (item* & t, item* it) {
    if (!t)
        t = it;
    else if (it->prior > t->prior)
        split (t, it->key, it->l, it->r),  t = it;
    else
        insert (it->key < t->key ? t->l : t->r, it);
    upd(t);
}



int n, m, k, a[MAXN];
ll s[MAXN];
using il = pair<int, ll>;
il dp[MAXN];
item* root;

ii query(ll threshold) {
    ii ans(0, 0);
    item* it = root;
    while (it) {
        if (it->key > threshold) {
            it = it->l;
        } else {
            ans = max(ans, it->val);
            if (it->l)
                ans = max(ans, it->l->max);
            it = it->r;
        }
    }
    return ans;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s[i+1] = s[i]+a[i];
    }

    dp[0] = il(0, 0);
    root = new item(0, rng(), ii(0, 0));
    for (int i = 1; i < n; i++) {
        ii maxi = query(s[i]);
        insert(root, new item(2*s[i]-s[maxi.second], rng(), ii(maxi.first+1, i)));
    }
    cout << query(s[n]).first+1 << endl;
}
