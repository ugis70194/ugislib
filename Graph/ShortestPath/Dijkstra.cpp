namespace a{
    #include<iostream>
    #include<vector>
    #include<algorithm>
    #include<queue>
    using namespace std;
    using ll = long long;
    using P = pair<ll,ll>;

    struct edge{ll to,cost;};
    vector<edge> G[100100];

    vector<ll> Dijkstra(int start){
        vector<ll> dist(100100,1e18); 
        dist[start] = 0;
        priority_queue<P,vector<P>,greater<P>> Q;
        Q.push({0ll,start});

        while(!Q.empty()){
            P p = Q.top(); Q.pop();
            if(dist[p.second] < p.first) continue;
            for(auto& e : G[p.second]){
                if(dist[e.to] > dist[p.second] + e.cost){
                    dist[e.to] = dist[p.second] + e.cost;
                    Q.push({dist[e.to],e.to});
                }
            }
        }
        return dist;
    }
}

/*
優先度付きキューを用いてcostが小さいものから順番に取り出す
明らかに最適でないものを取り除いて値を更新する、
明らかに最適な場合は更新をしない（同じ辺を戻らない）ことで高速化する
*/

namespace b{
    #include<iostream>
    #include<vector>
    #include<queue>
    using namespace std;

    #define INF (1LL << 63)
    struct edge{
        size_t to;
        size_t weight;
    };

    vector<size_t> dijkstra(vector<vector<edge>>& Graph, int& startPoint, int& vertexNum){
        vector<size_t> minimumWeight(vertexNum,INF);

        priority_queue<vector<pair<size_t,size_t>>, vector<pair<size_t,size_t>>, greater<pair<size_t,size_t>>> priorityQueue;
        priorityQueue.push({0,startPoint});
        minimumWeight[startPoint] = 0;

        while(!priorityQueue.empty()){
            pair<size_t,size_t> tmp = priorityQueue.top();

            edge Edge;
            Edge.to = tmp.second;
            Edge.weight = tmp.first;

            priorityQueue.pop();

            if(minimumWeight[Edge.to] < Edge.weight) continue;
            for(edge& edge : Graph[Edge.to]){
                if(minimumWeight[edge.to] < minimumWeight[Edge.to] + edge.weight) continue;
                minimumWeight[edge.to] = minimumWeight[Edge.to] + edge.weight;
                priorityQueue.push({minimumWeight[edge.to],edge.to});
            }
        }
        return minimumWeight;
    }

}

namespace c{
    vector<vector<int>> dijkstra(vector<vector<edge>>& Graph,int vertex, int start, int tickets){
    #define INF 1e18
    using PP = pair<int,P>;
    #define weight first
    #define now second.first
    #define ticket second.second

    vector<vector<int>> dist(vertex,vector<int>(tickets+1,INF));
    priority_queue<vector<PP>,vector<PP>,greater<PP>> Q;

    Q.push({0,{start,tickets}});
    for(int i=0;i<=tickets;i++) dist[start][i] = 0;

    while(!Q.empty()){
        PP p = Q.top(); Q.pop();
        
        if(dist[p.now][p.ticket] < p.weight) continue;

        for(edge Edge : Graph[p.now]){
            if(dist[Edge.to][p.ticket] < p.weight + Edge.cost) continue;
            
            dist[Edge.to][p.ticket] = p.weight + Edge.cost;
            Q.push({dist[Edge.to][p.ticket], {Edge.to,p.ticket}});

            if(p.ticket > 0){
                if(dist[Edge.to][p.ticket-1] < p.weight) continue;
                dist[Edge.to][p.ticket-1] = p.weight;
                Q.push({dist[Edge.to][p.ticket-1], {Edge.to,p.ticket-1}});
            }
        }
    }
    
    return dist;
    }   
}