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
#include <assert.h>
#include <unordered_map>
#define all(a) a.begin(),a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define clx complex<long double>
#define rep(i,n) for(int i=0;i<n;++i)
typedef long long ll;
typedef long double ldb;



using namespace std;
int _bufint;
inline int in(){
    scanf("%d", &_bufint);
    return _bufint;
}
const ll LINF=(~((1ll)<<63));
const int INF=~(1<<31);
const double eps=1e-6;


int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
   // freopen("trans.in", "r", stdin);
   // freopen("trans.out", "w", stdout);
#endif
    int n = in();
    vector <int> z;
    for(int i = 0; i < n; ++i) z.pb(in());
    vector<int> pf (n, 0);
    for(int i = 1; i < n; ++i){
        pf[i + z[i] - 1]=max(pf[i + z[i] - 1], z[i]);
    }
    for(int i = n - 1; i > 0; --i) pf[i - 1] = max(pf[i] - 1, pf[i - 1]);
    for(int i = 0; i < n; ++i) printf("%d ", pf[i]);
    
    return 0;
}
