#include<vector>
#include<stack>
#include<queue>
#include<functional>
#include<algorithm>

class HLDecomposition{
private:
    int size, pos;
    std::vector<std::vector<int>> Graph;
    std::vector<int> Dec_id, heavy_head, heavy_next, sub_size, par, depth, inv_id, tree_id;  

    void dfs(int root){
        using Pair = std::pair<int,int>;
        std::stack<Pair> Stack;
        par[root] = -1;
        depth[root] = 0;
        Stack.emplace(root, 0);
        while(!Stack.empty()){
            int v = Stack.top().first;
            int& i = Stack.top().second;
            if(i < (int)Graph[v].size()){
                int u = Graph[v][i]; i++;
                if(u == par[v]) continue;
                par[u] = v;
                depth[u] = depth[v] + 1;
                Stack.emplace(u, 0);
            } else {
                Stack.pop();
                int max_sub = 0;
                for(int& u : Graph[v]){
                    if(u == par[v]) continue;
                    sub_size[v] += sub_size[u];
                    if(max_sub < sub_size[u]){
                        max_sub = sub_size[u];
                        heavy_next[v] = u;
                    }
                }
            }
        }
    }

    void bfs(int root, int id){
        int& k = pos;
        std::queue<int> que({root});
        while(!que.empty()){
            int head = que.front(); que.pop();
            for(int i = head; i != -1; i = heavy_next[i]){
                tree_id[i] = id;
                Dec_id[i] = k; k++;
                inv_id[Dec_id[i]] = i;
                heavy_head[i] = head;
                for(int h : Graph[i]){
                    if(h != par[i] && h != heavy_next[i]) que.push(h);
                }
            }
        }
    }
public:
    HLDecomposition() = delete;
    HLDecomposition(int V) : 
        size(V), pos(0), Graph(size), Dec_id(size, -1), 
        heavy_head(size),heavy_next(size, -1), sub_size(size, 1), 
        par(size), inv_id(size), tree_id(size) {} 

    void add_edge(int u, int v){
        Graph[u].emplace_back(v);
        Graph[v].emplace_back(u);
    }  
    void build(std::vector<int> forest = std::vector<int>(1,0)){
        int id = 0;
        for(int& root : forest){
            dfs(root);
            bfs(root, id); id++;
        }
    }  

    void for_each(int u, int v, const std::function<void(int ,int)>& func){
        while(1){
            if(Dec_id[u] > Dec_id[v]) std::swap(u, v);
            func(std::max(Dec_id[heavy_head[v]], Dec_id[u]), Dec_id[v]);
            if(heavy_head[u] != heavy_head[v]) v = par[heavy_head[v]];
            else break;
        }
    }

    void for_each_edge(int u, int v, const std::function<void(int ,int)>& func){
        while(1){
            if(Dec_id[u] > Dec_id[v]) std::swap(u, v);
            if(heavy_head[u] != heavy_head[v]){
                func(Dec_id[heavy_head[v]], Dec_id[v]);
                v = par[heavy_head[v]];
            } else {
                if(u != v) func(Dec_id[u] + 1, Dec_id[v]);
                break;
            }
        }
    }

    int LCA(int u, int v){
        while(1){
            if(Dec_id[u] > Dec_id[v]) std::swap(u, v);
            if(heavy_head[u] == heavy_head[v]) return u;
            v = par[heavy_head[v]];
        }
    }

    int dist(int u ,int v){
        return depth[u] + depth[v] - 2*depth[LCA(u, v)];
    }
};