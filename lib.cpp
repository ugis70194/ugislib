#include<bits/stdc++.h>
using namespace std;

int gcd(int n,int m){return !m?n:gcd(m,n%m);}

//Dijkstra
using P = pair<int,int>;
struct edge{int to,cost;};//行き先とそこまでの費用
vector<edge> G[100100]; //edge型の配列の配列をつくる
                        //各頂点から行ける頂点と費用を記録

vector<int> dijkstra(int start){
    // start = 0;
    vector<int> dist(100100,1e9); dist[start] = 0;
    //始点からの費用の合計を記録
    //始点は当然0
    priority_queue<P,vector<P>,greater<P>> Q;
    //優先度付きキューで昇順に取り出す
    Q.push({0,start}); //costと現在地のペアを追加
    while(!Q.empty()){
        P p = Q.top(); Q.pop(); //取り出して削除
        //second が現在地,first がそこまでの費用の和
        //現在地に記録されている費用の和より今までの費用の和が大きいならスキップ
        if(dist[p.second] < p.first) continue;
        for(auto &e : G[p.second]){//現在地から行ける点を列挙
            if(dist[e.to] > dist[p.second] + e.cost){//現在行き先に記録されている値より、現在地に記録されている値のそこまでの費用の和が小さいなら
                dist[e.to] = dist[p.first] + e.cost; //行き先の記録を更新
                Q.push({dist[e.to],e.to}); //行き先とそこまでの値を突っ込む 
            }
        }
    } 
    return dist;//始点から各点に行く最小コストが記録されたものを返す
} 


