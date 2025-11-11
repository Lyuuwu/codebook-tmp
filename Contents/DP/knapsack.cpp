// Classic Knapsack Templates
// Usage:
//   - zeroOneKnapsack(w, v, W)       // 0/1 knapsack, each item once
//   - completeKnapsack(w, v, W)      // complete/unbounded knapsack
//   - multipleKnapsack(w, v, c, W)   // multiple items, count c[i] via binary splitting
// When to use:
//   - 0/1: select subset with capacity limit
//   - complete: unlimited copies of each item
//   - multiple: each item has count c[i] (convert to 0/1 by splitting counts)

long long zeroOneKnapsack(const vector<int>& w, const vector<long long>& v, int W){
    vector<long long> dp(W+1, 0);
    int n = (int)w.size();
    for(int i=0;i<n;++i){
        for(int c=W;c>=w[i];--c)
            dp[c] = max(dp[c], dp[c-w[i]] + v[i]);
    }
    return *max_element(dp.begin(), dp.end());
}

long long completeKnapsack(const vector<int>& w, const vector<long long>& v, int W){
    vector<long long> dp(W+1, 0);
    int n = (int)w.size();
    for(int i=0;i<n;++i){
        for(int c=w[i]; c<=W; ++c)
            dp[c] = max(dp[c], dp[c-w[i]] + v[i]);
    }
    return *max_element(dp.begin(), dp.end());
}

long long multipleKnapsack(vector<int> w, vector<long long> v, const vector<int>& cnt, int W){
    // Binary splitting → 0/1 items
    vector<int> ww; vector<long long> vv;
    int n = (int)w.size();
    for(int i=0;i<n;++i){
        int c = cnt[i], k = 1;
        while(c>0){
            int take = min(k, c);
            ww.push_back(w[i]*take);
            vv.push_back(v[i]*take);
            c -= take; k <<= 1;
        }
    }
    return zeroOneKnapsack(ww, vv, W);
}

