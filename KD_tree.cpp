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

ll gcd(ll a, ll b){
    if(b == 0) return a;
    else return gcd(b, a%b);
}

const ll LINF=~((1ll)<<63);
const int INF=~(1<<31);
const double eps=1e-6;
struct node{
    int lx,ly,rx,ry;
    int mi,lazy;
    node(){
        mi = INF;
        lazy = 0;
    }
};
bool compX(pair<pair<int,int>,int> a, pair<pair<int,int>,int> b){
    return a.first.first < b.first.first;
}
bool compY(pair<pair<int,int>,int> a, pair<pair<int,int>,int> b){
    return a.first.second < b.first.second;
}
const int maxn=1000000;
node tree[maxn];
vector<pair<pair<int,int>,int> > init;
void rmin(int &a, int b){
    a = min(a,b);
}
void rmax(int &a, int b){
    a = max(a,b);
}
void build(int v, int l, int r, bool x){
    tree[v].lazy = 0;
    tree[v].mi = tree[v].lx = tree[v].ly = INF;
    tree[v].rx = tree[v].ry = -INF;
    for(int i = l; i < r; ++i){
        rmin(tree[v].lx, init[i].first.first);
        rmin(tree[v].ly, init[i].first.second);
        rmin(tree[v].mi, init[i].second);
        rmax(tree[v].rx, init[i].first.first);
        rmax(tree[v].ry, init[i].first.second);
    }
    if(r - l == 1) return;
    int m = (l + r) / 2;
    nth_element(init.begin()+l,init.begin()+m, init.begin()+r, (x)?(compX):(compY));
    build(2*v, l, m, !x);
    build(2*v+1, m, r, !x);
}
void push(int v){
    if(tree[v].lazy == 1){
        tree[v].lazy = 0;
        if(2*v < maxn){
            tree[v*2].lazy = 1;
            tree[v*2].mi = tree[v].mi;
        }
        if(2*v+1 < maxn){
            tree[v*2+1].lazy = 1;
            tree[v*2+1].mi = tree[v].mi;
        }
    }
}
void setmin(int v, int x1, int y1, int x2, int y2, int val){
    if(x1 > tree[v].rx || x2 < tree[v].lx || y1 > tree[v].ry || y2 < tree[v].ly) return;
    if(x1 <= tree[v].lx && x2 >= tree[v].rx && y1 <= tree[v].ly && y2 >= tree[v].ry){
        tree[v].lazy = 1;
        tree[v].mi = val;
        return;
    }
    push(v);
    setmin(2*v, x1, y1, x2, y2, val);
    setmin(2*v+1, x1, y1, x2, y2, val);
    tree[v].mi = min(tree[v*2].mi, tree[v*2+1].mi);
}
int getmin(int v, int x1, int y1, int x2, int y2){
    if(x1 > tree[v].rx || x2 < tree[v].lx || y1 > tree[v].ry || y2 < tree[v].ly) return INF;
    if(x1 <= tree[v].lx && x2 >= tree[v].rx && y1 <= tree[v].ly && y2 >= tree[v].ry){
        return tree[v].mi;
    }
    push(v);
    return min(getmin(2*v, x1, y1, x2, y2), getmin(2*v+1, x1, y1, x2, y2));
}
int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //	freopen("output.txt", "w", stdout);
#else
    //freopen("kth.in", "r", stdin);
    //freopen("kth.out", "w", stdout);
#endif
    int n=in();
    for(int i=0;i<n;++i){
        int a = in(), b = in(), c = in();
        init.pb( mp( mp(a,b), c) );
    }
    build(1, 0, init.size(), true);
    int m=in();
    for(int i = 0; i < m; ++i){
        char cc;
        scanf("\n%c", &cc);
        if(cc == '='){
            int x1 = in(), y1 = in(), x2 = in(), y2 = in(), val = in();
            setmin(1, x1, y1, x2, y2, val);
        }
        else{
            int x1 = in(), y1 = in(), x2 = in(), y2 = in();
            int val = getmin(1, x1, y1, x2, y2);
            if(val != INF)
                 printf("%d\n", val);
            else puts("NO");
        }
    }

    return 0;
}

