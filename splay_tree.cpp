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
const int maxn = 2000006;
 
struct node;
node *null;
 
 
struct node{
    node *l, *r, *p;
    int s, m, val;
    bool rev;
    node(int _val){
        val = m = _val;
        rev = 0;
        s = 1;
        l = r = p = null;
    }
    node(){
        val = m = INF;
        rev = s = 0;
        l = r = p = this;
    }
    void update(){
        m = min(val, min(l->m, r->m));
        s = (this!=null) + l->s + r->s;
    }
    void push(){
        if(rev) swap(l, r);
        l->rev ^= rev, r->rev ^= rev;
        rev = 0;
    }
};
 
void rotate(node *x){
    node *p = x->p;
    node *pp = p->p;
    if(pp != null){
        if(pp->l == p)  pp->l = x;
        else pp->r = x;
    }
    x->p = pp;
    if(p->l == x){
        x->r->p = p;
        p->l = x->r;
        x->r = p;
    }else{
        x->l->p = p;
        p->r = x->l;
        x->l = p;
    }
    p->p = x;
    p->update();
    x->update();
}
 
void splay(node *x){
    while(x->p != null){
        x->p->p->push();
        x->p->push();
        x->push();
        if(x->p->p == null) rotate(x);
        else if((x->p->p->l == x->p) ^ (x->p->r == x))
            rotate(x->p),rotate(x);
        else
            rotate(x),rotate(x);
    }
}
 
node* get(node *v, int i){
    v->push();
    if(i <= v->l->s) return get(v->l, i);
    if(i == v->l->s+1) return v;
    return get(v->r, i-v->l->s-1);
}
 
void split(node *root, int i, node **l, node **r){
    if(i == 0) return (void)(*l=null,*r=root);
    root = get(root, i);
    splay(root);
    *l = root;
    *r = root->r;
    root->r = (*r)->p = null;
    (*l)->update(), (*r)->update();
}
 
void merge(node *l, node *r, node **root){
    if(l==null || r==null) return (void)(*root=(l==null)?(r):(l));
    l = get(l, l->s);
    splay(l);
    l->r = r;
    r->p = *root = l;
    (*root)->update();
}
 
int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //  freopen("output.txt", "w", stdout);
#else
    // freopen("c.in", "r", stdin);
    // freopen("c.out", "w", stdout);
#endif
    int n = in(), m = in();
    null = new node();
    node *root = null;
    for(int i = 0; i < n; ++i){
        merge(root, new node(in()), &root);
    }
    for(int i = 0; i < m; ++i){
        int c = in(), l = in(), r = in();
        node *tl, *tr, *tm;
        split(root, r, &tm, &tr);
        split(tm, l-1, &tl, &tm);
        if(c == 1) tm->rev ^= 1;
        else printf("%d\n", tm->m);
        merge(tl, tm, &tm);
        merge(tm, tr, &root);
    }
    return 0;
}
