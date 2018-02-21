/**
 * priority_queを使用したダイクストラ法
 * 計算量はO(|E|log|V|)
 */

#ifndef CLION_PROCON_DIJKSTRA_PQ_H
#define CLION_PROCON_DIJKSTRA_PQ_H

#endif //CLION_PROCON_DIJKSTRA_PQ_H
struct edge{ll to,cost;};
typedef pair<ll,ll> P;//firstは最短距離、secondは頂点の番号

int V;//超点数
vector<vector<edge> > G;//グラフ
vector<ll> d; //最短距離

void dijkstra(int s){
    priority_queue<P,vector<P>,greater<P> > que;
    fill(d.begin(),d.end(),INFl);
    d[s] = 0;
    que.push(P(0,s));

    while(!que.empty()){
        P p = que.top();que.pop();
        ll v = p.second;
        if(d[v] < p.first) continue;
        for(int i = 0; i < G[v].size(); i++){
            edge e = G[v][i];
            if(d[e.to] > d[v] + e.cost){
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to],e.to));
            }
        }
    }

}


class Dijkstra{
public:
    struct edge{ll to,cost;};
    typedef pair<ll,ll> P;//firstは最短距離、secondは頂点の番号

    int V;//超点数
    vector<vector<edge> > G;//グラフ,G[i]はiから出る辺の集合,G[i][j]はiから出る辺のj番目の辺
    vector<ll> d; //最短距離

    //0origin
    Dijkstra(int N){
        V = N;
        G = vector<vector<edge> >(N);
        d = vector<ll>(N);
    };

    void dijkstra(int s){
        priority_queue<P,vector<P>,greater<P> > que;
        fill(d.begin(),d.end(),INFl);
        d[s] = 0;
        que.push(P(0,s));

        while(!que.empty()){
            P p = que.top();que.pop();
            ll v = p.second;
            if(d[v] < p.first) continue;
            for(int i = 0; i < G[v].size(); i++){
                edge e = G[v][i];
                if (d[e.to] > d[v] + e.cost && !(d[e.to] == INFl && d[v] == INFl)) {
                    d[e.to] = d[v] + e.cost;
                    que.push(P(d[e.to],e.to));
                }
            }
        }

    }
    /* 頂点fromに頂点toに達するコストcostの辺を貼る */
    void addEdge(int from,int to,int cost){
        edge e;
        e.to = to;
        e.cost = cost;
        G[from].push_back(e);
    }
};


//以下は使用例
/*
 int main() {
    int N;
    cin >> N;
    V = N;
    G = vector<vector<edge> >(N+1);
    d = vector<ll>(N+1);

    REP(i,1,N){
        int a,b,c;
        cin >> a >> b >> c;
        edge e;
        e.to = b;
        e.cost = c;
        G[a].push_back(e);
        e.to = a;
        G[b].push_back(e);
    }
    int Q,K;
    cin >> Q >> K;
    dijkstra(K);
    REP(i,0,Q){
        int x,y;
        cin >> x >> y;
        cout << d[x] + d[y] << endl;
    }

    return 0;
}
 */