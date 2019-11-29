#define i64 long long 

i64 POW(i64 x,i64 n, i64 MOD = 1000000007){
    i64 res = 1;
    while(n){
        if(n%2) ((res *= x) %= MOD);
        ((x *= x) %= MOD);
        n >>= 1;
    }
    return res;
}