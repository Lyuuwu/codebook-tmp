#include <bits/stdc++.h>

using namespace std ;

int K ;
int dp[20][105][105][2] ;
vector<int> dig ;

int solve(int pos, int sum, int dsum, bool lim){
    if(pos == -1){
        if(sum == 0 && dsum == 0) return 1 ;
        return 0 ;
    }

    int &d = dp[pos][sum][dsum][lim] ;
    if(d != -1) return d ;

    int up = lim ? dig[pos] : 9 ;
    int res = 0 ;
    for ( int i=0 ; i<=up ; i++ ){
        res += solve(pos-1, (sum * 10 + i) % K, (dsum + i) % K, lim && i==up) ;
    }

    return d = res ;
}

int count(int n){
    memset(dp, -1, sizeof(dp)) ;
    dig.clear() ;

    while(n > 0){
        dig.push_back(n % 10) ;
        n /= 10 ;
    }

    return solve(dig.size() - 1, 0, 0, 1) ;
}

int main(){
    int T ;
    scanf("%d", &T) ;

    int a, b ;
    while(T--){
        scanf("%d%d%d", &a, &b, &K) ;
        if(K > 90) printf("0\n") ;
        else printf("%d\n", count(b) - count(a-1)) ;
    }

    return 0 ;
}