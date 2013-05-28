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
ll dist(pair<ll,ll> a, pair<ll,ll> b){
    return (a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second);
}
 
int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
#endif
    int n;
    while(cin>>n){
        if(!n) break;
        vector<pair<ll,ll> > v;
        for(int i=0;i<n;++i){
            int a=in(),b=in();
            v.pb(mp(b,a));
        }
       /* for(int i=0;i<n;++i){
            for(int j=i+1;j<n;++j){
                cout<<sqrt(dist(v[i], v[j]))<<endl;
            }
        }*/
 
        sort(v.begin(), v.end());
        set<pair<ll,ll> > s;
        ll res=dist(v[0], v[1]);
        int ans1=0, ans2=1;
        s.insert(mp(v[0].second, v[0].first));
        s.insert(mp(v[1].second, v[1].first));
        int l=0;
        for(int i=2;i<n;++i){
            while((v[l].first-v[i].first)*(v[l].first-v[i].first)>res){
                s.erase(mp(v[l].second, v[l].first));
                ++l;
            }
            set<pair<ll,ll> >::iterator to=s.lower_bound(mp(v[i].second-(ll)(sqrt(res)+0.5)-1,-1000000000));
            set<pair<ll,ll> >::iterator end=s.upper_bound(mp(v[i].second+(ll)(sqrt(res)+0.5)+1,1000000000));
            //to=s.begin();
            //end=s.end();
            while(to!=s.end()){
                pair<ll,ll> cur=*to;
                ll d=dist(v[i], mp(cur.second, cur.first));
                if(d<res){
                    res=d;
                    ans1=i;
                    ans2=lower_bound(v.begin(), v.end(), mp(cur.second, cur.first))-v.begin();
                }
                if(to==end) break;
                ++to;
            }
            s.insert(mp(v[i].second, v[i].first));
        }
        printf("%.10lf\n", sqrt(res+0.));
    }
 
    return 0;
}
