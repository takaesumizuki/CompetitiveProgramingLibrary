struct BFS01 {
    struct edge {
        ll to, cost;
    };
    typedef pair<ll, ll> P;//firstは最短距離、secondは頂点の番号

    int V;//超点数
    vector<vector<edge> > G;//グラフ,G[i]はiから出る辺の集合,G[i][j]はiから出る辺のj番目の辺
    vector<ll> d; //最短距離

    BFS01(int N) {
        V = N;
        G.resize(N);
        d = vector<ll>(N);
    };

    void addEdge(int from, int to, int cost) {
        edge e;
        e.to = to;
        e.cost = cost;
        G[from].push_back(e);
    }

    void calc(int s) {
//        priority_queue<P,vector<P>,greater<P> > que;
        deque<P> que;
        fill(d.begin(), d.end(), INFl);
        d[s] = 0;
        que.push_back(P(0, s));

        while (!que.empty()) {
            P p = que.front();
            que.pop_front();
            ll v = p.second;
            if (d[v] < p.first) continue;
            for (int i = 0; i < G[v].size(); i++) {
                edge e = G[v][i];
                if (d[e.to] > d[v] + e.cost && !(d[e.to] == INFl && d[v] == INFl)) {
                    d[e.to] = d[v] + e.cost;
                    if (e.cost == 0) {
                        que.push_front(P(d[e.to], e.to));
                    }else{
                        que.push_back(P(d[e.to],e.to));
                    }
                }
            }
        }

    }
};
