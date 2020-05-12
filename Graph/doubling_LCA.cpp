#include<iostream>
#include<vector>


class doubling_LCA {
private:
    std::vector<std::vector<int>> Tree;
    std::vector<std::vector<int>> par;
    std::vector<int> depth;

    void dfs(int v, int p){
        for(auto& c : Tree[v]) {
            if(c == p) continue;
            depth[c] = depth[v] + 1;
            par[0][c] = v;
            dfs(c, v); 
        }
    }
    void doubling(const int& V){
        const int D = par.size();
        for(int d = 1; d < D; d++){
            for(int v = 0; v < V; v++){
                if(par[d-1][v] < 0) par[d][v] = -1;
                else par[d][v] = par[d-1][par[d-1][v]];
            }
        }
    }

public: 
    doubling_LCA() = delete;
    doubling_LCA(const doubling_LCA&) = delete;
    doubling_LCA& operator=(const doubling_LCA&) = delete;

    doubling_LCA(std::vector<std::vector<int>>& tree, int root = 0) : Tree(tree) {
        int V = Tree.size();
        int D = 1;
        while((1 << D) < V) D++;
        depth.assign(V, -1);
        par.assign(D, std::vector<int>(V, -1));

        dfs(root, -1);
        doubling(V);
    }

    int operator()(int u, int v){
        if(depth[u] < depth[v]) std::swap(u, v);
        int D = par.size();
        for(int d = 0; d < D; d++){
            if((depth[u] - depth[v]) & (1 << d)) u = par[d][u];
        }

        if(u == v) return u;
        for(int d = D - 1; d >= 0; d--){
            if(par[d][u] != par[d][v]) {
                u = par[d][u];
                v = par[d][v];
            }
        }
        return par[0][u];
    }
};

int main(){
    using namespace std;
    int N;
    cin >> N;

    std::vector<std::vector<int>> Tree(N);
    for(int i = 0; i < N; i++){
        int K; cin >> K;
        Tree[i].resize(K);
        for(int k = 0; k < K; k++){
            cin >> Tree[i][k];
        }
    }

    doubling_LCA LCA(Tree);

    int Q;
    cin >> Q;
    for(int i = 0; i < Q; i++){
        int u, v;
        cin >> u >> v;
        cout << LCA(u, v) << endl;
    }
}