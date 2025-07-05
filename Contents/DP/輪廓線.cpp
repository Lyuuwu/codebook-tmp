#include <bits/stdc++.h>

using namespace std ;
using ll = long long ;

ll dp[2][(1 << 10) + 5] ;
int n, m ;
int cur ;

void update(int s1, int s2){
	if(s2 & (1 << m)){
		dp[cur][s2 ^ (1 << m)] += dp[cur ^ 1][s1] ;
	}
}

int main(){
	while(~scanf("%d%d", &n, &m)){
		if(m > n) swap(n, m) ;
		memset(dp, 0, sizeof(dp)) ;
		cur = 0 ;
		dp[cur][(1 << m) - 1] = 1 ;
		for ( int i=0 ; i<n ; i++ ) for ( int j=0 ; j<m ; j++ ){
			cur ^= 1 ;
			memset(dp[cur], 0, sizeof(dp[cur])) ;

			for ( int k=0 ; k<(1 << m) ; k++ ){
				update(k, k << 1) ; // not put
				if(i && !(k & (1 << (m - 1)))) update(k, (k << 1) | (1 << m) | 1) ; // put up
				if(j && !(k & 1)) update(k, (k << 1) | 3) ; // put left
			}
		}
		printf("%lld\n", dp[cur][(1 << m) - 1]) ;
	}
	return 0 ;
}