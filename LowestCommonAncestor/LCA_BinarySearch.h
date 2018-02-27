struct LCA {
    int V;//頂点数
    vector <vector<int>> G;//グラフの隣接リスト表現
    int MAX_LOG_V = 1;
    int root = 0;//根ノードの番号

    vector <vector<int>> parent;//親を2^k回辿って到達する頂点(根を通り過ぎる場合は-1とする)
    vector<int> depth;//根からの深さ

    LCA(int V) {
        this->V = V;
        while (1 << MAX_LOG_V < V) {//バグが怖い
            MAX_LOG_V++;
        }
        G.resize(V);
        parent.resize(MAX_LOG_V, vector<int>(V));
        depth.resize(V);
    }

    /**
     * 辺を追加した後に初期化をする
     */
    void init() {
        //parentとdepthの初期化
        dfs(root, -1, 0);
        //parentを初期化する
        for (int k = 0; k + 1 < MAX_LOG_V; k++) {
            for (int v = 0; v < V; v++) {
                if (parent[k][v] < 0) parent[k + 1][v] = -1;
                else parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    void setRoot(int root_) {
        this->root = root_;
    }

    void dfs(int v, int p, int d) {
        parent[0][v] = p;
        depth[v] = d;
        for (int i = 0; i < G[v].size(); i++) {
            if (G[v][i] != p) dfs(G[v][i], v, d + 1);
        }
    }

    /**
     * uとvのlcaを求める
     * @param u 頂点
     * @param v 頂点
     * @return lcaとなる頂点
     */
    int lca(int u, int v) {
        //uとvの高さが同じになるまで親を辿る
        if (depth[u] > depth[v]) swap(u, v);
        for (int k = 0; k < MAX_LOG_V; k++) {
            if ((depth[v] - depth[u]) >> k & 1) {
                v = parent[k][v];
            }
        }
        if (u == v) return u;
        //二分探索でLCAを求める
        for (int k = MAX_LOG_V - 1; k >= 0; k--) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    /**
     * 辺を追加する
     * @param from 元
     * @param to 先
     */
    void add_edge(int from, int to) {
        G[from].push_back(to);
    }
};

