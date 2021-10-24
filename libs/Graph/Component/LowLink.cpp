#include<vector>
#include<algorithm>
class LowLink{
private:
    std::vector<std::vector<int>> Graph;
    std::vector<bool> visited; 
    std::vector<int> order, low;

    void dfs(int u = 0 , int ord = 0, int par = -1){
        visited[u] = true;
        order[u] = ord;
        low[u] = ord;
        bool is_articulation = false;
        int deg = 0;
        for(int& v : Graph[u]){
            if(par == v) continue;
            if(visited[v] == false){
                deg++;
                dfs(v, ord+1, u);
                is_articulation |= (par != -1 && order[u] <= low[v]);
                low[u] = std::min(low[u], low[v]);
                if(order[u] < low[v]) bridge.emplace_back(std::make_pair(std::min(u, v), std::max(u,v)));
            } else {
                low[u] = std::min(low[u], order[v]);
            }
        }
        is_articulation |= (par == -1 && deg > 1);
        if(is_articulation) articulation.emplace_back(u);
    }
public:
    std::vector<int> articulation;
    std::vector<std::pair<int, int>> bridge;
    LowLink() = delete;
    LowLink(std::vector<std::vector<int>>& G) :  Graph(G){
        visited.assign(Graph.size(), false);
        order.resize(Graph.size());
        low.resize(Graph.size());
        dfs(); 
    }

    std::vector<int> get_articulation(){
        return articulation;
    }

    std::vector<std::pair<int,int>> get_bridge(){
        return bridge;
    }
};