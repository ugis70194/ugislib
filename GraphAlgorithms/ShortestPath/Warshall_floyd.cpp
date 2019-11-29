#include<vector>
#include<algorithm>

template<typename Int>
void Warshall_Floid(std::vector<std::vector<Int>>& min_dist, int V, Int INF){
    for(int relay = 0; relay < V; relay++){
        for(int from = 0; from < V; from++){
            for(int to = 0; to < V; to++){
                if(min_dist[from][relay] == INF) continue;
                if(min_dist[relay][to] == INF) continue;
                min_dist[from][to] = std::min(min_dist[from][to], min_dist[from][relay] + min_dist[relay][to]);
            }
        }
    }
}