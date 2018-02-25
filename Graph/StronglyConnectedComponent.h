struct SCC {
    int V;
    vector<vector<int> > G;//グラフの隣接リスト表現
    vector<vector<int> > rG;//変の向きを逆にしたグラフ
    vector<int> vs;//帰りがけ順の並び
    vector<bool> used;//既に調べたか
    vector<int> cmp;//属する共連結成分のトポロジカル順序

    SCC(int v) {
        V = v;
        G.resize(V);
        rG.resize(V);
        used.resize(V);
        cmp.resize(V);
    }

    /**
     * 辺を貼る
     * @param from 辺の元
     * @param to 辺の先
     */
    void add_edge(int from, int to) {
        G[from].push_back(to);
        rG[to].push_back(from);
    }

    void dfs(int v) {
        used[v] = true;
        for (int i = 0; i < G[v].size(); i++) {
            if (!used[G[v][i]]) dfs(G[v][i]);
        }
        vs.push_back(v);
    }


    void rdfs(int v, int k) {
        used[v] = true;
        cmp[v] = k;
        for (int i = 0; i < rG[v].size(); i++) {
            if (!used[rG[v][i]]) rdfs(rG[v][i], k);
        }
    }

    int scc() {
        fill(used.begin(), used.end(), false);
        vs.clear();
        for (int v = 0; v < V; v++) {
            if (!used[v]) dfs(v);
        }
        fill(used.begin(), used.end(), false);
        int k = 0;
        for (int i = vs.size() - 1; i >= 0; i--) {
            if (!used[vs[i]]) rdfs(vs[i], k++);
        }
        return k;
    }
};
