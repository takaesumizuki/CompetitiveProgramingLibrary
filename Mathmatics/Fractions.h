struct Bunsuu {
    using T = ll;
    T p, q;

    Bunsuu(T p_, T q_) : p(p_), q(q_) {

    }

    Bunsuu(pair<T, T> aPair) : p(aPair.first), q(aPair.second) {

    }

    Bunsuu operator+(Bunsuu right) {
        T bunbo = q * right.q;
        T bunshi = p * right.q + right.p * q;
        return Bunsuu(yakubun(bunshi, bunbo));
    }

    Bunsuu operator-(Bunsuu right) {
        T bunbo = q * right.q;
        T bunshi = p * right.q - right.p * q;
        return Bunsuu(yakubun(bunshi, bunbo));
    }

    Bunsuu operator*(Bunsuu right) {
        T bunbo = q * right.q;
        T bunshi = p * right.p;
        return Bunsuu(yakubun(bunshi, bunbo));
    }

    Bunsuu operator/(Bunsuu right) {
        T bunbo = q * right.p;
        T bunshi = p * right.q;
        return Bunsuu(yakubun(bunshi, bunbo));
    }

    void print() {
        cout << p << "/" << q << endl;
    }

    ll gcd(ll a, ll b) {
        a = abs(a);
        b = abs(b);
        if (a < b) swap(a, b);
        if (a % b == 0) return b;

        return gcd(b, a % b);
    }

    pair<T, T> yakubun(T p, T q) {
        if (p == 0)return pair<T, T>(0ll, 1ll);
        T gcd_v = gcd(p, q);
        p /= gcd_v;
        q /= gcd_v;
        return pair<T, T>(p, q);
    }

    double value() {
        return 1.0 * p / q;
    }
};

