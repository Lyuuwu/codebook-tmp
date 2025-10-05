struct Edge{
	int v, cap, cost , next ;
};

using pii = pair<int, int> ;
class MCMF{
private:
	int N, s, t, tot ;
	vector<Edge> e ;
	vector<int> head ;
public:
	MCMF(int n, int _s, int _t){
		N = n ;
		s = _s ;
		t = _t ;
		e.resize(n*n + 5) ;
		head.assign(n+5, -1) ;
		tot = -1 ;
	}

	void AddEdge(int u, int v, int cap, int cost){
		e[++tot] = {v, cap, cost, head[u]} ;
		head[u] = tot ;
		e[++tot] = {u, 0, -cost, head[v]} ;
		head[v] = tot ;
	}

	int run(){
		vector<int> dis(N+1), pot(N+1, 0), preE(N+1) ;
		int flow = 0, cost = 0 ;

		auto dijkestra = [&](){
			fill(dis.begin(), dis.end(), INF) ;
			priority_queue<pii, vector<pii>, greater<pii>> pq ;
			dis[s] = 0 ;
			pq.push({0, s}) ;

			while(!pq.empty()){
				auto [d, u] = pq.top() ; pq.pop() ;
				if(d > dis[u]) continue ;
				for ( int i=head[u] ; i!=-1 ; i=e[i].next ){
					int v = e[i].v, cap = e[i].cap, w = e[i].cost ;
					if(cap && dis[v] > d + w + pot[u] - pot[v]){
						dis[v] = d + w + pot[u] - pot[v] ;
						preE[v] = i ;
						pq.push({dis[v], v}) ;
					}
				}
			}

			return dis[t] != INF ;
		};

		while(dijkestra()){
			for ( int v=1 ; v<=N ; v++ ) if(dis[v] < INF){
				pot[v] += dis[v] ;
			}

			int aug = INT_MAX ;
			for ( int v=t ; v!=s ; v=e[preE[v]^1].v ){
				aug = min(aug, e[preE[v]].cap) ;
			}

			for ( int v=t ; v!=s ; v=e[preE[v]^1].v ){
				e[preE[v]].cap -= aug ;
				e[preE[v]^1].cap += aug ;
				cost += aug * e[preE[v]].cost ;
			}
		}

		return cost ;
	}
};