#include<vector>
#include<cmath>
#include<map>
#include<queue>


std::vector<int> SieveofEratosthenes(int N){
    std::vector<bool> is_prime(N+1,true);
    std::vector<int> prime;
    prime.reserve(N);
    is_prime[0] = is_prime[1] = false;
    for(int i=2;i<=N;i+=2) is_prime[i] = false;
    is_prime[2] =  true;
    prime.emplace_back(2);

    for(int i=3;i<=sqrt(N);++i){
        if(!is_prime[i]) continue;
        for(int j = i*2; j<=N;j*=2){
            is_prime[j] = false;
        }
    }

    for(int i=3;i<=N;++i) if(is_prime[i]) prime.emplace_back(i);

    return prime;
}

bool prime_number_determination(int p){
    bool is_prime = true;
    for(int j=2;j*j<=p;++j){
        if(p % j == 0){
            is_prime = false;
            break;
        }
    }
    return is_prime;
}


