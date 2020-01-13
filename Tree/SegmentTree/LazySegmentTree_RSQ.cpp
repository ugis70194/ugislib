#include<vector>
#include<algorithm>
#include<cstdint>
//RAQ 
class LazySegmentTree{
private:
    using Int = int_fast64_t;
    std::vector<Int> arr;
    std::vector<Int> lazy;
    size_t size;
public:
    LazySegmentTree(size_t range){
        size = 1;
        while(size < range) size <<= 1;
        arr.assign(2*size-1, 0);
        lazy.assign(2*size-1, 0);
    }
    LazySegmentTree(const std::vector<Int>& vec){
        size = 1;
        while(size < vec.size()) size <<= 1;
        arr.assign(2*size-1, 0);
        lazy.assign(2*size-1, 0);
        for(size_t i = 0; i < vec.size(); ++i) arr[i+size-1] = vec[i];
        for(Int i = size-2; i >= 0; --i) arr[i] = arr[2*i+1] + arr[2*i+2];
    }

    void eval(size_t idx, size_t l, size_t r){
        if(lazy[idx] == 0) return;
        //arr[idx] += lazy[idx];
        arr[idx] += lazy[idx] * (r - l);
        if(r - l > 1){
            lazy[2*idx+1] += lazy[idx];// / 2;
            lazy[2*idx+2] += lazy[idx];// / 2;
        };
        lazy[idx] = 0;
    }

    void add(size_t L, size_t R, Int x, size_t idx=0, size_t l=0, size_t r=1e9+7){
        if(r > 1e9) r = size;

        eval(idx, l, r);
        if(r <= L || R <= l) return;
        if(L <= l && r <= R) {
            lazy[idx] += (r - l) * x;
            eval(idx, l, r);
        } else {
            add(L, R, x, 2*idx+1, l, (l+r)/2);
            add(L, R, x, 2*idx+2, (l+r)/2, r);
            arr[idx] = arr[2*idx+1] + arr[2*idx+2];
        }
    }

    Int sumQuery(size_t L, size_t R, size_t idx=0, size_t l=0, size_t r=1e9+7){
        if(r > 1e9) r = size;
        if(r <= L || R <= l) return 0;

        eval(idx ,l ,r);
        if(L <= l && r <= R) return arr[idx];
        Int sum = 0;
        sum += sumQuery(L, R, 2*idx+1, l, (l+r)/2);
        sum += sumQuery(L, R, 2*idx+2, (l+r)/2,r);
        return sum;
    }
};