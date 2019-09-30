#include <vector>
std::vector<int> Enumeration_diviser(int N){
    std::vector<int> diviser;
    for(int i=1;i*i<=N;++i){
        if(N % i == 0){
            diviser.emplace_back(i);
            diviser.emplace_back(N/i);
        }
    }
    return diviser;
}
