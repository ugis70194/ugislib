#include<cstdint>
#include<random>
#include<vector>
#include<algorithm>

template<typename T>
class RandomizedQueue{
private:
    std::random_device seed_gen;
    std::mt19937_64 rng;
    std::vector<T> que;
    uint_fast64_t len;
public:
    RandomizedQueue() : len(0), rng(seed_gen()) {}

    RandomizedQueue(int_fast64_t begin, int_fast64_t end) : len(end - begin + 1), rng(seed_gen()){
        que.reserve(end - begin + 1);
        for(int_fast64_t i = begin; i <= end; i++){
            que.emplace_back(i);
        }
    }

    void push(T n){
        que[len] = n;
        len++;
    }

    T pop(){
        int_fast64_t idx = rng() % len;
        int_fast64_t res = que[idx];
        std::swap(que[idx], que[len-1]);
        len--;
    }

    uint_fast64_t size() {
        return size;
    }
};