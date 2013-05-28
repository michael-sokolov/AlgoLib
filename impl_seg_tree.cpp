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
struct node{
    node *l, *r;
    int sl, sr;
    int size;
    int cl, cr;
    int i;
    bool del;
    node(int n, int ii, int can){
        del=0;
        size=n;
        i=ii;
        l=r=NULL;
        sl=size/2;
        sr=size-size/2-1;
        cl=can/2;
        cr=can-can/2-1;
    }
};
node *root;
void destroy(node *v, int i){
    if(v->sl+1==i && !v->del){
        v->del=1;
        v->size--;
        return;
    }
    if(i<=v->sl){
        if(v->l==NULL){
            v->l=new node(v->sl, v->i, v->cl);
        }
        destroy(v->l, i);
        v->sl--;
    }else{
        if(v->r==NULL){
            v->r=new node(v->sr, v->i+v->cl+1, v->cr);
        }
        destroy(v->r, i-v->sl-!(v->del));
        v->sr--;
    }
    v->size--;
}
int get(node *v, int i){
    if(v->sl+1==i && !v->del){
        return v->i+v->cl;
    }
    if(i<=v->sl){
        if(v->l==NULL){
            v->l=new node(v->sl, v->i, v->cl);
        }
        return get(v->l, i);
    }else{
        if(v->r==NULL){
            v->r=new node(v->sr, v->i+v->cl+1, v->cr);
        }
        return get(v->r, i-v->sl-!(v->del));
    }
}

int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
#endif
    int n=in(), m=in();
    int nn=n;
    while(nn<n){
        nn<<=1;
    }
    root=new node(nn, 1, nn);
   // root->l=new node(root->sl, 1, root->sl);
   // root->r=new node(root->sr, nn/2+2, root->sr);
    for(int i=0;i<m;++i){
        char c;
        scanf("\n%c", &c);
        if(c=='D'){
            destroy(root, in());
        }else{
            printf("%d\n", get(root, in()));
        }
    }


    return 0;
}
