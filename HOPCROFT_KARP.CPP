#include <bits/stdc++.h>
using namespace std;

struct matcher {
    const int maxn = 1e6 + 5;
    const int INF = 1e9 + 5;
    
    int numNodes, numEdges;
    vector<int> matchL, matchR, dist;
    vector<vector<int>> ke;
    int matched;

    matcher(int numNodes):
        numNodes(numNodes),
        matchL(maxn, 0), matchR(maxn, 0), dist(maxn),
        ke(maxn),
        matched(0) {}

    void addEdge(int u, int v) {
        ke[u].push_back(v);
    }

    bool bfs() {
        queue<int> Q;
        for (int i = 1; i <= numNodes; i++)
            if (!matchL[i]){
                dist[i] = 0;
                Q.push(i);
            }
            else dist[i] = INF;

        bool found = false;
        while (!Q.empty()) {
            int u = Q.front(); Q.pop();
            for (auto &v: ke[u])
                if (!matchR[v]) found = true;
                else 
                    if (dist[matchR[v]] == INF) {
                        dist[matchR[v]] = dist[u] + 1;
                        Q.push(matchR[v]);
                    }
        }

        return found;
    }

    bool dfs(int u) {
        if (dist[u] == INF) return false;
        for (auto &v: ke[u]) {
            if (!matchR[v] || (dist[matchR[v]] == dist[u] + 1 && dfs(matchR[v]))) {
                matchL[u] = v;
                matchR[v] = u;
                return true;
            }
        }
        
        return false;
    }

    void process() {
        while(bfs()) {
            for (int i = 1; i <= numNodes; i++)
                if (!matchL[i]) matched += dfs(i);
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int n, m, edges; cin >> n >> m >> edges;
    matcher BipartiteGraph(n);
    while (edges--){
        int u, v; cin >> u >> v;
        BipartiteGraph.add_edge(u, v);
    }

    BipartiteGraph.process();
    cout << BipartiteGraph.matched << "\n";
    for (int i = 1; i <= BipartiteGraph.numNodes; i++)
        if (BipartiteGraph.matchL[i]) cout << i << " " << BipartiteGraph.matchL[i] << "\n";
  
    return 0;
}
