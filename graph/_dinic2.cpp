template<typename F>
struct dinic
{
	struct edge
	{
		int src, dst, rev;
		F flow, cap;
	};

	int n;
	vector<vector<edge>> adj;

	dinic(int n) : n(n), adj(n), it(n), level(n) {}

	void add_edge(int u, int v, F cuv, F cvu = 0)
	{
		adj[u].push_back({u, v, (int) adj[v].size(), 0, cuv});
		if (u == v) adj[u].back().rev++;
		adj[v].push_back({v, u, (int) adj[u].size() - 1, 0, cvu});
	}

	vector<decltype(adj.front().begin())> it;
	vector<int> level;

	bool bfs(int s, int t)
	{
		fill(level.begin(), level.end(), -1);
		queue<int> q;

		for (q.push(t), level[t] = 0; !q.empty(); q.pop())
		{
			t = q.front();
			for (edge &e : adj[t])
			{
				edge &ee = adj[e.dst][e.rev];
				if (ee.flow < ee.cap && level[e.dst] == -1)
					level[e.dst] = 1 + level[t], q.push(e.dst);
			}
		}

		return level[s] >= 0;
	}

	F dfs(int s, int t, F f)
	{
		if (s == t)
			return f;

		F flow = 0;

		for (; it[s] != adj[s].end(); ++it[s])
		{
			edge &e = *it[s];

			if (level[s] == 1 + level[e.dst] && e.flow < e.cap)
			{
				F delta = dfs(e.dst, t, min(f - flow, e.cap - e.flow));
				e.flow += delta;
				adj[e.dst][e.rev].flow -= delta;
				flow += delta;
			}

			if (flow == f) return flow;
		}

		return flow;
	}

	const F oo = numeric_limits<F>::max();

	F max_flow(int s, int t)
	{
		for (int u = 0; u < n; ++u)
			for (edge &e : adj[u])
				e.flow = 0;

		F flow = 0;

		while (bfs(s, t))
		{
			for (int u = 0; u < n; ++u)
				it[u] = adj[u].begin();

			flow += dfs(s, t, oo);
		}

		// level[u] == -1 => s side of min cut
		return flow;
	}
};