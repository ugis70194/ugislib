#include<cstdint>
#include<random>
#include<vector>
#include<algorithm>
#include<cassert>

template<typename T>
class RandomizedQueue{
private:
    std::random_device seed_gen;
    std::mt19937_64 rng;
    std::vector<T> que;
    size_t len;
public:
    RandomizedQueue() : len(0), rng(seed_gen()) {}
    RandomizedQueue(std::vector<T>& vec) : rng(seed_gen()){
        que = vec;
        len = que.size();
    }
    RandomizedQueue(size_t begin, size_t end) : len(end - begin + 1), rng(seed_gen()){
        que.reserve(end - begin + 1);
        for(size_t i = begin; i <= end; ++i){
            que.emplace_back(i);
        }
    }

    void push(T n){
        if(len + 1 > que.size()) que.resize(2*que.size());
        que[len] = n;
        ++len;
    }

    void push(size_t begin, size_t end){
        if(len + (end-begin+1) > que.size()) que.resize(2*(len+(end-begin+1)));
        for(size_t i = begin; i <= end; ++i){
            que[len] = i;
            len++;
        }
    }

    void push(std::vector<T>& vec){
        if(len + vec.size() > que.size()) que.resize(2*(len+vec.size()));
        for(size_t i = 0; i < vec.size(); ++i){
            que[len] = vec[i];
            ++len;
        }
    }

    T pop(){
        assert(len > 0);
        size_t idx = rng() % len;
        std::swap(que[idx], que[len-1]);
        --len;
        if(len < que.size() / 3) que.resize(que.size() / 2);
        return que[len];
    }

    size_t size() {
        return size;
    }
};