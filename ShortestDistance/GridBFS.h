struct GridBFS {
    vector<vector<int> > mat;
    int H, W;

    GridBFS(int h, int w) {
        H = h;
        W = w;
        mat.resize(H, vector<int>(W, INF));
    }

    void setFloor(int h, int w) {
        mat[h][w] = 0;
    }

    void setWall(int h, int w) {
        mat[h][w] = -1;
    }

    void init(int h, int w) {
        H = h;
        W = w;
        mat.resize(H, vector<int>(W, INF));
    }

    int get(int h, int w) {
        return mat[h][w];
    }

    bool check(int h, int w) {
        return h < H && h >= 0 && w < W && w >= 0;
    }

    /**
     *
     * @param sh スタートのhの座標
     * @param sw スタートのwの座標
     */
    void calc(int sh, int sw) {
        typedef pair<int, int> P;
        queue<pair<int, int> > que;
        que.push(P(sh, sw));
        mat[sh][sw] = 0;
        int dh[] = {0, 1, 0, -1};
        int dw[] = {1, 0, -1, 0};
        while (!que.empty()) {
            int h = que.front().first;
            int w = que.front().second;
            que.pop();
            for (int i = 0; i < 4; i++) {
                int newH = h + dh[i];
                int newW = w + dw[i];
                if (check(newH, newW) && this->get(newH, newW) != 0 && this->get(newH, newW) > this->get(h, w) + 1) {
                    mat[newH][newW] = mat[h][w] + 1;
                    que.push(P(newH, newW));
                }
            }
        }
    }
};
