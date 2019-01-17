#include<bits/stdc++.h>
using namespace std;
#define rep(i,N) for(int (i)=0;(i)<(N);++(i))

int Enumerate(int N,int X,int A[]){//数え上げ
    int sum = 0,ans = 0,left = 0;
    for(int right = 0; right < N;++right){
        sum += A[right];
        while(sum > X) sum -= A[left],++left;
        ans += right - left + 1;
    }
    return ans;
}

int Seq(){
    int N,K,ans = 0;
    cin >> N >> K;
    vector<int> S(N);
    for(int i = 0;i<N;++i){cin >> S[i];if(S[i] == 0) ans = N;}

    int prd = 1;
    int right = 0;
    if(ans == N)return ans;
    for(int left = 0;left < N;++left){
        while(right < N && prd*S[right] <= K){
            prd *= S[right];
            ++right;
        }
        ans = max(ans,(right-left));
        if(left == right) ++right;
        else prd /= S[left];
    }

    if(K == 0) ans = 0;
    return ans;
}