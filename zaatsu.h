template<typename T>
vector<int> zaatsu(vector <T> v) {
    map<T, int> mp;
    vector <T> w = v;
    sort(all(w));
    int cnt = 0;
    for (int i = 0; i < w.size(); i++) {
        if (mp.find(w[i]) == mp.end()) {
            mp[w[i]] = ++cnt;
        }
    }
    vector<int> ret(v.size());

    for (int i = 0; i < v.size(); i++) {
        ret[i] = mp[v[i]];
    }
    return ret;
}
