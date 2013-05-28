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
#define all(a) a.begin(),a.end()
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define clx complex<long double>
#define rep(i,n) for(int i=0;i<n;++i)
typedef long long ll;
typedef long double ldb;
typedef unsigned long long ull;

using namespace std;
int _bufint;
inline int in(){
    scanf("%d", &_bufint);
    return _bufint;
}
const ll LINF=~((1ll)<<63);
const int INF=~(1<<31);
const double eps=1e-6;
ll n, s, k;
vector<ll> v;
int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
#endif
    n=in();
    s=in();
    k=in();

    for(int i=0;i<k;++i) v.pb(in());

    ll nn=1<<(k/2);
    vector<ll> m;
    vector<ll> a, b;
    for(int i=0;i<k/2;++i) a.pb(v[i]);
    for(int i=k/2;i<k;++i) b.pb(v[i]);
    for(int i=0;i<nn;++i){
        ll sum=s;
        for(int j=0;j<(k/2);++j){
            if((1<<j) & i){
                sum+=a[j];
            }else sum-=a[j];
            if(sum<0 || sum>n){
                sum=-1;
                break;
            }
        }
        if(sum>=0) m.pb(sum);
    }
    sort(m.begin(), m.end());
    ll ans1=LINF, ans2=-LINF;
    ll mm=1<<(k-k/2);
    for(int i=0;i<mm;++i){
        ll sum=0;
        ll minsum=LINF;
        ll maxsum=-LINF;
        for(int j=0;j<(k-k/2);++j){
            if((1<<j) & i){
                sum+=b[j];
            }else sum-=b[j];
            minsum=std::min(minsum, sum);
            maxsum=std::max(maxsum, sum);
        }
        if(maxsum>n) continue;
        ll c1=*lower_bound(m.begin(), m.end(), max(-minsum,0ll));
        if(c1+maxsum<=n && c1+minsum>=0)
          ans1=min(ans1, c1+sum);
        ll c2=*(--lower_bound(m.begin(), m.end(), min(n-maxsum, n)+1));
      //  if(upper_bound(m.begin(), m.end(), n-maxsum)==m.begin()) assert(1);
        if(c2+sum>n) continue;
        if(c2+minsum>=0 && c2+maxsum<=n)
            ans2=max(ans2, c2+sum);
    }
    cout<<ans1<<' '<<ans2<<endl;
    return 0;
}
