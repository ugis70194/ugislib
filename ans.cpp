//We love ABC
const long long mod = 1e9 + 7;
long long dp[100010][4];
string t = "ABC";
int main(){
    string s;
    cin >> s;
    int n = s.size();
    dp[0][0] = 1;
    for(int i = 0; i < n; i++){
        for(int j = 0; j <= 3; j++){
            if(s[i] != '?') dp[i + 1][j] = (dp[i + 1][j] + dp[i][j]) % mod;
            else dp[i + 1][j] = (dp[i + 1][j] + dp[i][j] * 3) % mod;
            if(j < 3 && (s[i] == '?' || s[i] == t[j])) dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j]) % mod;
        }
    }
    cout << dp[n][3] << endl;
}

//FT Robot
string s;
int x,y;
bitset<202020> X[2];
 
int main(){
  cin >> s >> x >> y;
  X[0][101010] = true;
  X[1][101010] = true;
 
  int cou = 0;
  int index = 0;
  while(index < s.size() && s[index++] == 'F') cou++;
  X[0] = (X[0] << cou);
 
  int now = 1;
 
  while(index < s.size()){
    cou = 0;
    while(index < s.size() && s[index++] == 'F') cou++;
    X[now] = (X[now] << cou) | (X[now] >> cou);
    now ^= 1;
  }
 
  if(X[0][x + 101010] && X[1][y + 101010]){
    cout << "Yes" << endl;
  }
  else{
    cout <<"No" << endl;
  }
}









//Repeated Spell
const int mod = 1000000007;
int n, m, dp[1009][1009]; string s, t;
int main() {
    cin >> s >> t;
    n = s.size();
    m = t.size();
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m; ++j) {
            dp[i + 1][j] = dp[i][j];
            if (j != 0 && s[i] == t[j - 1]) {
                dp[i + 1][j] += dp[i][j - 1];
                if (dp[i + 1][j] >= mod) dp[i + 1][j] -= mod;
            }
        }
    }
    cout << dp[n][m] << endl;
    return 0;
}

//srange bank
const int MAX_N = 110000;

int dp[MAX_N]; // dp[i] が i についての答え

int main() {
	int N;
	cin >> N;

	// 初期化
	for (int i = 0; i < MAX_N; ++i) dp[i] = N; // INF の気持ち
	dp[0] = 0;

	// 集める DP --- dp[n] に遷移を集める
	for (int n = 1; n <= N; ++n) {
		for (int pow6 = 1; pow6 <= n; pow6 *= 6) {
			dp[n] = min(dp[n], dp[n - pow6] + 1);
		}
		for (int pow9 = 1; pow9 <= n; pow9 *= 9) {
			dp[n] = min(dp[n], dp[n - pow9] + 1);
		}
	}

	cout << dp[N] << endl;
}



























const int MAX_N = 110000;

int dp[MAX_N]; // dp[i] が i についての答え

int main() {
	int N;
	cin >> N;

	// 初期化
	for (int i = 0; i < MAX_N; ++i) dp[i] = N; // INF の気持ち
	dp[0] = 0;

	// 配る DP --- dp[n] から遷移を出して行く
	for (int n = 0; n < N; ++n) {
		for (int pow6 = 1; n + pow6 <= N; pow6 *= 6) {
			dp[n + pow6] = min(dp[n + pow6], dp[n] + 1);
		}
		for (int pow9 = 1; n + pow9 <= N; pow9 *= 9) {
			dp[n + pow9] = min(dp[n + pow9], dp[n] + 1);
		}
	}

	cout << dp[N] << endl;
}

//徒競走
#include <bits/stdc++.h>
using namespace std;
int n, m, x, y; long long dp[1 << 20]; vector<int> G[20];
int main() {
	cin >> n >> m;
	for(int i = 0; i < m; i++) cin >> x >> y, G[y - 1].push_back(x - 1);
	dp[0] = 1;
	for(int i = 1; i < (1 << n); i++) {
		for(int j = 0; j < n; j++) {
			if(!(i & (1 << j))) continue;
			bool flag = true;
			for(auto &e : G[j]) {
				if(!(i & (1 << e))) {
					flag = false;
					break;
				}
			}
			if(flag) dp[i] += dp[i - (1 << j)];
		}
	}
	cout << dp[(1 << n) - 1] << endl;
}

//高橋くんの苦悩
int main(){
  int W,N,K;
  cin>> W >> N >> K;
  vector<int> A(N),B(N);
  rep(i,0,N - 1){
    cin >> A[i] >> B[i];
  }
 
  vector<vector<int>> dp(W + 1,vector<int>(K + 1,-1e9));
  dp[0][0]  = 0;
  int ans = 0;
  rep(i,0,N - 1){
    auto next = dp;
    rep(w,A[i],W){
      rep(k,1,K){
        next[w][k] = max(next[w][k] , dp[w - A[i]][k - 1] + B[i]);
        ans = max(ans , next[w][k]);
      }
    }
    swap(next,dp);
  }
  cout << ans << endl;
}

//Mixing Experiment
int N;
int Ma,Mb;
vector<int> A,B,C;
int main(){
  cin >> N >> Ma >> Mb;
  A.resize(N);
  B.resize(N);
  C.resize(N);
  rep(i,0,N - 1){
    cin >> A[i] >> B[i] >> C[i];
  }
 
  vector<vector<int>> dp(505,vector<int>(505,1e9));
  dp[0][0] = 0;
 
  rep(i,0,N - 1){
    auto next = dp;
    rep(a,0,400)rep(b,0,400){
      if(a - A[i] >= 0 && b - B[i] >= 0){
        next[a][b] = min(next[a][b],dp[a - A[i]][b - B[i]] + C[i]);
      }
    }
    swap(next,dp);
  }
  int a = Ma;
  int b = Mb;
  int ans = 1e9;
  while(a <= 400 && b <= 400){
    ans = min(ans , dp[a][b]);
    a += Ma;
    b += Mb;
  }
 
  cout << (ans == 1e9 ? -1 : ans) << endl;
}

//Candies
int main() {
	int n;
	cin >> n;
	vvi a(3, vi(n + 1));
	erep(i, 1, 2) erep(j, 1, n) cin >> a[i][j];
	vvi dp(3, vi(n + 1, 0));
	erep(i, 1, 2) erep(j, 1, n) dp[i][j] = a[i][j] + max(dp[i - 1][j], dp[i][j - 1]);
	cout << dp[2][n] << endl;
}
