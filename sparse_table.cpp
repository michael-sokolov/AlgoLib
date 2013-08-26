#pragma comment(linker, "/STACK:66777216")
#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <string>
#include <cstring>
#include <algorithm>
#include <set>
#include <ctime>
#include <map>
#include <stack>
#include <deque>
#include <queue>
#include <cmath>
#include <list>
#include <vector>
#include <iomanip>
#include <cctype>
#include <complex>
#include <iterator>
#include <ostream>
#include <bitset>
#include <sstream>
#define all(a) a.begin(),a.end()
#define pb push_back
#define mp make_pair
#define clx complex<long double>
#define rep(i,n) for(int i=0;i<n;++i)
#define all(a) a.begin(),a.end()
#define rall(a) a.rbegin(),a.rend()
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;

using namespace std;
int _bufint;
inline int in(){
   scanf("%d", &_bufint);
   return _bufint;
}
const ll LINF = ~((1ll)<<63);
const int INF = ~(1<<31);
const double eps = 1e-6;
const int N = 25000;
int l[N+5];
unsigned g[N][16];
unsigned int v[N+5];
int main(){
#ifdef SSU
   freopen("input.txt", "r", stdin);
   //    freopen("output.txt", "w", stdout);
#else
   // freopen("beloved.in", "r", stdin);
   //   freopen("beloved.out", "w", stdout);
#endif

   int n,m,a,b;
   int lle=0;

   while( (1 << lle) <= N ){
       for(int i = (1 << lle); i < ( 1 << (lle+1) ) && i <= N; ++i){
           l[i]=lle;
       }
       ++lle;
   }

   while( ~scanf("%d%d%d%d", &n, &m, &a, &b) ){
       if(n + m + a + b == 0) break;
       for(int i = 0; i < n; ++i){
           v[i] = a * (i + 1LL) + b;
       }
       int nn = 1, lo = 0;
       while(nn < n){
           nn *= 2;
           ++lo;
       }
       for(int i = 0; i < n; ++i) g[i][0] = v[i];
       for(int i = 1;i < lo; ++i){
           for(int j = 0; j + (1 << (i-1)) < n; ++j){
               g[j][i] = min(g[j][i-1], g[j + (1 << (i-1))][i-1]);
           }
       }
       ll res=0;
       for(int i = n; i < n+2 * m; i += 2){
           pair<int,int> cur = mp(((unsigned int)(a * (i+1LL) + b)) % n, ((unsigned int)(a * (i+2LL) + b)) % n);
           if(cur.first > cur.second) swap(cur.first, cur.second);
           int len = cur.second - cur.first;
           int ln = l[len];
           unsigned int rr=min(g[cur.first][ln], g[cur.second - (1 << ln) + 1][ln]);
           res += rr;
       }
       printf("%lld\n", res);
   }
   return 0;
}
