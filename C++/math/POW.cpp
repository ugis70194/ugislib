#define int long long 

int POW(int x,int n){
    int res = 1;
    while(n){
        if(n%2) res *= x;
        x *= x;
        n >>= 1;
    }
    return res;
}