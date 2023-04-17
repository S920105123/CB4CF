
struct Min_cost_flow {
	// 0-based
	#define fi first
	#define se second
	#define PII pair<int, int>
//	static const int MAXV = MAXN * MAXN;
//	static const LL CINF = (LL)1e9 + 8763; // > maximum weighted distance 
	struct Edge {
	    int to,rev;
		LL cap,cost;
		Edge(int _to, int _rev, LL _cap, LL _cost) {
			to = _to; rev = _rev, cap = _cap, cost = _cost;
		}
	};
	
	int V;
	vector<Edge> G[MAXV];
	PII pre[MAXV];
	LL flow[MAXV], dist[MAXV];
	bool inque[MAXV];
	
	void init(int _V) {
	    V = _V;
	    for (int i = 0; i <= V; i++) {
	    	G[i].clear();
		}
	}
	PII add_edge(int fr, int to, LL cap, LL cost) {
		// add a directed edge
		int a = G[fr].size(), b = G[to].size();
	    G[fr].push_back(Edge(to, b, cap, cost));
	    G[to].push_back(Edge(fr, a, 0, -cost));
	    return {fr, (int) G[fr].size() - 1};
	}
	bool SPFA(int s, int t, LL &ans_flow, LL &ans_cost) {
		// Infinite loop if negative cycle
		queue<int> que;
	    for (int i = 0; i <= V; i++) {
	        dist[i] = CINF;
	        inque[i] = false;
	    }
	    dist[s] = 0;
	    flow[s] = CINF;
	    inque[s] = true;
	    que.push(s);
	    while (!que.empty()) {
	        int v = que.front();
			que.pop();
	        inque[v] = false;
	        for (int i = 0; i < G[v].size(); i++) {
	        	const Edge &e = G[v][i];
	            if (e.cap > 0 && dist[v] + e.cost < dist[e.to]) {
	                flow[e.to] = min(flow[v], e.cap);
	                dist[e.to] = dist[v] + e.cost;
	                pre[e.to] = PII(v, i);
	                if (!inque[e.to]) {
	                	que.push(e.to);
						inque[e.to] = true;
					}
	            }
	        }
	    }
	    if (dist[t] == CINF) return false;
	    if (dist[t] >= 0) return false;
	    // Add above line -> min cost first, then max flow (priority)
	    // Without        -> max flow first, then min cost
	
	    int v = t;
		LL f = flow[t];
	    ans_flow += flow[t];
	    ans_cost += dist[t] * flow[t];
	    while (v != s) {
	    	Edge &e = G[pre[v].fi][pre[v].se];
	        e.cap -= f;
	        G[v][e.rev].cap += f;
	        v = pre[v].fi;
	    }
	    return true;
	}
	pair<LL, LL> MCMF(int s, int t) {
	    LL ans_flow = 0, ans_cost = 0;
	    while (SPFA(s, t, ans_flow, ans_cost));
	    return make_pair(ans_flow, ans_cost);
	}
} algo;
