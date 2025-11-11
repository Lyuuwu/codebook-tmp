// Interval DP — Matrix Chain Multiplication
// Given dimensions p[0..n], matrices are (p[i-1] x p[i]).
// Minimize multiplication cost. Complexity: O(n^3).
// Usage:
//   long long cost = matrixChainMinCost(p);

const long long INF = (long long)4e18;

long long matrixChainMinCost(const vector<int>& p){
    int n = (int)p.size()-1;
    vector<vector<long long>> dp(n+1, vector<long long>(n+1, 0));
    for(int len=2; len<=n; ++len){
        for(int l=1; l+len-1<=n; ++l){
            int r = l+len-1;
            dp[l][r] = INF;
            for(int k=l; k<r; ++k){
                long long cost = dp[l][k] + dp[k+1][r] + 1LL*p[l-1]*p[k]*p[r];
                dp[l][r] = min(dp[l][r], cost);
            }
        }
    }
    return dp[1][n];
}

