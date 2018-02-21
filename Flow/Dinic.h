class Flow {
public:
    struct edge {
        int to, cap, rev;
    };
    vector<vector<edge> > G;
    vector<bool> used;
    vector<int> level;//sからの距離
    vector<int> iter;//どこまで調べ終わったか

    //0 ~ maxSize-1 のフローを構築できるようにする
    explicit Flow(unsigned maxSize) {
        G.resize(maxSize, vector<edge>());
        used.resize(maxSize, false);
        level.resize(maxSize, 0);
        iter.resize(maxSize, 0);
    }

    void add_edge(int from, int to, int cap) {
        G[from].push_back((edge) {to, cap, (int) G[to].size()});
        G[to].push_back((edge) {from, 0, (int) G[from].size() - 1});
    }

    //sからの最短距離をDFSで探す
    void bfs(int s) {
//        memset(level, -1, sizeof(level));
        fill(level.begin(),level.end(),-1);
        queue<int> que;
        level[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int i = 0; i < G[v].size(); i++) {
                edge &e = G[v][i];
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    que.push(e.to);
                }
            }
        }
    }

    //増加パスを探す
    int dfs(int v, int t, int f) {
        if (v == t) return f;
        for (int &i = iter[v]; i < G[v].size(); i++) {
            edge &e = G[v][i];
            if (e.cap > 0 && level[v] < level[e.to]) {
                int d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    //sからtへの最大流を求める
    int max_flow(int s, int t) {
        int flow = 0;
        for (;;) {
            bfs(s);
            if (level[t] < 0) return flow;
//            memset(iter, 0, sizeof(iter));
            fill(iter.begin(),iter.end(),0);
            int f;
            while ((f = dfs(s, t, INF)) > 0) {
                flow += f;
            }
        }
    }

};