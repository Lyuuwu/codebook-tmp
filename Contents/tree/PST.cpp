// Find range k-th largest number
struct Node{
	int sum, left, right ;
}seg[Maxn + 20 * Maxn] ;

class PersistentSegmentTree{
private:
	int n ;
	int cnt ;
	vector<int> version ;

	int build(int L, int R){
		int cur_cnt = cnt++ ;
		if(L == R){
			seg[cur_cnt] = {0, 0, 0} ;
			return cur_cnt ;
		}

		int M = (L + R) >> 1 ;
		int lc = build(L, M) ;
		int rc = build(M+1, R) ;
		
		seg[cur_cnt] = {0, lc, rc} ;
		return cur_cnt ;
	}
public:
	PersistentSegmentTree(int _n){
		n = _n ;
		cnt = 0 ;

		int root = build(1, n) ;
		version.push_back(root) ;
	}

	void update(int ver, int idx){
		auto upd = [&](auto &&self, const int cur, int L, int R){
			int cur_cnt = cnt++ ;

			if(L == R){
				seg[cur_cnt] = {seg[cur].sum + 1, 0, 0} ;
				return cur_cnt ;
			}

			int M = (L + R) >> 1 ;
			int lc = seg[cur].left ;
			int rc = seg[cur].right ;

			if(idx <= M) lc = self(self, seg[cur].left, L, M) ;
			else rc = self(self, seg[cur].right, M+1, R) ;

			seg[cur_cnt] = {seg[lc].sum + seg[rc].sum, lc, rc} ;

			return cur_cnt ;
		};

		int root = upd(upd, version[ver], 1, n) ;
		version.push_back(root) ;
	}

	int query(int verL, int verR, int k){
		auto qry = [&](auto &&self, const int cur_old, const int cur_new, int L, int R){
			if(L == R) return L ;

			int old_l = seg[cur_old].left, old_r = seg[cur_old].right ;
			int new_l = seg[cur_new].left, new_r = seg[cur_new].right ;

			int dl = seg[new_l].sum - seg[old_l].sum ;
			int dr = seg[new_r].sum - seg[old_r].sum ;

			int M = (L + R) >> 1 ;

			if(dl >= k) return self(self, old_l, new_l, L, M) ;
			k -= dl ;
			return self(self, old_r, new_r, M+1, R) ;
		};

		int idx = qry(qry, version[verL-1], version[verR], 1, n) ;
		return idx ;
	}
};