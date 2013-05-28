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
vector<vector<int> > g;
vector<vector<int> > que;
vector<int> dists;
vector<int> deep;
void dfs1(int v, int d){
    deep[v]=d;
    for(int i=0;i<g[v].size();++i){
        int to=g[v][i];
        if(deep[to]==-1) dfs1(to, d+1);
    }
}
set<pair<int,int> > s;
vector<int> u;
vector<int> pars;
vector<int> ans;
void dfs2(int v, int d){
    u[v]=1;
    pars.pb(v);
    set<pair<int,int> >::iterator cur=s.lower_bound(mp(d,-1));
    while(cur!=s.end()){
        pair<int,int> c=*cur;
        if(c.first==d){
            if(ans[c.second]==0)ans[c.second]=v+1;
            ++cur;
            s.erase(c);
        }else break;
    }
    for(int i=0;i<que[v].size();++i){
        if(dists[que[v][i]]<=d){
            if(ans[que[v][i]]==0) ans[que[v][i]]=pars[d-dists[que[v][i]]]+1;
        }else
        s.insert(mp(dists[que[v][i]] + d, que[v][i]));
    }

    for(int i=0;i<g[v].size();++i){
        int to=g[v][i];
        if(!u[to]){
            dfs2(to, d+1);
        }
    }


    for(int i=0;i<que[v].size();++i){
        s.erase(mp(dists[que[v][i]] + d, que[v][i]));
    }
    pars.pop_back();
}

int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
#endif

    int n=in();
    int q=in();
    g.assign(n, vector<int>());
    ans.assign(q, 0);
    for(int i=0;i<n-1;++i){
        int a=in()-1, b=in()-1;
        g[a].pb(b);
        g[b].pb(a);
    }
    que.assign(n, vector<int>());
    for(int i=0;i<q;++i){
        int a=in()-1, d=in();
        que[a].pb(i);
        dists.pb(d);
    }
    deep.assign(n, -1);
    dfs1(0,0);
    int die=0;
    for(int i=0;i<deep.size();++i){
        if(deep[i]>deep[die]) die=i;
    }
    deep.assign(n, -1);
    dfs1(die,0);
    die=0;
    for(int i=0;i<deep.size();++i){
        if(deep[i]>deep[die]) die=i;
    }
    u.assign(n, 0);

    dfs2(die, 0);

    deep.assign(n, -1);
    dfs1(die,0);
    die=0;
    for(int i=0;i<deep.size();++i){
        if(deep[i]>deep[die]) die=i;
    }
    u.assign(n, 0);
    dfs2(die,0);
    for(int i=0;i<ans.size();++i){
        printf("%d\n", ans[i]);
    }


    return 0;
}
