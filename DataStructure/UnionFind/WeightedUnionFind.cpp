#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

template<class Abel> struct UnionFind {
    vector<int> par; //親ノード
    vector<int> rank; //高さ
    vector<Abel> diff_weight;

    UnionFind(int N = 1, Abel SUM_UNITY = 0){
        init(N, SUM_UNITY);
    } 

    void init(int N = 1, Abel SUM_UNITY = 0){
        par.resize(N);
        rank.resize(N);
        diff_weight.resize(N);

        for(int i = 0; i < N; ++i){
            par[i] = i;
            rank[i] = 0;
            diff_weight[i] = SUM_UNITY;
        }
    }

    int root(int x){
        if(par[x] == x) return x;
        else{
            diff_weight[x] += diff_weight[par[x]];
            return par[x] = root(par[x]);
        }
    }

    bool is_same(int x,int y){ 
        return root(x) == root(y); 
    }

    Abel  weight(int x){
        root(x);
        return diff_weight[x];
    }

    Abel diff(int x,int y){
        return weight(y) - weight(x);
    }

    bool merge(int x,int y,int w = 0){
        w += weight(x);
        w -= weight(y);

        x = root(x);
        y = root(y);
        if(x == y) return false;

        if(rank[x] < rank[y]) swap(x,y), w = -w;
        if(rank[x] == rank[y]) ++rank[x];
        par[y] = x;
        diff_weight[y] = w;
        return true;
    }
};