class UnionFind {
    vector<int> p;//p[i]はiの属する組織
public:
    UnionFind(int n){
        p = vector<int>(n);
        for(int i = 0; i < n; i++){
            p[i] = i;
        }
        return;
    }

/* xの属する集合を返す */
    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }

/* yにxを統合する */
    void unite(int x, int y) {
        p[find(x)] = p[find(y)];
    }

/* xとyが属する集合が同じかを判定する */
    bool same(int x, int y) {
        return find(x) == find(y);
    }

};
