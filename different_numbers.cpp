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
    node *l, *r;
    int val;
    int sum;
    node(){
        val=0;
        sum=0;
        l=r=NULL;
    }
    void update(){
        sum=val;
        if(l!=NULL) sum+=l->sum;
        if(r!=NULL) sum+=r->sum;
    }
    node(node *v){
        val=0;
        sum=0;
        l=v->l;
        r=v->r;
        update();
    }
};
node* build(int tl, int tr){
    if(tr == tl) return new node();
    int tm = (tr+tl)/2;
    node *cur = new node();
    cur->l=build(tl, tm);
    cur->r=build(tm+1,tr);
    return cur;
}
int get(node *v,int tl, int tr, int l, int r){
    if(v==NULL) return 0;
    if(l>r) return 0;
    if(tl==l && tr==r) return v->sum;
    int tm=(tl+tr)/2;
    return get(v->l, tl, tm, l, min(r, tm))+get(v->r,tm+1,tr,max(l, tm+1),r);
}
node* update(node *v, int tl, int tr, int i, int d){
    node *cur = new node(v);
    if(tl==tr){
        cur->val=d;
        cur->update();
        return cur;
    }
    int tm=(tl+tr)/2;
    if(i<=tm) cur->l=update(cur->l, tl, tm, i, d);
    else cur->r=update(cur->r,tm+1,tr,i,d);
    cur->update();
    return cur;
}

int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //	freopen("output.txt", "w", stdout);
#else
    //  freopen("i.dat", "r", stdin);
    //freopen("i.ans", "w", stdout);
#endif
   vector<node*> tree;
   int n=in(), q=in();
   tree.pb(build(1,n));
   map<int,int> m;
   node *last=tree.back();
   for(int i=0;i<n;++i){
       int a=in();
       if(m.count(a)==0){
           last=update(last,1,n,i+1,1);
           tree.pb(last);
           m[a]=i+1;
       }else{
           last=update(last,1,n,m[a],0);
           last=update(last,1,n,i+1,1);
           tree.pb(last);
           m[a]=i+1;
       }
   }
   for(int i=0;i<q;++i){
       int a=in(), b=in();
       int res=get(tree[b], 1,n,a,b);
       printf("%d\n",res);
   }


    return 0;
}
