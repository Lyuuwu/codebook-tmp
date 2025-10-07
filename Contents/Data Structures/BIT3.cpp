// 區間修改 區間查詢
#define lowbit(x) x & -x

ll BIT1[MAXN], BIT2[MAXN] ;

void update(int idx, ll val){
    for ( int i=idx ; i<=n ; i+=lowbit(i) ){
        BIT1[i] += val ;
        BIT2[i] += idx * val ;
    }
}

// range query: query(R) - query(X - 1)
ll query(int idx){
    ll sum1 = 0, sum 2 = 0 ;
    for ( int i=idx ; i ; i-=lowbit(i) ){
        sum1 += BIT1[i] ;
        sum2 += BIT2[i] ;
    }

    return (idx + 1) * sum1 - sum2 ;
}

void build(){
    for (int i=1 ; i<=n ; i++ ){
        update(i, arr[i] - arr[i-1]) ;
    }
}

void usage(){
    update(L, x) ;
    update(R+1, -x) ;
}

void init(){
    memset(BIT1, 0, sizeof(BIT1)) ;
    memset(BIT2, 0, sizeof(BIT2)) ;
}