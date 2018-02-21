struct BIT{
    vector<int> bit;
    int n;
    /*
     * 1 ~ nまでのBITを作る
     */
    BIT(int n){
        bit.resize(n+1,0);
        this->n = n;
    }
    int sum(int i){
        int s = 0;
        while(i > 0){
            s += bit[i];
            i -= i & -i;
        }
        return s;
    }
    void add(int i,int x){
        while(i <= n){
            bit[i] += x;
            i += i & -i;
        }
    }
};