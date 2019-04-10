void visit(vector<vector<int>>& Graph, vector<bool>& visited, vector<int>& topo, int v){
    if(visited[v]) return;
    visited[v] = true;
    for(auto next : Graph[v]) visit(Graph, visited, topo, next);
    topo.push_back(v);
}

vector<int> topological_sort(vector<vector<int>>& Graph, int V){
    vector<int> topo;
    vector<bool> visited(V,false);
    for(int i=0;i<V;i++) visit(Graph, visited, topo, i);
    reverse(topo.begin(),topo.end());

    return topo;
}