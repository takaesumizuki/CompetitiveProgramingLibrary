/**
 * beetしゃんの抽象セグ木
 * ここ参照
 * http://beet-aizu.hatenablog.com/entry/2017/12/01/225955
 *

 ↓使える条件
 g(f(a,b),c)=f(g(a,c),g(b,c)) (a,b∈T,c∈E)
 g(g(a,b),c)=g(a,h(b,c)) (a∈T,b,c∈E)
 e を E の単位元とすると、 g(a,e)=a (a∈T)

 区間に対して更新となると以下の条件も加わる
 g(f(a,b),p(c,d))=f(g(a,p(c,d/2)),g(b,p(c,d/2))) (a,b∈T,c∈E,d∈ℕ)

 */
/*
 *  ↓便利スニペット
    using T = int;
    using E = int;
    auto f = [](T a, T b){return a + b;}; // 要素と要素のマージ
    auto g = [](T a, E b){return a + b;}; // 要素に作用素を作用
    auto h = [](E a, E b){return a + b;}; // 作用素と作用素をマージ
    auto p = [](E a, int b){return a * b;}; // 作用素を区間加算する場合
    T ti = 0; //要素の単位元?
    E ei = 0; //作用素の単位元?
    SegmentTree<T,E> treeone(n,f,g,h,ti,ei,p);
 */
template <typename T,typename E>
struct SegmentTree{
    using F = function<T(T,T)>;
    using G = function<T(T,E)>;
    using H = function<E(E,E)>;
    using P = function<E(E,size_t)>;
    int n;
    F f; //要素と要素のマージ
    G g; //要素に作用素を作用
    H h; //作用素と作用素をマージ
    T ti; //要素の単位元?
    E ei; //作用素の単位元?
    P p; //b個の作用素aをマージした場合
    vector<T> dat;
    vector<E> laz;
    SegmentTree(int n_,F f,G g,H h,T ti,E ei,
                P p=[](E a,size_t b){b++;return a;}):
            f(f),g(g),h(h),ti(ti),ei(ei),p(p){
        init(n_);
    }
    void init(int n_){
        n=1;
        while(n<n_) n*=2;
        dat.assign(2*n-1,ti);
        laz.assign(2*n-1,ei);
    }
    void build(int n_, vector<T> v){
        for(int i=0;i<n_;i++) dat[i+n-1]=v[i];
        for(int i=n-2;i>=0;i--)
            dat[i]=f(dat[i*2+1],dat[i*2+2]);
    }
    inline void eval(int len,int k){
        if(laz[k]==ei) return;
        if(k*2+1<n*2-1){
            laz[k*2+1]=h(laz[k*2+1],laz[k]);
            laz[k*2+2]=h(laz[k*2+2],laz[k]);
        }
        dat[k]=g(dat[k],p(laz[k],len));
        laz[k]=ei;
    }
    T update(int a,int b,E x,int k,int l,int r){
        eval(r-l,k);
        if(r<=a||b<=l) return dat[k];
        if(a<=l&&r<=b){
            laz[k]=h(laz[k],x);
            return g(dat[k],p(laz[k],r-l));
        }
        return dat[k]=f(update(a,b,x,k*2+1,l,(l+r)/2),
                        update(a,b,x,k*2+2,(l+r)/2,r));
    }
    T update(int a,int b,E x){
        return update(a,b,x,0,0,n);
    }
    T query(int a,int b,int k,int l,int r){
        eval(r-l,k);
        if(r<=a||b<=l) return ti;
        if(a<=l&&r<=b) return dat[k];
        T vl=query(a,b,k*2+1,l,(l+r)/2);
        T vr=query(a,b,k*2+2,(l+r)/2,r);
        return f(vl,vr);
    }
    T query(int a,int b){
        return query(a,b,0,0,n);
    }
    /**
     * kをxに更新する
     */
    void update(int k,T x){
        query(k,k+1);//evaluate
        k+=n-1;
        dat[k]=x;
        while(k){
            k=(k-1)/2;
            dat[k]=f(dat[k*2+1],dat[k*2+2]);
        }
    }
};

