#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)

template<class Info>
class SegmentTree {
private:
    int n;
    vector<Info> info;

    void init(int n, Info v = Info()) {
        init(vector<Info>(n, v));
    }

    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 * n, Info());
        auto build = [&](int p, int l, int r, auto &&build) {
            if (l == r) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) >> 1;
            build(left(p), l, m, build);
            build(right(p), m + 1, r, build);
            info[p] = info[left(p)] + info[right(p)];
        };
        build(1, 0, n - 1, build);
    }

    void update(int p, int l, int r, int i, const Info &v) {
        if (l == r) {
            info[p] = info[p].val + v;
            return;
        }
        int m = (l + r) >> 1;
        if (i <= m) {
            update(left(p), l, m, i, v);
        } else {
            update(right(p), m + 1, r, i, v);
        }
        info[p] = info[left(p)] + info[right(p)];
    }

    Info query(int p, int l, int r, int i) {
        if (l == r) {
            return info[p];
        }
        int m = (l + r) >> 1;
        if (i <= m) {
            return query(left(p), l, m, i);
        } else {
            return query(right(p), m + 1, r, i);
        }
    }

    Info query(int p, int l, int r, int i, int j) {
        if (r < i || l > j) {
            return Info();
        }
        if (l >= i && r <= j) {
            return info[p];
        }
        int m = (l + r) >> 1;
        return query(left(p), l, m, i, j) + query(right(p), m + 1, r, i, j);
    }
public:
    SegmentTree() : n(0) {}
    
    template<class T>
    SegmentTree(std::vector<T> init_) {
        init(init_);
    }
    
    SegmentTree(int n, Info v = Info()) {
        init(n, v);
    }
    

    Info query(int i, int j) {
        return query(1, 0, n - 1, i, j);
    }


    void update(int i, const Info &v) {
        update(1, 0, n - 1, i, v);
    }

    Info query(int i) {
        return query(1, 0, n - 1, i);
    }
};

struct Info {
    ll val;

    Info() : val(0) {}

    Info(ll val) : val(val) {}
};

Info operator+(const Info &a, const Info &b) {
    Info res = a.val + b.val;
    return res;
}