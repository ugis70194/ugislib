struct UnionFind{
    vector<int> par;
    vector<int> sizes;

    UnionFind(int size) : par(size), sizes(size,1){
        for(int i=0;i<size;i++) par[i] = i;
    }

    bool unite(int x,int y){
        x = find(x);
        y = find(y);

        if(x == y) return false;
        if(sizes[x] < sizes[y]) swap(x,y);

        par[y] = x;
        sizes[x] += sizes[y];
        sizes[y] = 0;

        return true;
    }

    int find(int x){
        if(par[x] == x) return x; 
        return par[x] = find(par[x]);
    }

    bool isSame(int x,int y){
        return find(x) == find(y);
    }

    int getSize(int x){
        return sizes[find(x)];
    }
};

struct edge{
    int from,to;
    int weight;

    bool operator <(const edge& e) const {
        return weight < e.weight;
    }
};

vector<edge> kruskal(int VertexNum, vector<edge>& Edges){
    UnionFind forest(VertexNum);
    vector<edge> edges;
    
    sort(Edges.begin(),Edges.end());
    for(edge Edge : Edges){
        if(!forest.isSame(Edge.from,Edge.to)){
            forest.unite(Edge.from,Edge.to);
            edges.push_back(Edge);
        }
    }

    return edges;
}
