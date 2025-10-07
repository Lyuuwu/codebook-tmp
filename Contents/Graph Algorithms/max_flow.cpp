struct Edge{
	int v, cap, next ;
};

class MaxFlow{
private:
	int N, S, T ;
	vector<Edge> e ;
	vector<int> head, cur, dep ;

	bool bfs(){
		queue<int> q ;
		for ( int i=0 ; i<=N ; i++ ){
			cur[i] = head[i] ;
			dep[i] = -1 ;
		}

		q.push(S) ;
		dep[S] = 0 ;

		while(!q.empty()){
			int u = q.front() ; q.pop() ;

			for ( int i=head[u] ; i!=-1 ; i=e[i].next ){
				int v = e[i].v ;
				if(dep[v] == -1 && e[i].cap > 0){
					dep[v] = dep[u] + 1 ;
					if(v == T) return 1 ;
					q.push(v) ;
				}
			}
		}

		return 0 ;
	}

	int dfs(int u, int flow){
		if(u == T) return flow ;
		int d, rest = 0 ;

		for ( int &i=cur[u] ; i!=-1 ; i=e[i].next ){
			int v = e[i].v ;
			if(dep[v] == dep[u] + 1 && e[i].cap > 0){
				d = dfs(v, min(flow - rest, e[i].cap)) ;

				if(d > 0){
					e[i].cap -= d ;
					e[i^1].cap += d ;
					rest += d ;

					if(rest == flow) break ;
				}
			}
		}

		if(rest != flow) dep[u] = -1 ;
		return rest ;
	}
public:
	MaxFlow(int n, int s, int t){
		N = n ; S = s ; T = t ;
		e.reserve(n*n) ;
		head.assign(n+1, -1) ;
		cur.resize(n+1) ;
		dep.resize(n+1) ;
	}

	void AddEdge(int u, int v, int cap){
		e.push_back({v, cap, head[u]}) ;
		head[u] = e.size() - 1 ;
		e.push_back({u, 0, head[v]}) ;
		head[v] = e.size() - 1 ;
	}

	int run(){
		int ans = 0 ;
		while(bfs()){
			ans += dfs(S, 0x3f3f3f3f) ;
		}
		return ans ;
	}
};