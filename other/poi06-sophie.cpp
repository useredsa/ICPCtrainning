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
const int MAXK = 10;


int n, m, k;
set<ii> e;
vi gr[MAXN];
vi ans;

inline bool inside(int u) {
    return find(ans.begin(), ans.end(), u) != ans.end();
}

bool back() {
    if ((int) ans.size() == k || e.empty()) {
        return e.empty();
    }
    ii edge = *e.begin();
    for (int u = edge.first; true; u = edge.second) {
        for (int v : gr[u]) {
            e.erase(ii(u, v));
            e.erase(ii(v, u));
        }
        ans.push_back(u);
        if (back()) return true;
        ans.pop_back();
        for (int v : gr[u]) {
            if (!inside(v)) {
                e.emplace(u, v);
                e.emplace(v, u);
            }
        }
        if (u == edge.second) break;
    }
    return false;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> k >> m;
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        --a, -- b;
        if ((int) gr[a].size() > MAXK or (int) gr[b].size() > MAXK) continue;
        if (find(gr[a].begin(), gr[a].end(), b) != gr[a].end()) {
            continue;
        }
        gr[a].push_back(b);
        gr[b].push_back(a);
        e.emplace(a, b);
        e.emplace(b, a);
    }
    for (int u = 0; u < n; ++u) {
        if ((int) gr[u].size() > MAXK) {
            ans.push_back(u);
            for (int v : gr[u]) {
                e.erase(ii(u, v));
                e.erase(ii(v, u));
            }
        }
    }

    int aux = n-k;
    for (k = ans.size(); k <= aux; ++k) {
        if (back()) {
            cout << n-ans.size() << endl;
            for (int u = 0; u < n; ++u) {
                if (!inside(u)) {
                    cout << u+1 << ' ';
                }
            }
            cout << endl;
            return 0;
        }
    }
    cout << "NIE\n";
}
