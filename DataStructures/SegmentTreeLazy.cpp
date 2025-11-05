#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)

enum QueryType { ADD, SET, NONE };

template <class Info, class Tag>
class SegmentTreeLazy {
private:
	const int n;
	vector<Info> tree;
	vector<Tag> lazy;

	void apply(int p, int l, int r, const Tag &v) {
		tree[p].apply(v, l, r);
		lazy[p].apply(v);
	}

	void push(int p, int l, int r) {
		int m = (l + r) >> 1;
		apply(left(p), l, m, lazy[p]);
		apply(right(p), m + 1, r, lazy[p]);
		lazy[p] = Tag();
	}

	void update(int p, int l, int r, int i, int j, const Tag &v) {
		if (j < l || i > r) { return; }
		if (i <= l && r <= j) {
			apply(p, l, r, v);
		} else {
			push(p, l, r);
			int m = (l + r) >> 1;
			update(left(p), l, m, i, j, v);
			update(right(p), m + 1, r, i, j, v);
			tree[p] = tree[left(p)] + tree[right(p)];
		}
	}

	Info query(int p, int l, int r, int i, int j) {
		if (j < l || i > r) { return Info(); }
		if (l >= i && r <= j) { return tree[p]; }
		push(p, l, r);
		int m = (l + r) >> 1;
		return query(left(p), l, m, i, j) +
				query(right(p), m + 1, r, i, j);
	}

public:
	SegmentTreeLazy() : n(0) {}

	SegmentTreeLazy(int n) : n(n) {
		tree.assign(4 << __lg(n), Info());
		lazy.assign(4 << __lg(n), Tag());
	}

    template<class T>
	SegmentTreeLazy(const vector<T> &a) : n(a.size()) {
		tree.assign(4 << __lg(n), Info());
		lazy.assign(4 << __lg(n), Tag());
        auto build = [&](int p, int l, int r, auto &&build) -> void {
    		if (l == r) {
                tree[p] = a[l];
            } else {
                int m = (l + r) >> 1;
                build(left(p), l, m, build);
                build(right(p), m + 1, r, build);
                tree[p] = tree[left(p)] + tree[right(p)];
            }
        };
		build(1, 0, n - 1, build);
	}

	void update(int l, int r, const Tag &v) {
		update(1, 0, n - 1, l, r, v);
	}

	Info query(int l, int r) { return query(1, 0, n - 1, l, r); }
};


struct Tag {
	QueryType type = NONE;
	ll val = 0;
	void apply(const Tag &t) {
		if (t.type == ADD) {
			val += t.val;
			if (type != SET) { type = ADD; }
		} else if (t.type == SET) {
			type = SET;
			val = t.val;
		}
	}

    Tag() : val(0) {}

    Tag(QueryType type, ll val) : type(type), val(val) {}
};

struct Info {
	ll val = 0;
	void apply(const Tag &t, int l, int r) {
		if (t.type == SET) {
			val = t.val * (r - l + 1);
		} else if (t.type == ADD) {
			val += t.val * (r - l + 1);
		}
	}

    Info() : val(0) {}

    Info(ll val) : val(val) {}
};

Info operator+(const Info &a, const Info &b) {
	Info res = a.val + b.val;
	return res;
}