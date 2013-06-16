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
struct edge{
    int a, b;
    ll cost, cap;
    ll flow;
    ll olc;
    edge(int aa, int bb, int cc, int ca){
        a=aa;
        b=bb;
        cost=cc;
        cap=ca;
        flow=0;
        olc=cc;
    }
};
vector<edge> edges;
int addedge(int a, int b, int cost, int cap){
    edges.pb(edge(a,b,cost,cap));
    edges.pb(edge(b,a,-cost, 0));
    return edges.size()-2;
}


int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
#else
    // freopen("beloved.in", "r", stdin);
    //   freopen("beloved.out", "w", stdout);
#endif

    int n=in(), m=in();
    vector<int> cities;
    for(int i=0;i<n-1;++i){
        cities.pb(in());
    }
    vector<vector<int> > g(n+1, vector<int>());
    for(int i=0;i<m;++i){
        int a=in()-1, b=in()-1, cap=in(), cost=in();
        int c=addedge(a,b, cost, cap);
        g[a].pb(c);
        g[b].pb(c^1);
        c=addedge(b,a, cost, cap);
        g[b].pb(c);
        g[a].pb(c^1);
    }
    int s=0, t=n;
    for(int i=1;i<n;++i){
        int c=addedge(i, t, -cities[i-1], INF);
        g[i].pb(c);
        g[t].pb(c^1);
    }
    ll res=0;
    vector<ll> pot(n+1, INF);
    pot[s]=0;
    bool wh=1;
    while(wh){
        wh=0;
        for(int i=0;i<edges.size();i+=2){
            int to=i;
            if(pot[edges[to].b]>pot[edges[to].a]+edges[to].cost){
               pot[edges[to].b]=pot[edges[to].a]+edges[to].cost;
               wh=1;
            }
        }
    }
    for(int i=0;i<edges.size();++i){
        edges[i].cost=edges[i].cost+pot[edges[i].a]-pot[edges[i].b];
    }
    while(true){
        vector<ll> dist(n+1, INF);
        vector<int> par(n+1, -1);
        dist[s]=0;
        vector<int> col(n+1,0);
        col[s]=1;
        set<pair<ll,int> >q;
        q.insert(mp(0,s));
        while(!q.empty()){
            int v=(*q.begin()).second;
            q.erase(q.begin());
            for(int i=0;i<g[v].size();++i){
                int to=g[v][i];
                if(edges[to].flow>=edges[to].cap) continue;
                if(dist[edges[to].b]>dist[v]+edges[to].cost){
                    dist[edges[to].b]=dist[v]+edges[to].cost;
                    q.insert(mp(dist[edges[to].b], edges[to].b));
                    par[edges[to].b]=to;
                }
            }
        }
        dist[t]+=pot[t];
        if(dist[t]>0 || dist[t]>=INF) break;
        int cur=t;
        ll flow=INF;
        while(cur!=s){
            int to=par[cur];
            flow=min(flow, edges[to].cap-edges[to].flow);
            cur=edges[to].a;
        }
        cur=t;
        while(cur!=s){
            int to=par[cur];
            edges[to].flow+=flow;
            edges[to^1].flow-=flow;
            cur=edges[to].a;
        }
        res+=flow*dist[t];
        for(int i=0;i<pot.size();++i){
            pot[i]+=dist[i];
        }
        for(int i=0;i<edges.size();++i){
            edges[i].cost=edges[i].olc+pot[edges[i].a]-pot[edges[i].b];
        }
    }
    cout<<-res<<endl;

    return 0;
}

