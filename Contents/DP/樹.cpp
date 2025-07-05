#include <bits/stdc++.h>

#define N 505
#define INF 0x3f3f3f3f

using namespace std ;

struct Edge{
	int v, w ;
} ;

vector<Edge> edge[N] ;
int n ;
int cnt[N] ;
int dp[N][N][2] ;

void init(){
	for ( int i=0 ; i<N ; i++ ) edge[i].clear() ;
	memset(cnt, 0, sizeof(cnt)) ;
	memset(dp, INF, sizeof(dp)) ;
}

void DFS(int u){
	cnt[u] = 1 ;
	for ( auto [v, w] : edge[u] ){
		DFS(v) ;
		cnt[u] += cnt[v] ;
	}

	dp[u][1][0] = dp[u][1][1] = 0 ;

	for ( auto [v, w] : edge[u] ){
		for ( int i=cnt[u] ; i>1 ; i-- ) for ( int j=1 ; j<i && j<=cnt[v] ; j++ ){
			dp[u][i][1] = min(dp[u][i][1], dp[u][i-j][1] + dp[v][j][1] + 2 * w) ;
			dp[u][i][0] = min(dp[u][i][0], dp[u][i-j][1] + dp[v][j][0] + w) ;
			dp[u][i][0] = min(dp[u][i][0], dp[u][i-j][0] + dp[v][j][1] + 2 * w) ;
		}
	}
}

int main(){
	int t = 0 ;

	while(~scanf("%d", &n) && n){
		init() ;
		for ( int i=0 ; i<n-1 ; i++ ){
			int u, v, w ;
			scanf("%d%d%d", &v, &u, &w) ;
			edge[u].push_back({v, w}) ;
		}
		
		DFS(0) ;
		printf("Case %d:\n", ++t) ;

		int q, e ;
		scanf("%d", &q) ;

		while(q--){
			scanf("%d", &e) ;

			for ( int i=n ; i>=1 ; i-- ) if(dp[0][i][0] <= e){
				printf("%d\n", i) ;
				break ;
			}
		}
	}

	return 0 ;
}