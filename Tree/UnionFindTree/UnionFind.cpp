#include<vector>
#include<algorithm>
#include<cstdint>

class UnionFind{
private:
    using uint = std::uint_fast64_t;
    std::vector<uint> par;
    std::vector<uint> sizes;

    uint find(uint x){
        if(x == par[x]) return x;
        return par[x] = find(par[x]);
    }
public:
    UnionFind() = delete;
    UnionFind(uint size) : par(size), sizes(size, 1){
        for(uint i = 0; i < size; ++i) par[i] = i;
    }

    bool unite(uint x, uint y){
        x = find(x);
        y = find(y);
        if(x == y) return false;
        
        if(sizes[x] < sizes[y]) std::swap(x, y);
        if(sizes[x] == sizes[y] && x > y) std::swap(x, y);
        sizes[x] += sizes[y];
        sizes[y] = 0;
        par[y] = x;
        return true;
    }
    bool isSame(uint x, uint y ){ return find(par[x]) == find(par[y]);}
    uint getSize(uint x){return sizes[find(par[x])];}
}; 