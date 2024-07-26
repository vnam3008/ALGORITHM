vector <vector<long long>> Mul(vector <vector<long long>> a, vector <vector<long long>> b){
    vector <vector<long long>> c(a.size(), vector <long long> (b[0].size(), 0));
    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b[0].size(); j++)
            for (int k = 0; k < (int)a[0].size(); k++)
                c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;
    return c;
}

vector <vector<long long>> Pow(vector <vector<long long>> x, long long y){
    vector <vector<long long>> res(x.size(), vector <long long>(x.size()));
    for (int i = 0; i < (int)res.size(); i++) res[i][i] = 1;
    bool ok = false;
    while (y){
        if (y & 1){
            if (ok) res = Mul(res, x);
            else{
                res = x;
                ok = true;
            }
        }
        x = Mul(x, x);
        y >>= 1;
    }
    return res;
}
