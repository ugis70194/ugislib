#include<vector>
#include<algorithm>
#include<cstdint>

//RMQ
class SegmentTree{
private:
    using Int = int_fast64_t;
    std::vector<Int> arr;
    size_t size;
    const Int INF = (1ll << 31) - 1ll;
public:
    SegmentTree(size_t range){
        size = 1;
        while(size < range) size <<= 1;
        arr.assign(2*size-1, INF);
    }
    SegmentTree(const std::vector<Int>& vec){
        size = 1;
        while(size < vec.size()) size <<= 1;
        arr.assign(2*size-1, INF);
        for(size_t i = 0; i < vec.size(); ++i) arr[i+size-1] = vec[i];
        for(Int i = size-2; i >= 0; --i) arr[i] = std::min(arr[2*i+1], arr[2*i+2]);
    }
    
    void update(size_t idx, Int value){
        idx += (size - 1);
        arr[idx] = value;
        while(idx > 0){
            idx = (idx-1) / 2;
            arr[idx] = std::min(arr[2*idx+1], arr[2*idx+2]);
        }
    }

    Int minQuery(size_t L, size_t R, size_t idx=0, size_t l=0, size_t r=1e9+7){
        if(r > 1e9) r = size;

        if(r <= L || R <= l) return INF;
        if(L <= l && r <= R) return arr[idx];

        Int MIN = INF;
        MIN = std::min(minQuery(L, R, 2*idx+1, l, (l+r)/2), MIN);
        MIN = std::min(minQuery(L, R, 2*idx+2, (l+r)/2,r), MIN);
        return MIN;
    }
};