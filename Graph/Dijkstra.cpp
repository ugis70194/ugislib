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