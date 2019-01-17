int gcd(int n,int m){return m?gcd(m,n%m):n;}
int lcm(int n,int m){return n*m/gcd(n,m);} 