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
const int maxn = 10000+20;
const int maxm = 15*maxn;
int from[maxm], to[maxm], cap[maxm], f[maxm], next_e[maxm];
int n, s, t, id;
int dist[maxn], q[maxn], first[maxn];

inline void add(int _from, int _to, int _cap){
    from[id] = _from;
    to[id] = _to;
    cap[id] = _cap;
    from[id+1] = _to;
    to[id+1] = _from;
    cap[id+1] = _cap;
}

bool bfs(){
    memset(dist, -1, n*sizeof(dist[0]));
    int qb = 0, qe = 0;
    q[qe++] = s;
    dist[s] = 0;
    while(qb < qe){
        int v = q[qb++];
        for(int i = first[v]; i != -1; i = next_e[i]){
            int _to = to[i];
            int _f = f[i], _c = cap[i];
            if(dist[_to] == -1 && _f < _c){
                dist[_to] = dist[v]+1;
                q[qe++] = _to;
                if(_to==t) goto end;
            }
        }
    }
    end:
    return (dist[t] != -1);
}

int u[maxn], p[maxn];
int uu[maxn];
int now;
int dfs(int v, int flow){
     int df;
    if(v == t || flow == 0){
        return flow;
    }
    int rest=flow;
    if(uu[v]<now){
        uu[v]=now;
        u[v]=first[v];
    }
    for(int i = u[v]; i != -1; i= u[v] = next_e[i]){
        int _to = to[i];
        int _f = f[i], _c = cap[i];
        if(_f < _c && dist[_to] == dist[v]+1){
            df = dfs(_to, min(rest, _c -_f));
            if(df > 0){
                f[i] += df;
                f[i^1] -= df;
                rest-=df;
            }
            if(!rest) return flow;
        }
    }
    return flow-rest;
}


int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
#else
    // freopen("beloved.in", "r", stdin);
    //   freopen("beloved.out", "w", stdout);
#endif

    n = in();
    ll flow = 0;
    int x;
    for(int i = 0; i < n; ++i){
        scanf("%d%d",&x,&x);
    }
    int m = in();
    memset(first, -1, n*sizeof(first[0]));
    memset(next_e, -1, m*sizeof(next_e[0]));
    int a,b,c;
    for(int i = 0; i < m; ++i){
        scanf("%d%d%d", &a,&b,&c);
        --a;
        --b;
        add(a, b, c);
        next_e[id] = first[a];
        first[a] = id;
        next_e[id+1] = first[b];
        first[b] = id+1;
        id += 2;
    }
    s = 0; t = n-1;
    now=1;
    while(bfs()){
        flow+=dfs(s, INF);
        ++now;
    }
    printf("%lld\n", flow);
    for(int i = 0; i < id; i+=2){
        if(f[i] >= 0)
            printf("%d %d %d\n", from[i]+1, to[i]+1, f[i]);
        else
            printf("%d %d %d\n", from[i+1]+1, to[i+1]+1, f[i+1]);
    }

    return 0;
}

