/* HLD */
int fa[Maxn], top[Maxn], son[Maxn], sz[Maxn], dep[Maxn] = {0}, dfn[Maxn], rnk[Maxn], dfscnt = 0 ;

void dfs1(int u, int from){
	fa[u] = from ;
	dep[u] = dep[from] + 1 ;
	sz[u] = 1 ;

	for ( auto v : g[u] ) if(v != from){
		dfs1(v, u) ;
		sz[u] += sz[v] ;
		if(son[u] == -1 || sz[v] > sz[son[u]]) son[u] = v ;
	}
}

void dfs2(int u, int t){
	top[u] = t ;
	dfn[u] = ++dfscnt ;
	rnk[dfscnt] = u ;

	if(son[u] == -1) return ;

	dfs2(son[u], t) ;

	for ( auto v : g[u] ) if(v != fa[u] && v != son[u]){
		dfs2(v, v) ;
	}
}

/* Segment Tree */
#define lc (id << 1)
#define rc ((id << 1) | 1)

struct ColorSeg{
	int left, right, tot ;

	ColorSeg operator+(const ColorSeg &o) const {
		if(tot == 0) return o ;
		if(o.tot == 0) return *this ;

		ColorSeg tmp ;
		tmp.left = left ;
		tmp.right = o.right ;
		tmp.tot = tot + o.tot - (right == o.left) ;
		
		return tmp ;
	}
} ;

struct Node{
	ColorSeg color ;
	int tag ;
}seg[Maxn << 2] ;

class SegmentTree{
private:
	void pull(int id){
		// normal pull
	}

	void AddTag(int id, int tag){
		// normal AddTag
	}

	void push(int id){
		// normal push
	}

	void modify(int l, int r, int tag, int L=1, int R=n, int id=1){
		// normal modify
	}

	ColorSeg query(int l, int r, int L=1, int R=n, int id=1){
		// normal query
	}
public:
	void build(int L=1, int R=n, int id=1){
		// normal build
	}

    // update val from u to v (simple path)
	void update(int u, int v, int val){
		while(top[u] != top[v]){
			if(dep[top[u]] < dep[top[v]]) swap(u, v) ;
			modify(dfn[top[u]], dfn[u], val) ;
			u = fa[top[u]] ;
		}

		if(dep[u] < dep[v]) swap(u, v) ;
		modify(dfn[v], dfn[u], val) ;
	}

    // get sum from u to v (simple path)
	int get(int u, int v){
		pair<int, ColorSeg> U, V ;
		ColorSeg M ;
		U = {u, {0, 0, 0}} ;
		V = {v, {0, 0, 0}} ;

		while(top[U.first] != top[V.first]){
			if(dep[top[U.first]] < dep[top[V.first]]) swap(U, V) ;
			U.second = query(dfn[top[U.first]], dfn[U.first]) + U.second ;
			U.first = fa[top[U.first]] ;
		}

		if(dep[U.first] < dep[V.first]) swap(U, V) ;
		
		M = query(dfn[V.first], dfn[U.first]) ;

		return (U.second.tot + V.second.tot + M.tot) - (U.second.left == M.right) - (V.second.left == M.left) ;
	}
}tree ;

void init(){
	memset(son, -1, sizeof(son)) ;
}