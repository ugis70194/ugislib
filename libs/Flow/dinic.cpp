#include<vector>
#include<queue>
#include<cstdint>

struct edge {
  size_t to; // 行先の頂点番号
  size_t rev; // 逆辺 Graph[to][from] が G[to] の何番目の要素か
  int_fast32_t capacity; // 辺の容量

  edge() = delete;
  edge(size_t to, int_fast32_t capacity, size_t rev){
    this->to = to;
    this->capacity = capacity;
    this->rev = rev;
  }
};

class Dinic {
private:
  mutable std::vector<std::vector<edge>> Graph;
  mutable std::vector<int_fast32_t> level; // distance from s
  mutable std::vector<size_t> looked;

  // get distance from node s.
  void get_distance(size_t s){
    level.assign(level.size(), -1);
    std::queue<size_t> que;

    que.push(s);
    level[s] = 0;

    while(!que.empty()){
      auto& from = que.front(); que.pop();

      for(size_t i = 0; i < Graph[from].size(); i++){
        edge& e = Graph[from][i];

        if(e.capacity > 0 and level[e.to] == -1){
          level[e.to] = level[from] + 1;
          que.push(e.to);
        }
      }
    }
  }

  // flow amount f from node v to node t
  // パスs-tの最小容量と流したflow fの小さいほうが返ってくる
  int_fast32_t get_flow_v_to_t(size_t v, size_t t, int_fast32_t f){
    if(v == t){
      return f;
    }

    for(size_t& i = looked[v]; i < Graph[v].size(); i++){
      edge& e = Graph[v][i];

      //距離が増加する向きのみ調べる
      if(e.capacity > 0 && level[v] < level[e.to]){
        int_fast32_t flow = get_flow_v_to_t(e.to, t, std::min(f, e.capacity));
        if(flow > 0){
          e.capacity -= flow;
          Graph[e.to][e.rev].capacity += flow;
          return flow;
        }
      }
    }
    return 0;
  }
public:
  Dinic() = delete;
  Dinic &operator=(const Dinic) = delete;

  Dinic(size_t V){
    Graph.resize(V);
    level.resize(V);
    looked.resize(V);
  }

  void add_edge(size_t from, size_t to, int_fast32_t capacity){
    size_t rev_from = Graph[to].size();
    size_t rev_to = Graph[from].size();
    Graph[from].push_back(edge(to, capacity, rev_from));
    Graph[to].push_back(edge(from, 0, rev_to));
  }


  // return maximum_flow from node s to node t.
  int_fast32_t maximum_flow(size_t s, size_t t) {
    int_fast32_t max_flow = 0;
    get_distance(s);

    // 残余グラフ上でsからtに到達できなくなったら終わり
    while(level[t] != -1){
      looked.assign(looked.size(), 0);

      int_fast32_t flow = INT32_MAX;
      while(flow > 0){
        flow = get_flow_v_to_t(s, t, INT32_MAX);
        max_flow += flow;
      }

      get_distance(s);
    }
    return max_flow;
  }
};