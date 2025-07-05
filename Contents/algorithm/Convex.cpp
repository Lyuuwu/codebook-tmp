struct Coordinate{
	long long x, y ;

	friend bool operator<(const Coordinate&a, const Coordinate& b){
		if(a.x == b.x) return a.y < b.y ;
		return a.x < b.x ;
	}

	friend bool operator==(const Coordinate& a, const Coordinate& b){
		return a.x == b.x && a.y == b.y ;
	}
} ;

vector<Coordinate> nodes ;

long long cross(const Coordinate& o, const Coordinate& a, const Coordinate& b){
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x) ;
}

void input(){
	nodes.clear() ;

	int n, x, y ;
	char c ;
	cin >> n ;

	for ( int i=0 ; i<n ; i++ ){
		cin >> x >> y >> c ;
		if(c == 'Y') nodes.push_back({x, y}) ;
	}
}

void monotone(){
	sort(nodes.begin(), nodes.end()) ;

	int n = unique(nodes.begin(), nodes.end()) - nodes.begin() ;

	vector<Coordinate> ch(n+1) ;

	int m = 0 ;

	for ( int i=0 ; i<n ; i++ ){
		while(m > 1 && cross(ch[m-2], ch[m-1], nodes[i]) < 0) m-- ;
		ch[m++] = nodes[i] ;
	}
	for  ( int i=n-2, t=m ; i>=0 ; i-- ){
		while(m > t && cross(ch[m-2], ch[m-1], nodes[i]) < 0) m-- ;
		ch[m++] = nodes[i] ;
	}

	if(n > 1) m-- ;
	cout << m << endl ;

	for ( int i=0 ; i<m ; i++ ) cout << ch[i].x << " " << ch[i].y << endl ;
}