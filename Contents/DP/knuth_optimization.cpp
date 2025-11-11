// Knuth Optimization — Interval DP O(n^2)
// Applies to DP of the form:
//   dp[l][r] = min_{l<=k<r} { dp[l][k] + dp[k+1][r] } + w(l,r)
// Conditions:
//   1) Quadrangle inequality on w: A[a][c] + A[b][d] <= A[a][d] + A[b][c] for a<=b<=c<=d
//   2) Monge array (or equivalent) ⇒ opt[l][r-1] <= opt[l][r] <= opt[l+1][r]
// Typical: merging stones, optimal BST, matrix chain variants.

const long long INF = (long long)4e18;

// Example: w(l,r) via prefix sums (replace with your cost)
inline long long w(int l, int r, const vector<long long>& pref){
    // cost of merging [l..r]
    return pref[r] - pref[l-1];
}

long long knuth_dp(const vector<long long>& a){
    int n = (int)a.size();
    vector<long long> pref(n+1,0);
    for(int i=1;i<=n;++i) pref[i]=pref[i-1]+a[i-1];
    vector<vector<long long>> dp(n+2, vector<long long>(n+2, 0));
    vector<vector<int>> opt(n+2, vector<int>(n+2, 0));
    for(int i=1;i<=n;++i) opt[i][i]=i;
    for(int len=2; len<=n; ++len){
        for(int l=1; l+len-1<=n; ++l){
            int r=l+len-1;
            dp[l][r] = INF;
            int st = opt[l][r-1], ed = opt[l+1][r];
            if(st==0) st=l; if(ed==0) ed=r-1;
            for(int k=st; k<=ed; ++k){
                long long val = dp[l][k] + dp[k+1][r] + w(l, r, pref);
                if(val < dp[l][r]){ dp[l][r]=val; opt[l][r]=k; }
            }
        }
    }
    return dp[1][n];
}

