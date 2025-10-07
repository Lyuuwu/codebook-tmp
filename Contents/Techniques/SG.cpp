long long SG(long long k){

	if(k % 2 == 0){
		return k / 2;
	}
	else{
		return SG(k / 2);
	}
	
}

int main(){
	int cas, n;
	
	scanf("%d", &cas);
	while(cas--){
		scanf("%d", &n);
		
		long long s, v = 0;
		
		for(int i = 0; i < n; i++){
			scanf("%lld", &s);
			v ^= SG(s); //XOR
		}
		
		if(v) printf("YES\n");
		else printf("NO\n");
	}
}

int SG[30] ;
int vis[Maxn], stone[Maxn] ;

void build(){
	SG[0] = 0 ;
	memset(vis, 0, sizeof(vis)) ;

	for ( int i=1 ; i<30 ; i++ ){
		int cur = 0 ;
		for ( int j=0 ; j<i ; j++ ) for ( int k=0 ; k<=j ; k++ ){
			vis[SG[j] ^ SG[k]] = i ;
		}
		while(vis[cur] == i) cur++ ;
		SG[i] = cur ;
	}
}

int main(){
	build() ;

	int T = 0 ;
	while(~scanf("%d", &n) && n){
		int ans = 0 ;

		for ( int i=1 ; i<=n ; i++ ) scanf("%d", &stone[i]) ;

		for ( int i=1 ; i<=n ; i++ ) if(stone[i] & 1){
			ans ^= SG[n-i] ;	
		}
    }
}