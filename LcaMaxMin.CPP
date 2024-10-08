int st[LOG + 5][maxn], h[maxn], mn[LOG + 1][maxn], mx[LOG + 1][maxn];
vector <pair<int, int>> g[maxn];

void Init(){
	for (int i = 1; i < maxn; i++)
		for (int j = 0; j <= LOG; j++){
			mn[j][i] = INF;
			mx[j][i] = -INF;
		}
	for (auto &x: g) x.clear();
	memset(h, 0, sizeof h);
	memset(st, 0, sizeof st);
}

void DFS(int u){
	for (auto &x: g[u]){
		int v = x.first, c = x.second;
		if (v != st[0][u]){
			st[0][v] = u;
			h[v] = h[u] + 1;
			mn[0][v] = min(mn[0][v], c);
			// mn[0][v] = min(w[u], w[v]);
			// mx[0][v] = max(w[u], w[v]);
			mx[0][v] = max(mx[0][v], c);
			for (int i = 1; i <= LOG; i++){
				st[i][v] = st[i-1][st[i-1][v]];
				mn[i][v] = min(mn[i-1][v], mn[i-1][st[i-1][v]]);
				mx[i][v] = max(mx[i-1][v], mx[i-1][st[i-1][v]]);
			}
			DFS(v);
		}
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

pair <int, int> Get(int u, int v){
	int ansMin = INF, ansMax = -INF;
	if (h[u] < h[v]) swap(u, v);
	int k = h[u] - h[v];
	for (int i = LOG; i >= 0; i--)
		if (k >> i & 1){
			ansMin = min(ansMin, mn[i][u]);
			ansMax = max(ansMax, mx[i][u]);
			u = st[i][u];
		}
	if (u == v) return {ansMin, ansMax};
	for (int i = LOG; i >= 0; i--)
		if (st[i][u] != st[i][v]){
			ansMin = min(ansMin, min(mn[i][u], mn[i][v]));
			ansMax = max(ansMax, max(mx[i][u], mx[i][v]));
			u = st[i][u];
			v = st[i][v];
		}
	ansMin = min(ansMin, min(mn[0][u], mn[0][v]));
	ansMax = max(ansMax, max(mx[0][u], mx[0][v]));
	return {ansMin, ansMax};
}
