#include<bits/stdc++.h>
using namespace std;

// {葉からの距離, 最も遠い葉ノードの番号}
pair<int,int> dfs(vector<vector<int>>& city, vector<int>& visited, int now){
    visited[now] = true;

    int dist = 1, leaf = now;
    for(auto& nxt : city[now]){
        if(visited[nxt]) continue;

        auto d_l = dfs(city, visited, nxt);
        if(dist <= d_l.first){
            dist = d_l.first + 1;
            leaf = d_l.second;
        }
    }

    return {dist, leaf};
}

int diamiter(vector<vector<int>>& city){
    const int V = city.size();
    vector<int> visited(V, 0);
    auto d_l = dfs(city, visited, 0);
    //cout << d_l.first << " " << d_l.second << endl;
    visited.assign(V, 0);
    auto ret = dfs(city, visited, d_l.second);
    //cout << ret.first << " " << ret.second << endl;

    return ret.first;
}