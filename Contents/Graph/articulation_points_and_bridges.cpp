int dfn[Maxn] = {-1}, low[Maxn] = {-1}, dfscnt ;

void dfs(int u, int fa){
	dfn[u] = low[u] = ++dfscnt ;
	int child = 0 ;

	for ( auto v : g[u] ) if(v != fa){
		if(dfn[v] == -1){
			child++ ;
			dfs(v, u) ;
			low[u] = min(low[u], low[v]) ;

			if(low[v] >= dfn[u]){
				// this edge is a bridge
			}

			if(u != fa && low[v] >= dfn[u]){
				// this node v is a articulation point
			}
		}
		else low[u] = min(low[u], dfn[v]) ;
	}

	if(u == fa && child > 1){
		// this node u is a articulation point
	}
}