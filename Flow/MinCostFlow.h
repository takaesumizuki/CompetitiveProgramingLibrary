class MinCostFlow {
    typedef pair<int, int> P;
    struct edge {
        int to, cap, cost, rev;
    };
public:
    int V;//頂点数
    vector<vector<edge>> G;//グラフ
    vector<int> h; //ポテンシャル
    vector<int> dist; //最短距離
    vector<int> prevv, preve;//直前の頂点と辺

    MinCostFlow(int V) {
        this->V = V;
//        G.resize(V,vector<edge>());
        G.resize(V);
        h.resize(V);
        dist.resize(V);
        prevv.resize(V);
        preve.resize(V);
    }

    void add_edge(int from, int to, int cap, int cost) {
        G[from].push_back((edge) {to, cap, cost, (int) G[to].size()});
        G[to].push_back((edge) {from, 0, -cost, (int) G[from].size() - 1});
    }

    //流せない場合は-1を返す
    int min_cost_flow(int s, int t, int f) {
        int res = 0;
        fill(h.begin(), h.end(), 0);
        while (f > 0) {
            priority_queue<P, vector<P>, greater<P> > que;
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            que.push(P(0, s));
            while (!que.empty()) {
                P p = que.top();
                que.pop();
                int v = p.second;
                if (dist[v] < p.first) continue;
                for (int i = 0; i < G[v].size(); i++) {
                    edge &e = G[v][i];
                    if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        prevv[e.to] = v;
                        preve[e.to] = i;
                        que.push(P(dist[e.to], e.to));
                    }
                }
            }


            if (dist[t] == INF) return -1;

            for (int v = 0; v < V; v++) h[v] += dist[v];

            int d = f;
            for (int v = t; v != s; v = prevv[v]) {
                d = min(d, G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            res += d * h[t];

            for (int v = t; v != s; v = prevv[v]) {
                edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return res;
    }
};

