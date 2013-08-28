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
#include <unordered_map>
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
typedef unsigned long long uint64;  //assume this gives 64-bits


using namespace std;
int _bufint;
inline int in(){
    scanf("%d", &_bufint);
    return _bufint;
}
const ll LINF=~((1ll)<<63);
const int INF=~(1<<31);
const double eps=1e-6;

const int N=(1<<23)+8230000;
const uint64 m1  = 0x5555555555555555;
const uint64 m2  = 0x3333333333333333; 
const uint64 m4  = 0x0f0f0f0f0f0f0f0f; 
const uint64 m8  = 0x00ff00ff00ff00ff;
const uint64 m16 = 0x0000ffff0000ffff;
const uint64 m32 = 0x00000000ffffffff;
const uint64 hff = 0xffffffffffffffff;
const uint64 h01 = 0x0101010101010101;
map<ll,ll> mem;

int n;
vector<ll> g;
inline int geth(ull x){
    x = (x & m1 ) + ((x >>  1) & m1 ); 
    x = (x & m2 ) + ((x >>  2) & m2 ); 
    x = (x & m4 ) + ((x >>  4) & m4 );
    x = (x & m8 ) + ((x >>  8) & m8 );
    x = (x & m16) + ((x >> 16) & m16);
    x = (x & m32) + ((x >> 32) & m32);
    return x;
}

inline ll f(ll mask){
    if(mask==0) return 1;
    if((mask&(mask-1))==0) return 2;
    if(mem.count(mask)) return mem[mask];
    ll &res=mem[mask];
    int mak=geth(mask);
    int co=mak, mi=0;
    for(int i=0;i<n;++i){
        if(mask&(1ll<<i)){
            int c=geth(mask&(g[i]));
            if(c<=co){
                co=c;
                mi=i;
            }
            if(c==mak-1){
                mi=i;
                break;
            }
        }
    }
    int k=mi;
    mask^=(1ll<<k);
    if((mask&g[k]) == mask){

        res+=2*f(mask);
    }
    else{
         res+=f(mask);

        res+=f(mask&(g[k]));
    }
    return res;
}



bool comp(int a, int b){
    return a<b;
}

int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif
    srand(time(0));
string s;
    n=in();

    for(int i=0;i<n;++i){

        cin>>s;
        ll r=0;
        s[i]='0';
        int ss=0;
        for(int j=0;j<s.size();++j){
            if(s[j]=='1'){
                r|=(1LL<<j);
            }
        }
        g.pb(r);
    }
    cout<<f(((1ll)<<n)-1)<<endl;

    return 0;
}
