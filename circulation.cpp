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
int g[250][250];
int f[250][250];
int n;
int s, t;
vector<int> d;
bool bfs(){
    queue<int> q;
    q.push(s);
    d.assign(n,-1);
    d[s]=0;
    while(!q.empty()){
        int to=q.front();
        q.pop();
        for(int i=0;i<n;++i){
            if(g[to][i]>f[to][i] && d[i]==-1){
                d[i]=d[to]+1;
                q.push(i);
            }
        }
    }
    return d[t]!=-1;
}
vector<int> u;
ll dfs(int v, ll flow){
    if(v==t || flow==0) return flow;
    for(int &i=u[v];i<n;++i){
        if(f[v][i]<g[v][i] && d[v]+1==d[i]){
            ll cur=dfs(i, min(flow, (ll)g[v][i]-f[v][i]));
            if(cur>0){
                f[v][i]+=cur;
                f[i][v]-=cur;
                return cur;
            }
        }
    }
    return 0;
}

int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    freopen("cooling.in", "r", stdin);
    freopen("cooling.out", "w", stdout);
#endif
    n=in();
    int m=in();
    s=n, t=n+1;
    n+=2;
    for(int i=0;i<m;++i){
        int a=in()-1, b=in()-1, l=in(), c=in();
        g[a][b]=c-l;
        g[a][t]+=l;
        g[s][b]+=l;
    }
    ll res=0;
    while(bfs()){
        u.assign(n,0);
        while(1){
            ll cur=dfs(s,INF);
            if(!cur) break;
            res+=cur;
        }
    }
    for(int i=0;i<n;++i){
        if(f[i][t]<g[i][t]){
            puts("NO");

            return 0;
        }
    }
    puts("YES");
    rewind(stdin);
    n=in(), m=in();
    for(int i=0;i<m;++i){
        int a=in()-1, b=in()-1, l=in(), c=in();
        printf("%d\n", l+f[a][b]);
    }

    fflush(stdout);

    return 0;
}
