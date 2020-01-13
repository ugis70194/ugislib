#include <iostream>
#include <algorithm>
#include <vector>
#include <functional> 
using namespace std;

#define int long long 
template <typename Monoid>
struct SegmentTree {
    using Function = function< Monoid(Monoid,Monoid) >;
    int size;
    vector<Monoid> segment;

    const Function f;
    const Monoid M_1; //Monoid の単位元?

    SegmentTree(int N, const Function f, const Monoid &M_1) : f(f), M_1(M_1) {
        size = 1;
        while (size < N) size <<= 1;
        segment.assign(2 * size , M_1);
    } 

    void set(int K, const Monoid &X){
        segment[K + size] = X;
    }

    void build(){
        for(int k = size - 1;k > 0;--k){
            segment[k] = f(segment[2 * k + 0],segment[2 * k + 1]);
        }
    }

    void update(int k, const Monoid &x){
        k += size;
        segment[k] = x;
        while(k >>= 1){
            segment[k] = f(segment[2 * k + 0],segment[2 * k + 1]);
        }
    }

    Monoid query(int a,int b){
        Monoid L = M_1, R = M_1;
        for(a += size, b += size; a < b; a >>= 1, b >>= 1){
            if(a & 1) L = f(L, segment[a++]);
            if(b & 1) R = f(segment[--b], R);
        }
        return f(L,R);
    }

    Monoid operator[](const int &k) const {
        return segment[k + size];
    }
};
