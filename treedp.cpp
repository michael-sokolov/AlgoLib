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
vector<vector<ll> > g;
vector<ll> weig, sum;
vector<ll> inp;
ll tp=1;
void dfs1(ll v, ll p){
    weig[v]=1;
    sum[v]=0;
    inp[v]=tp++;
    for(ll i=0;i<g[v].size();++i){
        ll to=g[v][i];
        if(to==p) continue;
        dfs1(to, v);
        weig[v]+=weig[to];
        sum[v]+=weig[to]+sum[to];
    }
}
vector<ll> upw;
void dfs2(ll v, ll p,ll up){
    upw[v]=up;
    for(ll i=0;i<g[v].size();++i){
        ll to=g[v][i];
        if(to==p) continue;
        dfs2(to, v, up+sum[v]-sum[to]-weig[to]+(g.size()-weig[v]));
    }
}

int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
   // freopen("trans.in", "r", stdin);
   // freopen("trans.out", "w", stdout);
#endif
    ll n=in();

    g.assign(n, vector<ll>());
    vector<pair<ll,ll> > edges;
    weig.assign(n, 0);
    sum.assign(n,0);
    upw.assign(n,0);
    inp.assign(n,0);
    for(ll i=0;i<n-1;++i){
        ll a=in()-1, b=in()-1;
        g[a].pb(b);
        g[b].pb(a);
        edges.pb(mp(a,b));
    }
    dfs1(0,-1);
    dfs2(0,-1,0);

    for(ll i=0;i<n-1;++i){
        ll a=edges[i].first, b=edges[i].second;
        if(inp[a] > inp[b]) swap(a,b);
        ll res=weig[b]*upw[b]+(n-weig[b])*sum[b]+weig[b]*(n-weig[b]);
        cout<<res<<endl;
    }
//for each edge sum of lenghts of simple paths


    return 0;
}

