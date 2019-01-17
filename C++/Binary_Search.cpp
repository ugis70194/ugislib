#include<vector>
bool Binary_Search(int N,std::vector<int>& S){
    int left = 0,right = N;
    while(left <= right){
        int mid = (left + right) / 2;
        if(S[mid] == N) return true;
        else if(S[mid] > N) right = mid-1;
        else left = mid+1;
    }
    return false;
}
     
