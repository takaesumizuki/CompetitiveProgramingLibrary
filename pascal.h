//
// Created by たかえすみずき on 2017/09/28.
//

#ifndef CLION_PROCON_PASCAL_H
#define CLION_PROCON_PASCAL_H

#endif //CLION_PROCON_PASCAL_H
#define REP(i, m, n) for(int i=int(m);i<int(n);i++)
#define MAX_PAS 50 //最大の第一引数
ll pascal[MAX_PAS + 1][MAX_PAS + 1];

void calcPascal() {
    REP(i, 1, MAX_PAS + 1) {
        pascal[i][i] = 1;
        pascal[i][0] = 1;
    }
    REP(i, 1, MAX_PAS + 1) {
        REP(j, 1, i) {
            if (pascal[i][j] == 0)pascal[i][j] = pascal[i - 1][j - 1] + pascal[i - 1][j];
        }
    }
}
