//Ford-Fulkerson法
//O(F|E|) ただしFは最大流量
class Flow{
public:
    struct edge{int to,cap,rev;};
    vector<vector<edge> > G;
    vector<bool> used;

    //0 ~ maxSize-1 のフローを構築できるようにする
    explicit Flow(unsigned maxSize){
        G.resize(maxSize,vector<edge>());
        used.resize(maxSize,false);
    }

    void add_edge(int from,int to,int cap){
        G[from].push_back((edge){to,cap,(int)G[to].size()});
        G[to].push_back((edge){from,0,(int)G[from].size()-1});
    }

    //増加パスを探す
    int dfs(int v,int t,int f){
        if(v == t) return f;
        used[v] = true;
        for(int i = 0; i < G[v].size(); i++){
            edge &e = G[v][i];
            if(!used[e.to] && e.cap > 0){
                int d = dfs(e.to,t,min(f,e.cap));
                if(d > 0){
                    e.cap -= d;
                    G[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }

    int max_flow(int s,int t){
        int flow = 0;
        for(;;){
            rep(i,0,used.size()) used[i] = false;
            int f = dfs(s,t,INF);
            if(f == 0) return flow;
            flow += f;
        }
    }

};