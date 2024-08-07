/*
    author: Tran Van Nam
    Nguyen Trai High School - Quang Binh
*/
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e6 + 5;
const int MOD = 1e9 + 7;

long long fac[maxn], inv[maxn];

long long Mul(long long a, long long b){
    long long ans = 0;
    while (b){
        if (b & 1) ans = (ans + a) % MOD;
        a = (a + a) % MOD;
        b >>= 1;
    }
    return ans;
}

long long Pow(long long a, long long b){
    long long ans = 1;
    while (b){
        if (b & 1) ans = ans * a % MOD;
        a = a * a % MOD;
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

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    Init();
    
    
    return 0^0;
}
