#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using ii = pair<int, int>;
using vi = vector<int>;
using vii = vector<ii>;
const int INF = 1e9+7;
const ll MOD = 1e9+7;
const int MAXN = 2000006;



// Read :40
// Think :43
// Code :29 (6 minutes rest)


int t, n, m, used[MAXN];
vi g[MAXN], gr[MAXN], order;
int ncc;
vi components[MAXN];

void dfs1(int v) {
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i)
        if (!used[g[v][i]]) dfs1(g[v][i]);
    order.push_back(v);
}

void dfs2(int v) {
    used[v] = true;
    components[ncc].push_back(v);
    for (size_t i = 0; i < gr[v].size(); ++i)
        if (!used[gr[v][i]]) dfs2(gr[v][i]);
}

void scc() {
    ncc = 0;
    order.clear();
    memset(used, 0, n*sizeof(int));
    for (int i = 0; i < n; ++i)
        if (!used[i]) dfs1(i);
    memset(used, 0, n*sizeof(int));
    for (int i=0; i<n; ++i) {
        int v = order[n-1-i];
        if (!used[v]) {
            components[ncc].clear();
            dfs2 (v);
            ncc++;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> t;
    while (t--) {
        cin >> n >> m;
        n<<=1;
        for (int i = 0; i < n; ++i) {
            g[i].clear();
            gr[i].clear();
        }
        for (int i = 0, u, v; i < m; ++i) {
            cin >> u >> v;
            u=(u-1)<<1, v=(v-1)<<1;
            if (u == v) {
                g[u|1].push_back(v);
                gr[v].push_back(u|1);
            } else {
                g[u].push_back(v|1);
                gr[v|1].push_back(u);
            }
        }
        scc();
        n>>=1;

        memset(used, 0, n*sizeof(int));
        int ans = 0;
        for (int v : components[0]) {
            if (!used[v>>1]) {
                used[v>>1] = true;
                ans++;
            }
        }
        bool feasible = true;
        // for (int i = 0; i < n; ++i) {
        //     if (used[i]) {
        //         for (int v : g[i<<1]) {
        //             if (!used[v>>1]) {
        //                 //feasible = false;
        //             }
        //         }
        //     }    
        // }
        if (0 < ans && ans < n && feasible) {
            cout << "Yes\n" << n-ans << ' ' << ans << '\n';
            for (int i = 0; i < n; ++i) {
                if (!used[i])
                    cout << i+1 << ' ';
            }
            cout << '\n';
            for (int i = 0; i < n; ++i) {
                if (used[i])
                    cout << i+1 << ' ';
            }
            cout << '\n';
        } else {
            cout << "No\n";
        }
    }

}

