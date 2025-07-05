struct Edge{
	int u, v, w ;
    // 這是最大生成樹, 最小生成樹要改成 w < o.w
	bool operator>(const Edge &o) const {return w > o.w ;} ;
} ;

int par[N] ;
int sz[N] ;
int sum ;

vector<Edge> edge ;

void init(){
	edge.clear() ;
	for ( int i=0 ; i<N ; i++ ){
		par[i] = i ;
		sz[i] = 1 ;
	}
	sum = 0 ;
}

int find(int x){
	if(x == par[x]) return x ;
	return par[x] = find(par[x]) ;
}

int merge(int x, int y){
	x = find(x) ;
	y = find(y) ;

	if(x == y) return 0 ;
	if(sz[x] > sz[y]) swap(x, y) ;
	par[x] = y ;
	sz[y] += sz[x] ;

	return 1 ;
}

void MST(){
	int cnt = 0 ;
	for ( int i=0 ; i<edge.size() && cnt < n-1 ; i++ ){
		auto [u, v, w] = edge[i] ;
		if(merge(u, v)){
			cnt++ ;
			sum -= w ;
		}
	}
}

int main(){
    for ( int i=0 ; i<m ; i++ ){
        scanf("%d%d%d", &u, &v, &w) ;
        edge.push_back({u, v, w}) ;
        sum += w ;
    }

    sort(edge.begin(), edge.end(), greater<Edge>()) ;
    MST() ;
}