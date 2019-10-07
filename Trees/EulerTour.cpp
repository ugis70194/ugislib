#include<vector>
#include<algorithm>
#include<cstdint>

template<typename GraphType>
struct EularTour{
    std::vector<std::vector<GraphType>> tree;
    std::vector<size_t> tourArr;
    std::vector<size_t> begin;
    std::vector<size_t> end;
    size_t step;

    EularTour() = delete;
    EularTour(const std::vector<std::vector<GraphType>>& Graph, const size_t GraphSize) : tree(Graph), step(0){
        begin.resize(GraphSize);
        end.resize(GraphSize);
        visited.assign(GraphSize, false);
    }

    void makeTour(size_t v, size_t par=tree.size()+2){
        begin[v] = step;
        tourArr.emplace_back(v);
        step++;
        for(GraphType& next : tree[v]){
            if(next == par) continue;
            makeTour(next, step, v);
            tourArr.emplace_back(v);
            step++;
        }
        end[v] = step;
    }
};