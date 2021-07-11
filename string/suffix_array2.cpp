/*
	Tested: SPOJ SARRAY
	Complexity: O(n (log n)^2)
*/

struct suffix_array
{
	int n;
	vector<int> sa, rank, lcp;

	suffix_array(const string &s) : n(s.length()), sa(n), rank(n), lcp(n)
	{
		vector<int> t(n);
		for (int i = 0; i < n; ++i)
			rank[sa[i] = i] = s[i];
		for (int h = 1; t[n - 1] != n - 1; h *= 2)
		{
			auto cmp = [&](int i, int j)
			{
				if (rank[i] != rank[j]) return rank[i] < rank[j];
				return i + h < n && j + h < n
						? rank[i + h] < rank[j + h] : i > j;
			};
			sort(sa.begin(), sa.end(), cmp);
			for (int i = 0; i + 1 < n; ++i)
				t[i + 1] = t[i] + cmp(sa[i], sa[i + 1]);
			for (int i = 0; i < n; ++i)
				rank[sa[i]] = t[i];
		}
		for (int i = 0, k = 0; i < n; i++, k ? --k : 0)
		{
			if (rank[i] == n - 1)
			{
				k = 0;
				continue;
			}
			int j = sa[rank[i] + 1];
			while (i + k < n && j + k < n && s[i + k] == s[j + k])
				k++;
			lcp[rank[i]] = k;
		}
	}
};
