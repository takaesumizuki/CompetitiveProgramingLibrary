// RSQ ver1.0

//
// Created by たかえすみずき on 2017/3/17.
//
//Range Sum Query
//セグ木(ver1.2)
/**
 * verified 2017/3/17
 * https://onlinejudge.u-aizu.ac.jp/#/courses/library/3/DSL/2/DSL_2_E
 *
 *
 */
class SegTree {
public:
    int n;
    vector<ll> data, datb;
    const ll INITIAL_DAT = 0L;

    SegTree(int n_) {
        init(n_);
    }

    void init(int n_) {
        n = 1;
        while (n < n_) n *= 2;
        data = vector<ll>(2 * n);
        datb = vector<ll>(2 * n);
        for (int i = 0; i < 2 * n - 1; ++i) data[i] = datb[i] = INITIAL_DAT;
    }

    //どんなSegTreeを構築するか
    ll calc(ll vl, ll vr) {
        return vl + vr;
    }

    //[a,b)にkを加算する。
    //外部から呼び出すときはadd(a,b,x,0,0,セグのsize)で
    void add(int a, int b, int x, int k, int l, int r) {
        if (a <= l && r <= b) {
            data[k] += x;
        } else if (l < b && a < r) {
            datb[k] += (min(b, r) - max(a, l)) * x;
            add(a, b, x, k * 2 + 1, l, (l + r) / 2);
            add(a, b, x, k * 2 + 2, (l + r) / 2, r);
        }
    }
    void add(int a,int b,int x){
        add(a,b,x,0,0,n);
    }

    //[a,b)の合計値を求める
    //kは接点の番号,l,rはその接点が[l,r)に対応づいていることを表す。
    //したがって、外からはquery(a,b,0,0,n)として呼ぶ。
    ll query(int a, int b, int k, int l, int r) {
        //[a,b)と[l,r)が交差しなければINITIAL_DAT
        if (r <= a || b <= l) return INITIAL_DAT;

        //[a,b)が[l,r)が交差しなければ、INT_MAX
        if (a <= l && r <= b) return data[k] * (r - l) + datb[k];
        else {
            //そうでなければ、2つの子に対する処理,デフォルトは最小値
            ll res = (min(b, r) - max(a, l)) * data[k];
            res += query(a, b, k * 2 + 1, l, (l + r) / 2);
            res += query(a, b, k * 2 + 2, (l + r) / 2, r);
            return res;
        }
    }

    //[a,b)の合計値を求める
    ll sum(int a, int b) {
        return query(a, b, 0, 0, n);
    }
};

