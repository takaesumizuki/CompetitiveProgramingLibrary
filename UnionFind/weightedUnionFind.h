/**
 * 重み付きUnionFind
 * Abelは重さの型UnionFind<int>とかで
 * 0-indexed
 */
template<class Abel>
struct UnionFind {
    vector<int> par;
    vector<int> rank;
    vector<Abel> diff_weight;

    /**
     * 初期化
     * @param n
     * @param SUM_UNITY
     */
    UnionFind(int n = 1, Abel SUM_UNITY = 0) {
        init(n, SUM_UNITY);
    }

    /**
     * 大きさnで初期化
     * @param n
     * @param SUM_UNITY
     */
    void init(int n = 1, Abel SUM_UNITY = 0) {
        par.resize(n);
        rank.resize(n);
        diff_weight.resize(n);
        for (int i = 0; i < n; ++i) par[i] = i, rank[i] = 0, diff_weight[i] = SUM_UNITY;
    }

    /**
     * 自分の所属しているグループを返す
     * @param x
     * @return
     */
    int find(int x) {
        if (par[x] == x) {
            return x;
        } else {
            int r = find(par[x]);
            diff_weight[x] += diff_weight[par[x]];
            return par[x] = r;
        }
    }

    /**
     * 重み
     * @param x
     * @return
     */
    Abel weight(int x) {
        find(x);
        return diff_weight[x];
    }

    /**
     * xとyが同じグループに所属しているかを返す
     * @param x
     * @param y
     * @return
     */
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    /**
     * weight(y) = weight(x) + w となるように x と y を統合
     * yにxを統合
     * @param x
     * @param y
     * @param w
     * @return
     */
    bool unite(int x, int y, Abel w) {
        w += weight(x);
        w -= weight(y);
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) swap(x, y), w = -w;
        if (rank[x] == rank[y]) ++rank[x];
        par[y] = x;
        diff_weight[y] = w;
        return true;
    }

    /**
     * (yの重さ) - (xの重さ)を返す
     * @param x
     * @param y
     * @return
     */
    Abel diff(int x, int y) {
        return weight(y) - weight(x);
    }
};