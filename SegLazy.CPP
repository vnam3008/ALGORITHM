int a[maxn];
long long S[maxn << 2], lazy[maxn << 2];

void Init(){
    memset(S, 0, sizeof S);
    memset(lazy, 0, sizeof lazy);
}

void Build(int id, int l, int r){
    if (l == r){
        S[id] = a[l];
        return;
    }
    int mid = l + r >> 1;
    Build(id << 1, l, mid);
    Build(id << 1 | 1, mid + 1, r);
    S[id] = S[id << 1] + S[id << 1 | 1];
}

void Down(int id , int l , int r){
    int mid = l + r >> 1;
    S[id << 1] += (mid - l + 1) * lazy[id];
    S[id << 1 | 1] += (r - mid) * lazy[id];
    lazy[id << 1] += lazy[id];
    lazy[id << 1 | 1] += lazy[id];
    lazy[id] = 0;
}

void Update(int id, int l, int r, int u, int v, int val){
    if (v < l || u > r) return;
    if (u <= l && v >= r){
        lazy[id] += val;
        S[id] += (r - l + 1) * val;
        return;
    }
    Down(id , l , r);
    int mid = l + r >> 1;
    Update(id << 1, l, mid, u, v, val);
    Update(id << 1 | 1, mid + 1, r, u, v, val);
    S[id] = S[id << 1] + S[id << 1 | 1];
}

long long Get(int id, int l, int r, int u, int v){
    if (v < l || u > r) return 0;
    if (u <= l && v >= r) return S[id];
    Down(id , l , r);
    int mid = l + r >> 1;
    long long res1 = Get(id << 1, l, mid, u, v); 
    long long res2 = Get(id << 1 | 1, mid + 1, r, u, v);
    return res1 + res2;
}
