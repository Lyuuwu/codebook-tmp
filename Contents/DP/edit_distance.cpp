// Edit Distance (Levenshtein) — O(n*m)
// Usage:
//   int d = editDistance(a, b, 1, 1, 1); // costs: ins, del, sub

int editDistance(const string& a, const string& b, int ins=1, int del=1, int sub=1){
    int n = (int)a.size(), m = (int)b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i=0;i<=n;++i) dp[i][0] = i*del;
    for(int j=0;j<=m;++j) dp[0][j] = j*ins;
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(a[i-1]==b[j-1]) dp[i][j] = dp[i-1][j-1];
            else dp[i][j] = min({dp[i-1][j] + del, dp[i][j-1] + ins, dp[i-1][j-1] + sub});
        }
    }
    return dp[n][m];
}

