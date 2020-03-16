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
 * one side.
 * 
 * If you note that (ans[j]+1, j) is increasing in j, you can use a stack and a binary search inside the stack to solve the problem!
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ii = pair<int, int>;
const int INF = 1e9+9;
const int MAXN = 1000006;

int n, a[MAXN];
ll s[MAXN];
using lii = pair<ll, ii>;
vector<lii> myStack;

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        s[i+1] = s[i]+a[i];
    }

    myStack.emplace_back(0, ii(0, 0));
    for (int i = 1; i <= n; i++) {
        ii maxi = (--upper_bound(myStack.begin(), myStack.end(), lii(s[i], ii(INF, INF))))->second;
        ll key = 2*s[i]-s[maxi.second];
        while (myStack.back().first >= key)
            myStack.pop_back();
        myStack.emplace_back(key, ii(maxi.first+1, i));
    }
    cout << myStack.back().second.first << endl;
}
