//
// Created by たかえすみずき on 2017/11/13.
//
// RMQ ver1.0

//Range Minimum Query
//セグ木(最小値ver)
class RMQ {
public:
    const int MAX_N = 1 << 17;
    int n;
    vector<int> dat;

    RMQ(int n_) {
        init(n_);

    }

    void init(int n_) {
        n = 1;
        while (n < n_) n *= 2;
        dat = vector<int>(2 * n);
        for (int i = 0; i < 2 * n - 1; ++i) dat[i] = INT_MAX;
    }

    //k番目の値(0-indexed)をaに変更
    void update(int k, int a) {
        k += n - 1;
        dat[k] = a;
        //登りながら更新
        while (k > 0) {
            k = (k - 1) / 2;
            dat[k] = min(dat[k * 2 + 1], dat[k * 2 + 2]);
        }
    }

    //[a,b)の最小値を求める
    //kは接点の番号,l,rはその接点が[l,r)に対応づいていることを表す。
    //したがって、外からはquery(a,b,0,0,n)として呼ぶ。
    int query(int a, int b, int k, int l, int r) {
        //[a,b)と[l,r)が交差しなければINT_MAX
        if (r <= a || b <= l) return INT_MAX;

        //[a,b)が[l,r)が交差しなければ、INT_MAX
        if (a <= l && r <= b) return dat[k];
        else {
            //そうでなければ、2つの子の最小値
            int vl = query(a, b, k * 2 + 1, l, (l + r) / 2);
            int vr = query(a, b, k * 2 + 2, (l + r) / 2, r);
            return min(vl,vr);
        }
    }

    //[a,b)の最小値を求める
    int find(int a,int b){
        return query(a,b,0,0,n);
    }
};
