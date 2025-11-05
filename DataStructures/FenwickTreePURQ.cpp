template<typename T>
struct PURQ {
    int n;
    vector<T> ft;
    PURQ(int n) : n(n), ft(n+1) {}
    PURQ(vector<T> &a) : PURQ((int)a.size()) {
        for(int i = 0; i < n; i++){
            add(i+1, a[i]);
        }
    }
    void add(int i, T x) {
        for( ; i <= n; i += lsb(i)){
            ft[i] += x;
        }
    }
    T query(int i){
        T sum = 0;
        for( ; i > 0; i -= lsb(i)) {
            sum += ft[i];
        }
        return sum; 
    }
    T query(int i, int j){
        return query(j) - query(i-1);
    }
};