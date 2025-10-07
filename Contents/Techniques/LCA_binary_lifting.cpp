#include <bits/stdc++.h>

using namespace std ;

const int Maxn = 500005 ;

vector<int> e[Maxn] ;
int depth[Maxn] ;
int up[Maxn][40] ;
int MaxLog ;

void dfs(int u, int from, int d){
	up[u][0] = from ;
	depth[u] = d ;

	for ( int i=1 ; i<=MaxLog ; i++ ){
		up[u][i] = up[up[u][i - 1]][i - 1] ;
	}

	for ( auto v : e[u] ){
		if(v == from) continue ;
		dfs(v, u, d + 1) ;
	}
}

int lca(int u, int v){
	if(depth[u] < depth[v]) swap(u, v) ;

	for ( int i=MaxLog ; i>=0 ; i-- ) if(depth[u] - (1 << i) >= depth[v]){
		u = up[u][i] ;
	}

	if(u == v) return u ;

	for ( int i=MaxLog ; i>=0 ; i-- ) if(up[u][i] != up[v][i]){
		u = up[u][i] ;
		v = up[v][i] ;
	}

	return up[u][0] ;	
}

int main(){
	int n, q, root ;
	scanf("%d%d%d", &n, &q, &root) ;
	MaxLog = __lg(n) ;

	for ( int i=0 ; i<n-1 ; i++ ){
		int u, v ;
		scanf("%d%d", &u, &v) ;
		e[u].push_back(v) ;
		e[v].push_back(u) ;
	}

	dfs(root, root, 0) ;

	while(q--){
		int u, v ;
		scanf("%d%d", &u, &v) ;
		printf("%d\n", lca(u, v)) ;
	}

	return 0 ;
}