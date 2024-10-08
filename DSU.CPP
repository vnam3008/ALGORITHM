int root[maxn], sz[maxn];

void Init(){
    for (int i = 0; i < maxn; i++){
        root[i] = i;
        sz[i] = 1;
    }
}

int Get(int u){
    return u == root[u] ? u : root[u] = Get(root[u]);
};

bool Union(int u, int v){
    u = Get(u);
    v = Get(v);
    if (u == v) return false;
    if (sz[u] < sz[v]) swap(u, v);
    root[v] = u;
    sz[u] += sz[v];
    return true;
}
