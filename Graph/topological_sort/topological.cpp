#include<vector>
#include<algorithm>

void visit(std::vector<std::vector<int>>& Graph, std::vector<bool>& visited, std::vector<int>& topo, int v){
    if(visited[v]) return;
    visited[v] = true;
    for(auto next : Graph[v]) visit(Graph, visited, topo, next);
    topo.push_back(v);
}

std::vector<int> topological_sort(std::vector<std::vector<int>>& Graph, int V){
    std::vector<int> topo;
    std::vector<bool> visited(V,false);
    for(int i=0;i<V;i++) visit(Graph, visited, topo, i);
    reverse(topo.begin(),topo.end());

    return topo;
}