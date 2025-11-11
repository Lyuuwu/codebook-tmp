// Monotonic Queue Optimization (Sliding window DP)
// Pattern:
//   dp[i] = cost[i] + min_{j in [i-W, i-1]} dp[j]
// Maintain deque of candidate indices with increasing dp[j], dropping out-of-window.
// Complexity: O(n)
// When to use:
//   - Transition takes min/max over a fixed-width window of previous states.

long long solve_with_window(const vector<long long>& cost, int W){
    int n = (int)cost.size();
    vector<long long> dp(n, (long long)4e18);
    deque<int> dq; // indices of candidates, dp[dq] increasing
    for(int i=0;i<n;++i){
        // remove out-of-window (keep j in [i-W, i-1])
        while(!dq.empty() && dq.front() < i - W) dq.pop_front();
        // base for i: if dq empty, no feasible j; else take min dp[j]
        if(!dq.empty()) dp[i] = cost[i] + dp[dq.front()];
        else if(i==0) dp[i] = cost[i]; // starting point if needed
        // push current i into deque
        while(!dq.empty() && dp[dq.back()] >= dp[i]) dq.pop_back();
        dq.push_back(i);
    }
    return dp.back();
}

