vector<int> scc[Maxn] ;
int dfn[Maxn], low[Maxn], sccId[Maxn], dfscnt = 0, cnt_scc = 0 ;
stack<int> st ;
bitset<Maxn> inSt, vis ;

void dfs(int u, int from){
	dfn[u] = low[u] = ++dfscnt ;
	st.push(u) ;
	inSt[u] = 1 ;

	for ( auto v : g[u] ){
		if(!inSt[v] && dfn[v] != -1) continue ;
		if(dfn[v] == -1) dfs(v, u) ;
		low[u] = min(low[u], low[v]) ;
	}

	if(dfn[u] == low[u]){
		cnt_scc++ ;
		int x ;

		do{
			x = st.top() ;
			st.pop() ;

			inSt[x] = 0 ;
			sccId[x] = cnt_scc ;
			scc[cnt_scc].push_back(x) ;
		}
		while(x != u) ;
	}
}

void init(){
	memset(dfn, -1, sizeof(dfn)) ;
	memset(low, -1, sizeof(low)) ;
}

int main(){
    init() ;
    input() ;
    for ( int i=1 ; i<=n ; i++ ) if(dfn[i] == -1){
		dfs(i, i) ;
	}
}