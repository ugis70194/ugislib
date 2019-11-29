#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using i64 = long long;

vector<i64> dist;

//if find negative loop,return true
bool Bellman_Ford(vector<vector<pair<int,int>>>& Graph,int V, int start){
    dist[start] = 0;
    for(int i=0;i<V;++i){
        for(int v=0;v<V;++v){
            for(auto& e : Graph[v]){
                if(dist[v] == 1e18) continue;
                if(dist[e.first] > dist[v] + e.second){
                    dist[e.first] = dist[v] + e.second;
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
