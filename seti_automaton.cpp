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
const ll LINF=~((1ll)<<63);
const int INF=~(1<<31);
const double eps=1e-8;
struct node{
    int suf;
    map<char, int> to;
    int l, r;
    int len;
    int dp;
    node(){
        l=r=-1;
        dp=1;
    }
};
vector<node> at;
int last=0;
void add(int i, char c){
    int cur=at.size();
    at.pb(node());
    at[cur].l=at[cur].r=i;
    at[cur].len=at[last].len+1;
    int p=last;
    while(p!=-1){
        if(at[p].to.count(c)==0){
            at[p].to[c]=cur;
        }else break;
        p=at[p].suf;
    }
    if(p!=-1){
        int q=at[p].to[c];
        if(at[p].len == at[q].len-1){
            at[cur].suf=q;
        }else{
            int clone=at.size();
            at.pb(node());
            at[clone]=at[q];
            at[clone].len=at[p].len+1;
            at[q].suf=clone;
            at[cur].suf=clone;
            while(p!=-1){
                if(at[p].to[c]==q)
                    at[p].to[c]=clone;
                p=at[p].suf;
            }
        }
    }else{
        at[cur].suf=0;
    }
    last=cur;
}
vector<int> u;
vector<vector<int> > g;
void dfs(int v){
    if(u[v]) return;
    u[v]=1;
    for(int i=0;i<g[v].size();++i){
        int to=g[v][i];
        dfs(to);
        at[v].r=max(at[to].r, at[v].r);
        at[v].l=min(at[to].l, at[v].l);
    }
}

int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
#endif
    at.pb(node());
    at[0].len=0;
    at[0].suf=-1;
    string s;
    cin>>s;
    for(int i=0;i<s.size();++i){
        add(i, s[i]);
    }
    ll res=0;
    g.assign(at.size(), vector<int>());
    for(int i=at.size()-1;i>0;--i){
        g[at[i].suf].pb(i);
    }
    u.assign(at.size(),0);
    dfs(0);
    for(int i=1;i<at.size();++i){
        int longest=at[i].len;
        int shortest=at[at[i].suf].len;
        int l=at[i].l, r=at[i].r;
        if(r-l>=shortest){
            int m=min(r-l, longest);
            res+=m-shortest;
        }
    }
    cout<<res<<endl;

    return 0;
}
