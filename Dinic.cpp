template<class T> struct Dinic {
	static const int MAXV = 210;
	static const int INF = (LL)1e9 + 5;
	struct Edge{
	    int f,to,rev;
	    T c;
	    Edge(int _to,int _r,T _c):to(_to),rev(_r),c(_c){}
	};
	
	// 0-based, MAXV is the number of vertices in the graph
	// Not the N in the problem statement!!
	vector<Edge> G[MAXV];
	int level[MAXV],st, end, n;
	int cur[MAXV];
	 
	void init(int _n){
	    n = _n;
	    for(int i=0; i<n; i++) G[i].clear();
	}
	
	pair<int, int> add_edge(int f,int t,T c, bool directed){
	    int r1 = G[f].size(), r2 = G[t].size();
	    G[f].push_back(Edge(t,r2,c));
	    G[t].push_back(Edge(f,r1,directed?0:c));
	    return make_pair(f, (int) G[f].size() - 1);
	}
	
	bool BFS(int s,int t){
	    queue<int> Q;
	    for(int i=0; i<n; i++) level[i] = 0;
	    level[s] = 1;
	    Q.push(s);
	    while(!Q.empty()){
	        int x = Q.front(); Q.pop();
	        for(int i=0; i<G[x].size(); i++){
	            Edge e = G[x][i];
	            if(e.c==0 || level[e.to]) continue;
	            level[e.to] = level[x] + 1;
	            Q.push(e.to);
	        }
	    }
	    return level[t]!=0;
	}
	
	T DFS(int s,T cur_flow){ // can't exceed c
	    if(s==end) return cur_flow;
	    T ans = 0, temp, total = 0;
	    for(int& i=cur[s]; i<G[s].size(); i++){
	        Edge &e = G[s][i];
	        if(e.c==0 || level[e.to]!=level[s]+1) continue;
	        temp = DFS(e.to, min(e.c, cur_flow));
	        if(temp!=0){
	            e.c -= temp;
	            G[e.to][e.rev].c += temp;
	            cur_flow -= temp;
	            total += temp;
	            if(cur_flow==0) break;
	        }
	    }
	    return total;
	}
	
	T max_flow(int s,int t){
		/* If you want to incrementally doing maxFlow, 
		   you need to add the result manually.
		   This function returns difference in that case. */
	    T ans = 0;
	    st = s, end = t;
	    while(BFS(s,t)){
	        while(true) {
	        	for (int i = 0; i < n; i++) cur[i] = 0;
	            T temp = DFS(s, INF);
	            if(temp==0) break;
	            ans += temp;
	        }
	    }
	    return ans;
	}
	
	vector<bool> min_cut(int s) {
	    vector<bool> visited(n);
	    queue<int> que;
	    que.push(s);
	    while (!que.empty()) {
	        int p = que.front();
	        que.pop();
	        visited[p] = true;
	        for (auto e : G[p]) {
	            if (e.c && !visited[e.to]) {
	                visited[e.to] = true;
	                que.push(e.to);
	            }
	        }
	    }
	    return visited;
	}
};
