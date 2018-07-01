struct RootedTree {
    vector <vector<int>> tree;
    vector<int> depth; //木の深さ
    vector<int> depthHash; //木の深さに対応したハッシュ値
    int size;
    int root = 0;
    unsigned int y = 2463534242; //乱数

    const int mod = MOD; //計算で使用するmod

    RootedTree(vector <vector<int>> tree) : tree(tree) {
        size = tree.size();
        depth.resize(size);
        depthHash.resize(size, -1);
    }

    /**
     * 根をrootとして木を代入する
     * @param tree
     * @param root
     */
    RootedTree(vector <vector<int>> tree, int root) : tree(tree), root(root) {
        size = tree.size();
        depth.resize(size);
        depthHash.resize(size, -1);
    }


    /**
     * 根をrootとして木を代入する
     * seedも指定
     * @param tree
     * @param root
     * @param seed
     */
    RootedTree(vector <vector<int>> tree, int root, unsigned seed) : tree(tree), root(root), y(seed) {
        size = tree.size();
        depth.resize(size);
        depthHash.resize(size, -1);
    }

    /**
     * 乱数を求める
     * @return
     */
    unsigned rnd(void) {
        y = y ^ (y << 13);
        y = y ^ (y >> 17);
        return y = y ^ (y << 5);
    }

    /**
     * 木の深さをセットする
     * 葉っぱの深さは1
     * 仕様するときは
     * @param n
     * @return
     */
    int setDepth(int n) {
        if (tree[n].size() == 0) return depth[n] = 1;
        int ret = -1;
        for (auto e : tree[n]) {
            int tmp = setDepth(e) + 1;
            if (ret < tmp) ret = tmp;
        }
        return depth[n] = ret;
    }

    /**
     * 木の深さをセットする
     */
    void setDepth() {
        setDepth(root);
    }

    /**
     * 頂点の深さに対応したハッシュ値を求める
     */
    void setDepthHash() {
        for (int i = 0; i < size; i++) {
            depthHash[i] = rnd() % mod;
        }
    }

    ll calcTreeHash(int n) {
        ll ret = 1ll;

        if (tree[n].size() == 0) return 1;
        for (auto e : tree[n]) {
            ret = ret * (depthHash[depth[n]] + calcTreeHash(e)) % mod;
        }

        return ret;
    }

    /**
     * 木のハッシュ値を求める
     * @return
     */
    int calcTreeHash() {
        return (int) calcTreeHash(root);
    }

    /**
     * 必要な作業をする
     */
    void doAll() {
        setDepth();
        setDepthHash();
    }


};

/**
 * ２つの根付き木を与えるとどう同値かどうかを判定してくれる関数
 * @param tree1 木
 * @param tree2 木
 * @return
 */
bool isIsomophic(vector <vector<int>> tree1, int root1, vector <vector<int>> tree2, int root2) {
    RootedTree treeone(tree1, root1);
    treeone.doAll();
    RootedTree treetwo(tree2, root2);
    treetwo.doAll();

    return treeone.calcTreeHash() == treetwo.calcTreeHash();

}

