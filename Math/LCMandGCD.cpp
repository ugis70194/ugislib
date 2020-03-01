#include<cstdint>
using i64 = int_fast64_t;
int gcd(int n,int m){return m?gcd(m,n%m):n;}
int lcm(int n,int m){return n*m/gcd(n,m);} 
i64 extGCD(i64 a, i64 b, i64& x, i64& y){
    if(b == 0){
        x = 1, y = 0;
        return a; 
    }
    i64 g = extGCD(b, a%b, y, x); 
    y -= a/b * x; 
    return g;
}