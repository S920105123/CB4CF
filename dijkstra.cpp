struct Edge {
	int to, w;
};
 
vector<LL> dijkstra(const vector<vector<Edge>> &G, int src) {
	// const int INF = (LL)1e18 + 48763;
	// struct Edge {int to, w;}
	min_heap<PLL> Q;
	vector<LL> dist(G.size(), INF);
	Q.push(PLL(0LL, src));
	while (!Q.empty()) {
		PLL temp = Q.top();
		Q.pop();
		LL d = temp.fi;
		int v = temp.se;
		if (dist[v] != INF) {
			continue;
		}
		dist[v] = d;
		for (Edge e : G[v]) {
			Q.push(PLL(d + e.w, e.to));
		}
	}
	return dist;
}
