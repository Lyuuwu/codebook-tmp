// Li Chao Segment Tree (Min Query)
// Maintains lines y = m x + b over integer x in [X_MIN, X_MAX].
// add_line(m, b), query(x) returns min value at x. Complexity: O(log range).
// When to use:
//   - DP of form dp[i] = min_j (m_j * x_i + b_j) without monotonic slope/query assumptions.

struct LiChao {
    struct Line { long long m, b; long long get(long long x) const { return m*x + b; } };
    struct Node { Line ln; Node *l=nullptr, *r=nullptr; Node(Line v): ln(v) {} };
    long long X_MIN, X_MAX; Node* root;
    static constexpr long long INF = (long long)4e18;

    LiChao(long long xmin, long long xmax): X_MIN(xmin), X_MAX(xmax), root(nullptr) {}

    void add_line(Line nw){ add_line(root, X_MIN, X_MAX, nw); }
    void add_line(long long m, long long b){ add_line({m,b}); }

    void add_line(Node* &p, long long l, long long r, Line nw){
        if(!p){ p = new Node(nw); return; }
        long long mid = (l + r) >> 1;
        bool lef = nw.get(l) < p->ln.get(l);
        bool mdf = nw.get(mid) < p->ln.get(mid);
        if(mdf) swap(nw, p->ln);
        if(l == r) return;
        if(lef != mdf) add_line(p->l, l, mid, nw);
        else add_line(p->r, mid+1, r, nw);
    }

    long long query(long long x) const { return query(root, X_MIN, X_MAX, x); }
    long long query(Node* p, long long l, long long r, long long x) const{
        if(!p) return INF;
        long long res = p->ln.get(x);
        if(l == r) return res;
        long long mid = (l + r) >> 1;
        if(x <= mid) return min(res, query(p->l, l, mid, x));
        else return min(res, query(p->r, mid+1, r, x));
    }
};

