class RURQ {
    private:
        RUPQ rupq;
        PURQ purq;
    public:
        RURQ(int m) : purq(PURQ(m)), rupq(RUPQ(m)) {}
    void range_update(int i, int j, ll v) {
        rupq.range_update(i, j, v);
        purq.update(i, v*(i-1));
        purq.update(j+1, -v*j);
    }
    ll rsq(int i) {
        return rupq.point_query(i)*i - purq.rsq(i);
    }
    ll rsq(int i, int j) {
        return rsq(j) - rsq(i-1);
    }
};