/*
	Dynamic hull for max dot queries

	Complexity:
	- Add: O(log n)
	- Query: O(log^2 n) but very fast in practice

	Tested: http://codeforces.com/gym/100377/problem/L
*/

typedef long long ll;
typedef complex<ll> point;

ll cross(point a, point b) { return imag(conj(a) * b); }

ll dot(point a, point b) { return real(conj(a) * b); }

ll area2(point a, point b, point c) { return cross(b - a, c - a); }

namespace std
{
	bool operator<(const point &a, const point &b)
	{
		return real(a) < real(b) || (real(a) == real(b) && imag(a) < imag(b));
	}
}

const ll oo = 0x3f3f3f3f3f3f3f3f;

struct dynamic_hull
{
	dynamic_hull() : hulls() {}

	void add_point(point p)
	{
		hull h;
		h.add_point(p);

		for (hull &_h : hulls)
			if (_h.empty())
			{
				h.swap(_h);
				break;
			}
			else h = merge(h, _h), _h.clear();

		if (!h.empty()) hulls.emplace_back(h);
	}

	ll max_dot(point p)
	{
		ll best = -oo;

		for (hull &h : hulls)
			if (!h.empty()) best = max(best, h.max_dot(p));

		return best;
	}

private:
	struct hull : vector<point>
	{
		void add_point(point p)
		{
			for (int s = size(); s > 1; --s)
				if (area2(at(s - 2), at(s - 1), p) < 0) break;
				else pop_back();
			push_back(p);
		}

		ll max_dot(point p)
		{
			int lo = 0, hi = (int) size() - 1, mid;

			while (lo < hi)
			{
				mid = (lo + hi) / 2;

				if (dot(at(mid), p) <= dot(at(mid + 1), p))
					lo = mid + 1;
				else hi = mid;
			}

			return dot(at(lo), p);
		}
	};

	static hull merge(const hull &a, const hull &b)
	{
		hull h;
		size_t i = 0, j = 0;

		while (i < a.size() && j < b.size())
			if (a[i] < b[j]) h.add_point(a[i++]);
			else h.add_point(b[j++]);

		while (i < a.size()) h.add_point(a[i++]);

		while (j < b.size()) h.add_point(b[j++]);

		return h;
	}

	vector<hull> hulls;
};
