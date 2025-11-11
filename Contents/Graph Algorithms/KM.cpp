// KM (Kuhn-Munkres) Algorithm — Maximum Weight Bipartite Matching
// Usage:
//   - Build: KM km(nLeft, nRight);              // 1-indexed
//   - Add edges: km.addEdge(u, v, w);           // 1 <= u <= nLeft, 1 <= v <= nRight
//   - Solve: long long ans = km.solve();        // maximum total weight
//   - Retrieve matching (right -> left): auto y2x = km.match_right(); // size nRight+1
// Notes:
//   - Complexity: O(N^3), N = max(nLeft, nRight).
//   - If nLeft != nRight, internally pads the smaller side with 0 weights.
//   - If an edge (u, v) is not allowed, you may set a very negative weight
//     (e.g., -INF) to forbid it and effectively achieve "max weight among valid edges".
//   - For minimum weight matching, invert weights (e.g., add a constant or negate).

struct KM {
    int nL, nR, N; // N = max(nL, nR)
    vector<vector<long long>> w; // 1..N x 1..N (padded with 0)
    vector<long long> lx, ly, slack; // labels and slack for Y
    vector<int> slackx, prevy;       // slack argmin and previous X for Y in augmenting tree
    vector<int> xy, yx;              // matching: xy[x]=y, yx[y]=x
    static constexpr long long INF = (long long)4e18;

    KM(int _nL, int _nR){
        nL = _nL; nR = _nR; N = max(nL, nR);
        w.assign(N+1, vector<long long>(N+1, 0));
        lx.assign(N+1, 0);
        ly.assign(N+1, 0);
        slack.assign(N+1, 0);
        slackx.assign(N+1, 0);
        prevy.assign(N+1, 0);
        xy.assign(N+1, 0);
        yx.assign(N+1, 0);
    }

    void addEdge(int u, int v, long long weight){
        if(u<=0 || u>nL || v<=0 || v>nR) return;
        w[u][v] = max(w[u][v], weight); // keep the best weight if duplicated
    }

    // Core augment step for left node 'root'
    void augment(int root){
        vector<char> S(N+1, false), T(N+1, false);
        queue<int> q;
        q.push(root); S[root] = true;
        for(int y=1; y<=N; ++y){
            slack[y] = lx[root] + ly[y] - w[root][y];
            slackx[y] = root;
            prevy[y] = 0;
        }

        int y_free = 0; // free Y found to augment
        while(true){
            while(!q.empty()){
                int x = q.front(); q.pop();
                for(int y=1; y<=N; ++y){
                    if(T[y]) continue;
                    long long d = lx[x] + ly[y] - w[x][y];
                    if(d == 0){
                        // tight edge, add to tree
                        T[y] = true; prevy[y] = x;
                        if(yx[y] == 0){ y_free = y; goto AUG; }
                        // else grow the tree
                        int x2 = yx[y];
                        if(!S[x2]){ S[x2] = true; q.push(x2);
                            for(int yy=1; yy<=N; ++yy){
                                long long dd = lx[x2] + ly[yy] - w[x2][yy];
                                if(dd < slack[yy]){ slack[yy] = dd; slackx[yy] = x2; }
                            }
                        }
                    } else if(d < slack[y]){
                        slack[y] = d; slackx[y] = x;
                    }
                }
            }
            // relabel
            long long delta = INF;
            for(int y=1; y<=N; ++y) if(!T[y]) delta = min(delta, slack[y]);
            for(int x=1; x<=N; ++x) if(S[x]) lx[x] -= delta;
            for(int y=1; y<=N; ++y){
                if(T[y]) ly[y] += delta;
                else slack[y] -= delta;
            }
            for(int y=1; y<=N; ++y){
                if(!T[y] && slack[y] == 0){
                    T[y] = true; prevy[y] = slackx[y];
                    if(yx[y] == 0){ y_free = y; goto AUG; }
                    int x2 = yx[y];
                    if(!S[x2]){ S[x2] = true; q.push(x2);
                        for(int yy=1; yy<=N; ++yy){
                            long long dd = lx[x2] + ly[yy] - w[x2][yy];
                            if(dd < slack[yy]){ slack[yy] = dd; slackx[yy] = x2; }
                        }
                    }
                }
            }
        }
    AUG:
        // Augment along alternating path ending at y_free
        while(y_free){
            int x = prevy[y_free];
            int next_y = xy[x];
            yx[y_free] = x; xy[x] = y_free;
            y_free = next_y;
        }
    }

    long long solve(){
        // init labels
        for(int x=1; x<=N; ++x){
            lx[x] = w[x][1];
            for(int y=2; y<=N; ++y) lx[x] = max(lx[x], w[x][y]);
        }
        fill(ly.begin(), ly.end(), 0);
        fill(xy.begin(), xy.end(), 0);
        fill(yx.begin(), yx.end(), 0);

        for(int x=1; x<=N; ++x) augment(x);

        long long ans = 0;
        // Sum only over real nodes to avoid counting padded matches
        for(int x=1; x<=nL; ++x){
            int y = xy[x];
            if(1 <= y && y <= nR) ans += w[x][y];
        }
        return ans;
    }

    // Right side matching (1..nR), value is the matched left index (or 0 if unmatched)
    vector<int> match_right() const{
        vector<int> ret(nR+1, 0);
        for(int y=1; y<=nR; ++y){
            if(y<=N) ret[y] = (y<= (int)yx.size()-1 ? yx[y] : 0);
        }
        return ret;
    }

    // Left side matching (1..nL), value is the matched right index (or 0 if unmatched)
    vector<int> match_left() const{
        vector<int> ret(nL+1, 0);
        for(int x=1; x<=nL; ++x){
            if(x<=N) ret[x] = (x<= (int)xy.size()-1 ? xy[x] : 0);
        }
        return ret;
    }
};

/*
Example:
    int n = 3, m = 3;
    KM km(n, m);
    km.addEdge(1, 1, 5);
    km.addEdge(1, 2, 6);
    km.addEdge(2, 2, 4);
    km.addEdge(2, 3, 7);
    km.addEdge(3, 1, 3);
    long long ans = km.solve(); // maximum weight
    auto y2x = km.match_right(); // y2x[v] = matched u
*/

