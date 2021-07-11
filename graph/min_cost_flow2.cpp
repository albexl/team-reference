/*
	Tested: ZOJ 3885
*/

template<typename T, typename C = T>
struct min_cost_flow
{
	struct edge
	{
		int src, dst;
		T cap, flow;
		C cost;
		int rev;
	};

	int n;
	vector<vector<edge>> adj;

	min_cost_flow(int n) : n(n), adj(n) {}

	void add_edge(int src, int dst, T cap, C cost)
	{
		adj[src].push_back({src, dst, cap, 0, cost, (int)adj[dst].size()});
		if (src == dst)
			adj[src].back().rev++;
		adj[dst].push_back({dst, src, 0, 0, -cost, (int)adj[src].size() - 1});
	}

	const C oo = numeric_limits<C>::max();

	vector<C> dist;
	vector<edge*> prev;
	vector<T> curflow;

	bool dijkstra(int s, int t)
	{
		dist.assign(n, oo);
		prev.assign(n, nullptr);
		curflow.assign(n, 0);
		dist[s] = 0;
		curflow[s] = numeric_limits<T>::max();

		using pci = pair<C, int>;
		priority_queue<pci, vector<pci>, greater<pci>> pq;
		pq.push({ 0, s });

		while (!pq.empty())
		{
			C d; int u;
			tie(d, u) = pq.top();
			pq.pop();

			if (d != dist[u])
				continue;

			for (auto &e : adj[u])
				if (e.flow < e.cap && dist[e.dst] > dist[u] + e.cost)
				{
					dist[e.dst] = dist[u] + e.cost;
					prev[e.dst] = &e;
					curflow[e.dst] = min(curflow[u], e.cap - e.flow);
					pq.push({ dist[e.dst], e.dst });
				}
		}

		return dist[t] < oo;
	}

	pair<T, C> max_flow(int s, int t)
	{
		T flow = 0;
		C cost = 0;

		while (dijkstra(s, t))
		{
			T delta = curflow[t];
			flow += delta;
			cost += delta * dist[t];

			for (edge *e = prev[t]; e != nullptr; e = prev[e->src])
			{
				e->flow += delta;
				adj[e->dst][e->rev].flow -= delta;
			}
		}

		return {flow, cost};
	}
};
