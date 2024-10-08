int st[LOG + 5][maxn], h[maxn];
vector <int> g[maxn];

void Init(){
	memset(h, 0, sizeof h);
	memset(st, 0, sizeof st);
	for (auto &x: g) x.clear();
}

void DFS(int u){
	for (auto &v: g[u])
		if (v != st[0][u]){
			st[0][v] = u;
			h[v] = h[u] + 1;
			for (int i = 1; i <= LOG; i++)
				st[i][v] = st[i-1][st[i-1][v]];
			DFS(v);
		}
}

int LCA(int u, int v){
	if (h[u] < h[v]) swap(u, v);
	int k = h[u] - h[v];
	for (int i = LOG; i >= 0; i--)
		if (k >> i & 1) u = st[i][u];
	if (u == v) return u;
	for (int i = LOG; i >= 0; i--)
		if (st[i][u] != st[i][v]){
			u = st[i][u];
			v = st[i][v];
		}
	return st[0][u];
}
