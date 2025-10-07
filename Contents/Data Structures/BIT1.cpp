// 單點修改 單點查詢
#define lowbit(x) (x & -x)

int BIT[MAX_SIZE] ;
int n ;

void modify(int idx, int val){
    for ( ; idx <= n ; idx += lowbit(idx) ){
        BIT[idx] += val ;
    }
}

int query(int idx){
    int sum = 0 ;
    for ( ; idx ; idx -= lowbit(idx) ){
        sum += BIT[idx] ;
    }
}

void init(){
    memset(BIT, 0, sizeof(BIT)) ;
}