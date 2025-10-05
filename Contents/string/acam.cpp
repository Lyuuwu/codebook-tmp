class ACAutomation{
private:
	vector<int> fail, end, order ;
	vector<vector<int>> tree ;

	int base, alpha ;

	int new_node(){
		tree.emplace_back(alpha, 0) ;
		fail.push_back(0) ;

		return tree.size() - 1 ;
	}
public:
	ACAutomation(int _base='a', int _alpha=26)
		: base(_base), alpha(_alpha) {
			clear() ;
		}

	void clear(){
		fail.assign(1, 0) ;
		order.clear() ;
		end.clear() ;
		tree.assign(1, vector<int>(alpha, 0)) ;
	}

	void add_pattern(const string &pattern){
		int u = 0 ;
		for ( auto ch : pattern ){
			int v = ch - base ;

			if(tree[u][v] == 0) tree[u][v] = new_node() ;
			u = tree[u][v] ;
		}

		end.push_back(u) ;
	}

	void build(){
		queue<int> q ;
		order.clear() ;
		order.push_back(0) ;

		for ( int i=0 ; i<alpha ; i++ ) if(tree[0][i] > 0){
			q.push(tree[0][i]) ;
		}

		while(!q.empty()){
			int u = q.front() ; q.pop() ;
			order.push_back(u) ;

			for ( int i=0 ; i<alpha ; i++ ){
				if(tree[u][i] == 0) tree[u][i] = tree[fail[u]][i] ;
				else{
					fail[tree[u][i]] = tree[fail[u]][i] ;
					q.push(tree[u][i]) ;
				}
			}
		}
	}

	vector<int> count_per_pattern(const string &text) const {
		int u = 0 ;
		vector<int> vis(tree.size(), 0) ;

		for ( char ch : text ){
			u = tree[u][ch - base] ;
			vis[u]++ ;
		}

		for ( int i=order.size()-1 ; i>=1 ; i-- ){
			int x = order[i] ;
			vis[fail[x]] += vis[x] ;
		}

		vector<int> ans(end.size(), 0) ;
		for ( int id=0 ; id<end.size() ; id++ ){
			ans[id] = vis[end[id]] ;
		}
		
		return ans ;
	}
};