#include <bits/stdc++.h>

using namespace std ;

const int Maxn = 2e4 + 5 ;

int n, m ;
vector<int> g[Maxn] ;

int dfn[Maxn], low[Maxn], fa[Maxn], dfscnt, cnt ;
set<int> ans ;

void init(){
	memset(dfn, -1, sizeof(dfn)) ;
	memset(low, -1, sizeof(low)) ;
	memset(fa, -1, sizeof(fa)) ;
	dfscnt = 0 ;
}

void dfs(int u){
	dfn[u] = low[u] = ++dfscnt ;

	for ( auto v : g[u] ) if(v != fa[u]){
		if(dfn[v] == -1){
			fa[v] = u ;
			dfs(v) ;
			low[u] = min(low[u], low[v]) ;
			if(fa[u] == -1) cnt++ ;
			else if(low[v] >= dfn[u]){
				ans.insert(u) ;
			}
		}
		else low[u] = min(low[u], dfn[v]) ;
	}
}

int main(){
	init() ;

	scanf("%d%d", &n, &m) ;

	while(m--){
		int u, v ;
		scanf("%d%d", &u, &v) ;
		g[u].push_back(v) ;
		g[v].push_back(u) ;
	}

	for ( int i=1 ; i<=n ; i++ ) if(dfn[i] == -1){
		cnt = 0 ;
		dfs(i) ;
		if(cnt > 1) ans.insert(i) ;
	}

	printf("%d\n", ans.size()) ;
	for ( auto node : ans ) printf("%d ", node) ;
	printf("\n") ;

	return 0 ;
}