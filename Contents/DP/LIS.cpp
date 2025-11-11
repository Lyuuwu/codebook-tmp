// LIS (Longest Increasing Subsequence) — O(n log n)
// Usage:
//   int len = LISLen(a);
// Notes:
//   - Strictly increasing by default (use <). For non-decreasing, replace lower_bound with upper_bound.

int LISLen(const vector<long long>& a){
    vector<long long> tail; // tail[k] = minimum possible tail of an LIS with length k+1
    for(long long x : a){
        auto it = lower_bound(tail.begin(), tail.end(), x);
        if(it == tail.end()) tail.push_back(x);
        else *it = x;
    }
    return (int)tail.size();
}

