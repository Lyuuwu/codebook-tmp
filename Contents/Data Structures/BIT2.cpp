// 區間修改, 單點查詢
#define lowbit(x) (x & -x)

int BIT[MAX_SIZE] ;
int n ;

void modify(int idx, int val){
    for ( ; idx <= n ; idx += lowbit(idx) ){
        BIT[idx] += val ;
    }
}

// ans: query(i)
int query(int idx){
    int sum = 0 ;
    for ( ; idx ; idx -= lowbit(idx) ){
        sum += BIT[idx] ;
    }

    return sum ;
}

void init(){
    memset(BIT, 0, sizeof(BIT)) ;
}

void build(){
    arr[0] = 0 ;
    for ( int i=1 ; i<=n ; i++ ) modify(i, arr[i] - arr[i-1]) ;
}

// usage
// add val
modify(L, x) ;
modify(R+1, -x) ;