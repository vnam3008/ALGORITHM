long long fac[maxn], inv[maxn];

long long Pow(long long a, long long b){
    long long ans = 1;
    while (b){
        if (b & 1) ans = 1LL * ans * a % MOD;
        a = 1LL * a * a % MOD;
        b >>= 1;
    }
    return ans;
}

void Init(){
    fac[0] = 1;
    for (int i = 1; i < maxn; i++) fac[i] = 1LL * fac[i - 1] * i % MOD;
    inv[maxn - 1] = Pow(fac[maxn - 1], MOD - 2);
    for (int i = maxn - 2; i >= 0; i--) inv[i] = 1LL * inv[i + 1] * (i + 1) % MOD;
}

long long C(int n, int k){
    if (k < 0 || k > n) return 0;
    return 1LL * (1LL * fac[n] * inv[k] % MOD) * inv[n - k] % MOD;
}
