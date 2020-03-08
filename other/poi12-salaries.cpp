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


int n, p[MAXN], z[MAXN], rev[MAXN];
vi gr[MAXN];

int dfs(int u) {
    int sz = 1;
    for (int v : gr[u]) {
        sz += dfs(v);
    }
    return sz;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++) {
        rev[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> z[i];
        p[i]--, z[i]--;
        if (p[i] == i)
            z[i] = n-1;
        if (z[i] == -1)
            gr[p[i]].push_back(i);
        rev[z[i]] = i;
    }

    int random = 0;
    priority_queue<int> determined;
    for (int i = 0; i < n; i++) {
        if (rev[i] == -1) {
            // cerr << "push " << i << endl;
            determined.push(i);
        } else {
            int u = rev[i], sz = dfs(u)-1;
            if (sz == 0) continue;
            // cerr << "sz[" << u << "] = " << sz << endl;
            if ((int) determined.size() + random == sz) {
            //     cerr << "can determine?\n";
                while (!determined.empty() and gr[u].size() == 1) {
            //         cerr << "ans[" << gr[u][0] << "] = " << determined.top() << endl;
                    u = gr[u][0];
                    z[u] = determined.top();
                    determined.pop();
                }
            }
            while (!determined.empty())
                random++, determined.pop();
            random -= dfs(u)-1;
        }
    }

    for (int i = 0; i < n; i++) {
        cout << z[i]+1 << endl;
    }
}
