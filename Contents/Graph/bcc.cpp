struct Edge{
	int v, next ;
}e[Maxm << 1] ;
int head[Maxm], tot = 1 ;

void add(int u, int v){
	e[++tot] = {v, head[u]} ;
	head[u] = tot ;
	e[++tot] = {u, head[v]} ;
	head[v] = tot ;
}

bitset<Maxm << 1> bz ;
vector<vector<int> > bcc ;
int dfn_cnt = 0, dfn[Maxn], low[Maxn], vis_bcc[Maxn], bcc_cnt = 0 ;

void dfs1(int u, int from){
	dfn[u] = low[u] = ++dfn_cnt ;

	for ( int i=head[u] ; i!=-1 ; i=e[i].next ){
		int v = e[i].v ;

		if(dfn[v] == -1){
			dfs1(v, i) ;
			if(dfn[u] < low[v]) bz[i] = bz[i^1] = 1 ;
			low[u] = min(low[u], low[v]) ;
		}
		else if(i != (from ^ 1)) low[u] = min(low[u], dfn[v]) ;
	}
}

void dfs2(int u, int id){
	vis_bcc[u] = id ;
	bcc[id].push_back(u) ;

	for ( int i=head[u] ; i!=-1 ; i=e[i].next ){
		int v = e[i].v ;

		if(vis_bcc[v] != -1 || bz[i]) continue ;
		dfs2(v, id) ;
	}
}

void init(){
	memset(dfn, -1, sizeof(dfn)) ;
	memset(head, -1, sizeof(head)) ;
	memset(vis_bcc, -1, sizeof(vis_bcc)) ;
}

int main(){
    init() ;
    input() ;
    for ( int i=1 ; i<=n ; i++ ) if(dfn[i] == -1){
		dfs1(i, 0) ;
	}

	for ( int i=1 ; i<=n ; i++ ) if(vis_bcc[i] == -1){
		bcc.push_back(vector<int>()) ;
		dfs2(i, bcc_cnt++) ;
	}
}