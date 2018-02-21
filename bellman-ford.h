//
// Created by たかえすみずき on 2017/10/10.
//

#ifndef CLION_PROCON_BELLMAN_FORD_H
#define CLION_PROCON_BELLMAN_FORD_H

#endif //CLION_PROCON_BELLMAN_FORD_H

/*
 * ベルマンフォード方法による最短路問題
 * 0originであることに注意
 *                                 */
struct edge {int from,to;ll cost;};
vector<edge> es; // 辺
vector<ll> d; //最短距離,0で初期化してね
int V,E;//頂点数と辺の数

bool find_negative_loop(int s){
    //dはINFで初期化しておく
    d[s] = 0;
    for(int i = 0; i < V; i++){
        for(int j = 0; j < E; j++){
            edge e = es[j];
            if(d[e.to] > d[e.from] + e.cost){
                d[e.to] = d[e.from] + e.cost;
                if(i == V - 1) return true;
            }
        }
    }
    return false;
}
