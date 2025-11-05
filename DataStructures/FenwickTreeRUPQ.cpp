template<typename T>
struct RUPQ {
	int n;
	vector<T> ft;
	RUPQ(int n) : n(n), ft(n+1) {}
	RUPQ(vector<T> &a) : RUPQ(a.size()) {
		for(int i = 0; i < n; i++) {
			update(i+1, i+1, a[i]);
		}
	}
	void update(int i, T v) {
		for( ; i <= n; i += lsb(i)) {
			ft[i] += v;
		}
	}
	void update(int i, int j, T v) {
		update(i, v);
		update(j+1, -v);
	}
	T query(int i) {
		T ans = 0;
		for( ; i; i -= lsb(i)) {
			ans += ft[i];
		}
		return ans;
	}
};