#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;

struct edge{ll to,cost;};
vector<edge> G[100100];
vector<ll> dist;
int V,E;//number of vertices and edges

//if find negative loop,return true
bool Bellman_Ford(int start){
    dist[start] = 0;
    for(int i=0;i<V;++i){
        for(int v=0;v<V;++v){
            for(auto& e : G[v]){
                if(dist[v] == 1e18) continue;
                if(dist[e.to] > dist[v] + e.cost){
                    dist[e.to] = dist[v] + e.cost;
                    if(i == V-1) return true;
                }
            }
        }
    }
    return false;
}