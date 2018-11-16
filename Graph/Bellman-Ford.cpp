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
/*
全ての頂点に対していける頂点を全て調べる、という操作を頂点の数だけ繰り返す
負の閉路が無ければこの操作を一度行うことで必ず一つ以上の頂点について最小値が確定する
始点が初めから確定しているのでV回目で更新があれば負の閉路があると言える
*/
