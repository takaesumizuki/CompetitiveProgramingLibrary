//
// Created by たかえすみずき on 2017/10/26.
//

#ifndef CLION_PROCON_EDITDISTANCE_H
#define CLION_PROCON_EDITDISTANCE_H

#endif //CLION_PROCON_EDITDISTANCE_H


/**
 *
 * @param str1
 * @param str2
 * @return 編集距離
 */
int editDistance(string str1, string str2) {
    vector <vector<int>> dp(str1.size() + 1, vector<int>(str2.size() + 1, 0));
    for (int i = 0; i < str1.size() + 1; i++) {
        dp[i][0] = 0;
    }

    for (int i = 0; i < str2.size() + 1; i++) {
        dp[0][i] = 0;
    }

    for (int i = 1; i < str1.size() + 1; i++) {
        for (int j = 1; j < str2.size() + 1; j++) {
            if (str1[i - 1] == str2[j - 1])
                dp[i][j] = min({dp[i - 1][j - 1] + 0, dp[i - 1][j] + 1, dp[i][j - 1] + 1});
            else dp[i][j] = min({dp[i - 1][j - 1] + 1, dp[i - 1][j] + 1, dp[i][j - 1] + 1});
        }
    }
    return dp[str1.size()][str2.size()];
}
