//
// Created by たかえすみずき on 2017/09/12.
//

#ifndef CLION_PROCON_PRIMES_H
#define CLION_PROCON_PRIMES_H

#endif //CLION_PROCON_PRIMES_H


#define REP(i, m, n) for(int i=int(m);i<int(n);i++)


void primes() {
    bool prime[1001];
    vector<int> primes;

    REP(i, 0, 1001) {
        prime[i] = true;
    }
    prime[0] = false;
    prime[1] = false;
    for (int i = 2; i <= 1000; i++) {
        if (prime[i]) {
            for (int j = i * 2; j <= 1000; j += i) {
                prime[j] = false;
            }
        }
    }
    REP(i, 0, 1001) {
        if (prime[i]) primes.push_back(i);
    }
    vector<int> pows(primes.size());
}

bool isPrime(int num){
    if(num == 2) return true;
    for(int i = 3; i * i <= num; i += 2){
        if(num % i == 0) return false;
    }
    return true;
}