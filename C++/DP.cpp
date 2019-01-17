#include<bits/stdc++.h>
using namespace std;
#define rep(i,N) for(int (i)=0;(i)<(N);++(i))
int knapsack(){
    int dp[1010][100100];
    int v[1010],w[1010];
    int N,W;
    cin >> N >> W;
    rep(i,N) cin >> v[i] >> w[i];

    int ans = 0;
    rep(i,N){
        rep(j,W+1){
            dp[i+1][j] = dp[i][j];
            if(j < w[i]) continue;
            dp[i+1][j] = max(dp[i+1][j],dp[i][j-w[i]] + v[i]);
            ans = max(ans,dp[i+1][j]);
        }
    }

    return ans;
}