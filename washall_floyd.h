//
// Created by たかえすみずき on 2017/10/08.
//

#ifndef CLION_PROCON_WASHALL_FLOYD_H
#define CLION_PROCON_WASHALL_FLOYD_H

#endif //CLION_PROCON_WASHALL_FLOYD_H
vector<vector<int> > G;//頂点iからjまでのグラフが入る,1beginの仕様,普通のワーシャルフロイドでは使わない。
vector<vector<int> > d;//頂点iからjまでの最短距離,間に編がない場合はINFが入る。
int V;//超点数

//1beginの場合
void washall() {
    for (int k = 1; k <= V; k++) {
        for (int i = 1; i <= V; i++) {
            for (int j = 1; j <= V; j++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

//0beginの場合
void washall() {
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (d[i][j] > d[i][k] + d[k][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}