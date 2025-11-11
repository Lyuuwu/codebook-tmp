// LCS (Longest Common Subsequence) — O(n*m)
// Usage:
//   int len = LCSLen(s, t);
// Notes: Uses O(min(n,m)) memory if desired; this is a simple O(n*m) DP.

int LCSLen(const string& s, const string& t){
    int n = (int)s.size(), m = (int)t.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(s[i-1]==t[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    return dp[n][m];
}

