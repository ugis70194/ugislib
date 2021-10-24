#include<map>

std::map<int,int> Pfact(int N){
    std::map<int,int> factor;
    int M = N;
    for(int i = 2; i*i <= M; i++){
        while(N % i == 0) {
            factor[i]++;
            N /= i;
        }
    }
    if(N != 1) factor[N]++;

    return factor;
}

    