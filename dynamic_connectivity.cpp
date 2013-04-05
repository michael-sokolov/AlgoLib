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
const int maxn=3*100005;
int h[maxn], si[maxn];
stack<int> s1,s2;
int ans=0;
int get(int a){
    while(h[a]!=a) a=h[a];
    return a;
}
void hset(int a, int b){
    a=get(a);
    b=get(b);
    if(a==b)
        return;
    ans--;
    if(si[a]>si[b]) swap(a,b);
    s1.push(a);
    h[a]=b;
    if(si[a]==si[b]){
        si[b]++;
        s2.push(b);
    }
}
void stop(){
    s1.push(-1);
    s2.push(-1);
}
void start(){
    while(!s1.empty())    {
        int cur=s1.top();
        s1.pop();
        if(cur!=-1) ++ans;
        else break;
        h[cur]=cur;
    }
    while(!s2.empty()){
        int cur=s2.top();
        s2.pop();
        if(cur==-1) break;
        --si[cur];
    }
}

struct node{
    int l, r;
    int a, b;
    node(int _a, int _b, int _l, int _r){
        a=_a;
        b=_b;
        l=_l;
        r=_r;
    }
    bool operator < (const node &a) const {
        return this->l < a.l;
    }
};
vector<int> answ;
vector<int> isque;
int maxk;
void divide(int l, int r,const vector<node> &v){
    if(l>=maxk) return;
    if(l==r){
        if((isque[l+1]-isque[l])==1){
            answ.pb(ans);
        }
        return;
    }
    int cc=isque[min(r+1, maxk)]-isque[l];
    if(!cc) return;
    int m=l+(r-l)/2;
    vector<node> le;
    stop();
    for(int i=0;i<v.size();++i){
        if(v[i].l>r || v[i].r<l) continue;

        if((v[i].r>=r && v[i].l<=l)){
             hset(v[i].a, v[i].b);
        }else{
            le.pb(v[i]);
        }
    }
    divide(l, m, le);
    divide(m+1, r, le);
    start();
}

int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    int n=in(), k=in();
    char type;
    vector<node> query;
    for(int i=0;i<maxn;++i) h[i]=i;
    map<pair<int,int> , int> t;
    int kk=1;
    maxk=k;
    while(kk<k) kk<<=1;
    isque.assign(k,0);
    for(int i=0;i<k;++i){
        scanf("\n%c", &type);
        if(type=='?'){
            isque[i]=1;
        }
        else{
            int a=in()-1, b=in()-1;
            if(a>b) swap(a,b);
            if(type=='-'){
                query[t[mp(a,b)]].r=i;
                t.erase(mp(a,b));
            }else{
                t[mp(a,b)]=query.size();
                query.pb(node(a,b,i,INF));
            }
        }
    }
    isque.insert(isque.begin(),0);
    for(int i=1;i<isque.size();++i){
        isque[i]+=isque[i-1];
    }
    ans=n;
    divide(0, kk-1, query);
    for(int i=0;i<answ.size();++i){
        printf("%d\n", answ[i]);
    }
    return 0;
}

