// TSP (Bitmask DP) — O(n^2 * 2^n)
// Finds min Hamiltonian cycle cost (start at 0) given distance matrix.
// Usage:
//   vector<vector<long long>> dist(n, vector<long long>(n, INF));
//   long long ans = tsp_bitmask(dist);

const long long INF = (long long)4e18;

long long tsp_bitmask(const vector<vector<long long>>& dist){
    int n = (int)dist.size();
    int S = 1<<n;
    vector<vector<long long>> dp(S, vector<long long>(n, INF));
    dp[1][0] = 0; // start at 0
    for(int mask=1; mask<S; ++mask){
        for(int u=0; u<n; ++u){
            if(!(mask & (1<<u)) || dp[mask][u] >= INF) continue;
            for(int v=0; v<n; ++v){
                if(mask & (1<<v)) continue;
                int nmask = mask | (1<<v);
                dp[nmask][v] = min(dp[nmask][v], dp[mask][u] + dist[u][v]);
            }
        }
    }
    long long ans = INF;
    for(int u=0; u<n; ++u){
        if(dp[S-1][u] < INF && dist[u][0] < INF)
            ans = min(ans, dp[S-1][u] + dist[u][0]);
    }
    return ans;
}

