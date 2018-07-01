/**
 * priority_queを使用したダイクストラ法
 * 計算量はO(|E|log|V|)
 */
class Dijkstra {
public:
    using T = long long int;
    typedef pair<T, int> P; //firstは最短距離、secondは頂点の番号
    const T inf = (T) 5e15;
    struct edge {
        int to;
        T cost;
    };

    int V;                  //超点数
    vector <vector<edge>> G; //グラフ,G[i]はiから出る辺の集合,G[i][j]はiから出る辺のj番目の辺
    vector <T> d;           //最短距離

    //0origin
    Dijkstra(int N) {
        V = N;
        G = vector < vector < edge >> (N);
        d = vector<T>(N);
    };

    void dijkstra(int s) {
        priority_queue <P, vector<P>, greater<P>> que;
        fill(d.begin(), d.end(), inf);
        d[s] = 0;
        que.push(P(0, s));

        while (!que.empty()) {
            P p = que.top();
            que.pop();
            int v = p.second;
            if (d[v] < p.first)
                continue;
            for (int i = 0; i < G[v].size(); i++) {
                edge e = G[v][i];
                if (d[e.to] > d[v] + e.cost && !(d[e.to] == inf && d[v] == inf)) {
                    d[e.to] = d[v] + e.cost;
                    que.push(P(d[e.to], e.to));
                }
            }
        }
    }

    /* 頂点fromに頂点toに達するコストcostの辺を貼る */
    void addEdge(int from, int to, T cost) {
        edge e;
        e.to = to;
        e.cost = cost;
        G[from].push_back(e);
    }

    T getDist(int v) {
        return d[v];
    }
};
