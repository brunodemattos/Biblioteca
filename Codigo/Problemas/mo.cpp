// Mo algorithm - distinct values
// 
// O(s*n*f + q*(n/s)*f) optimize over s, insert/erase = O(f)
// for s = sqrt(n), O((n+q)*sqrt(n)*f)

const int MAX = 3e4+10;
const int SQ = sqrt(MAX);
int v[MAX];

int ans, freq[MAX];

inline void insert(int p) {
	int o = v[p];
	freq[o]++;
	ans += (freq[o] == 1);
}

inline void erase(int p) {
	int o = v[p];
	ans -= (freq[o] == 1);
	freq[o]--;
}

inline ll hilbert(int x, int y) {
	static int N = (1 << 20);
	int rx, ry, s;
	ll d = 0;
	for (s = N/2; s>0; s /= 2) {
		rx = (x & s) > 0;
		ry = (y & s) > 0;
		d += s * ll(s) * ((3 * rx) ^ ry);
		if (ry == 0) {
			if (rx == 1) {
				x = N-1 - x;
				y = N-1 - y;
			}
			swap(x, y);
		}
	}
	return d;
}

#define HILBERT true
vector<int> MO(vector<ii> &q) {
	ans = 0;
	int m = q.size();
	vector<int> ord(m);
	iota(ord.begin(), ord.end(), 0);
#if HILBERT
	vector<ll> h(m);
	for (int i = 0; i < m; i++) h[i] = hilbert(q[i].first, q[i].second);
	sort(ord.begin(), ord.end(), [&](int l, int r) { return h[l] < h[r]; });
#else
	sort(ord.begin(), ord.end(), [&](int l, int r) {
		if (qu[l].first / SQ != qu[r].first / SQ) return qu[l].first < qu[r].first;
		if ((qu[l].first / SQ) % 2) return qu[l].s > qu[r].s;
		return qu[l].s < qu[r].s;
	});
#endif
	vector<int> ret(m);
	int l = 0, r = -1;

	for (int i : ord) {
		int ql, qr;
		tie(ql, qr) = q[i];
		while (r < qr) insert(++r);
		while (l > ql) insert(--l);
		while (l < ql) erase(l++);
		while (r > qr) erase(r--);
		ret[i] = ans;
	}
	return ret;
}
