// xxxxxoooo 找最小解
bool binary_search(){
    while(l < r){
        int m = (l + r) >> 1 ;
        if(check(m)) r = m ;
        else l = m + 1 ;
    }

    return l ;
}

// ooooxxxx 找最大解
bool binary_search(){
    while(l < r){
        int m = (l + r) >> 1 ;
        if(check(m)) l = m ;
        else r = m - 1 ;
    }

    return l ;
}

// 如果l & r 太大, m = (l + (r - l))  >> 1 ;