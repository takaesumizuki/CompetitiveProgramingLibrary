// RMQ ver1.0

//
// Created by たかえすみずき on 2017/11/13.
//
//Range Minimum Query
//セグ木(ver1.2)
class SegTree {
public:
    const int MAX_N = 1 << 17;
    int n;
    vector<ll> dat;
    const ll INITIAL_DAT = 0L;
    SegTree(int n_) {
        init(n_);
    }

    void init(int n_) {
        n = 1;
        while (n < n_) n *= 2;
        dat = vector<ll>(2 * n);
        for (int i = 0; i < 2 * n - 1; ++i) dat[i] = INITIAL_DAT;
    }

    //どんなSegTreeを構築するか(デフォルトはRMQ)
    ll calc(ll vl,ll vr){
        return min(vl,vr);
    }

    //k番目の値(0-indexed)をaに変更
    void update(int k, int a) {
        k += n - 1;
        dat[k] = a;
        //登りながら更新
        while (k > 0) {
            k = (k - 1) / 2;
//            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
            dat[k] = calc(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    //[a,b)の最小値を求める
    //kは接点の番号,l,rはその接点が[l,r)に対応づいていることを表す。
    //したがって、外からはquery(a,b,0,0,n)として呼ぶ。
    ll query(int a, int b, int k, int l, int r) {
        //[a,b)と[l,r)が交差しなければINITIAL_DAT
        if (r <= a || b <= l) return INITIAL_DAT;

        //[a,b)が[l,r)が交差しなければ、INT_MAX
        if (a <= l && r <= b) return dat[k];
        else {
            //そうでなければ、2つの子に対する処理,デフォルトは最小値
            ll vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            ll vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return calc(vl,vr);
        }
    }

    //[a,b)の最小値を求める
    ll find(int a,int b){
        return query(a,b,0,0,n);
    }
};
