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

vector<int> top;
vector<int> u;
vector<vector<int> > g, tg;
void dfs(int v){
    u[v]=1;
    for(int i=0;i<g[v].size();++i){
        int to=g[v][i];
        if(!u[to]) dfs(to);
    }
    top.pb(v);
}
bool dfs1(int v, int c){
    u[v]=1;
    if(v==c) return 1;
    for(int i=0;i<g[v].size();++i){
        int to=g[v][i];
        if(!u[to]) dfs(to);
    }
    return 0;
}
vector<int> comps;
void dfs2(int v, int comp){
    comps[v]=comp;
    for(int i=0;i<tg[v].size();++i){
        int to=tg[v][i];
        if(comps[to]==-1) dfs2(to, comp);
    }
}

int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
#endif

    int n=in();
    vector<pair<int,int> > v;
    for(int i=0;i<n;++i){
        int a=in(), b=in()-1, c=in();
        v.pb(mp(i, a));
        v.pb(mp(b, c));
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int m=v.size();
    rewind(stdin);
    n=in();
    g.assign(2*m, vector<int> ());
    tg=g;
    for(int i=0;i<n;++i){
        int a=in(), b=in()-1, c=in();
        int u=lower_bound(v.begin(), v.end(), mp(i, a))-v.begin();
        int e=lower_bound(v.begin(), v.end(), mp(b, c))-v.begin();
        g[u].pb(e+m);
        g[u+m].pb(e);
        g[e+m].pb(u);
        g[e].pb(u+m);
    }

    for(int i=0;i<m;++i){
        for(int j=i+1;j<m;++j){
            if(v[i].second==v[j].second || v[i].first==v[j].first){
                g[i].pb(j+m);
                g[j].pb(i+m);
            }
        }
    }


    u.assign(2*m,0);
    for(int i=0;i<u.size();++i){
        if(!u[i]) dfs(i);
    }
    reverse(top.begin(), top.end());

    //t
    for(int i=0;i<g.size();++i){
        for(int j=0;j<g[i].size();++j){
            int to=g[i][j];
            tg[to].pb(i);
        }
    }
    comps.assign(g.size(), -1);
    int ct=1;
    for(int i=0;i<top.size();++i){
        int to=top[i];
        if(comps[to]==-1) dfs2(to, ct++);
    }
//cut

    vector<int> ans(2*m,0);
    for(int i=0;i<m;++i){
        if(comps[i]<comps[i+m]) ans[i+m]=1;
        else ans[i]=1;
    }
    rewind(stdin);
    n=in();


    for(int i=0;i<n;++i){
        int a=in(), b=in()-1, c=in();
        int u=lower_bound(v.begin(), v.end(), mp(i, a))-v.begin();
        int e=lower_bound(v.begin(), v.end(), mp(b, c))-v.begin();
        if(ans[u]==1) printf("%d ",1);
        else printf("%d ",2);
    }


    return 0;
}
