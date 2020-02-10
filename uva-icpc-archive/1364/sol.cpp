// I'm not very proud of this code...
#include<bits/stdc++.h>
using namespace std;

using vi = vector<int>;
const int MAXN = 1003;

int n, m, adj[MAXN][MAXN], ans[MAXN];
vi gr[MAXN];

int low[MAXN], num[MAXN], p[MAXN];
int dfsNum, dfsRoot, rootChildren;
int numBCC;
vi bcc[MAXN];
int c[MAXN], trimmed[MAXN], selected;

stack<int> st;
void dfs(int u) {
  if (p[u] == -1) {
    dfsRoot = u;
    rootChildren = 0;
  }
  low[u] = num[u] = dfsNum++;
  for (int v : gr[u]) {
    if (num[v] == -1) {
      p[v] = u;
      if (u == dfsRoot) rootChildren++;
      int stSZ = st.size();
      dfs(v);
      if (low[v] >= num[u]) {
        while ((int) st.size() > stSZ) {
          bcc[numBCC].push_back(st.top());
          st.pop();
        }
        bcc[numBCC].push_back(u);
        numBCC++;
      }
      low[u] = min(low[u], low[v]);
    } else if (v != p[u]) {
      low[u] = min(low[u], num[v]);
    }
  }
  if (u != dfsRoot)
    st.push(u);
}

bool bipartite(int u, int p = -1) {
    c[u] = p == -1? 0 : 1-c[p];
    for (int v : gr[u]) {
        if (trimmed[v] == selected) {
            if (c[v] == -1) {
                if (!bipartite(v, u)) {
                    return false;
                }
            } else if (c[v] == c[u]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
  while (cin >> n >> m, n != 0) {
    dfsNum = numBCC = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i != j)
          adj[i][j] = true;
      }
      gr[i].clear();
      bcc[i].clear();
      trimmed[i] = p[i] = num[i] = low[i] = -1;
      ans[i] = false;
    }
    for (int i = 0, u, v; i < m; i++) {
      cin >> u >> v; u--, v--;
      adj[u][v] = adj[v][u] = false;
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (adj[i][j]) {
          gr[i].push_back(j);
        }
      }
    }

    for (int i = 0; i < n; i++) {
      if (num[i] == -1) {
        dfs(i);
      }
    }

	// for (int i = 0; i < numBCC; i++) {
 //    	for (int v : bcc[i]) {
 //        	cerr << v << "  ";
 //    	}
	// 	cerr << endl;
	// }
	// cerr << endl;

	for (int i = 0; i < numBCC; i++) {
    	selected = i;
    	for (int u : bcc[i]) {
        	trimmed[u] = i;
        	c[u] = -1;
    	}
    	if (!bipartite(bcc[i][0])) {
        	for (int u : bcc[i]) {
            	ans[u] = true;
        	}
    	}
	}
    
    int out = n;
    for (int i = 0; i < n; i++) {
      if (ans[i]) out--;
    }
    cout << out << endl;
  }
}
