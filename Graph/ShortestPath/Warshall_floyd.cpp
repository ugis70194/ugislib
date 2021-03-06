#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
using ll = long long;

vector<vector<ll>> dist(1010,vector<ll>(1010,1e18));

// if dist[n][n] is negative, It have negative loop
void Warshall_floyd(int& V){
    for(int mid=0;mid<V;++mid){
        for(int s=0;s<V;++s){
            for(int e=0;e<V;++e){
                if(dist[s][mid] == 1e18 || dist[mid][e] == 1e18) continue;
                dist[s][e] = min(dist[s][e],dist[s][mid] + dist[mid][e]);
            }
        }
    } 
}
/*
始点からある点を経由して終点へ行く、という操作を全てのパターンに対して行う
ただし辺がない場合は行わない(それはそう)
自己に対しての距離は常に０（明らかに最小なため）
負の閉路が存在する場合、自己に対しての距離が負になる
*/
