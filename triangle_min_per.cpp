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
inline double dist(const pair<int,int> &a, const pair<int,int> &b){
    return sqrt((a.first-b.first)*(a.first-b.first+0.) + (a.second-b.second)*(a.second-b.second+0.));
}
inline double dist(const pair<int,int> &a,const pair<int,int> &b, const pair<int,int>& c){
    return dist(a,b)+dist(b,c)+dist(c,a);
}
vector<pair<int,int> > v;
bool comp(int a, int b){
    return v[a]<v[b];
}
struct setcm{
    bool operator()(int a, int b){
        if(v[a].second == v[b].second) return v[a].first<v[b].first;
        return v[a].second<v[b].second;
    }
};

int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
#endif
    int n=in();
    vector<int> w;
    int lr=0;
    int la=100000000, lb=100000000;

    for(int i=0;i<n;++i){
        int a=in(),b=in();
        v.pb(mp(a,b));
        w.pb(i);
    }

    sort(w.begin(), w.end(), comp);
    for(int i=0;i<n;++i){
        pair<int,int> cur=v[w[i]];
        if(cur.first==la && cur.second==lb) ++lr;
        else lr=0;
        if(lr>=2){
            puts("0.0000000");
            printf("%d %d %d", w[i]+1, w[i-1]+1, w[i-2]+1);
            return 0;
        }
        la=cur.first;
        lb=cur.second;
    }
    multiset<int, setcm> s;
    double res=dist(v[w[0]], v[w[1]], v[w[2]]);
    int ans1=w[0], ans2=w[1], ans3=w[2];
    s.insert(ans1);
    s.insert(ans2);
    s.insert(ans3);
    int l=0;
    for(int i=3;i<w.size();++i){
        while(std::abs(v[w[l]].first-v[w[i]].first)>res/2){
            s.erase(s.find(w[l]));
            ++l;
        }
        v.pb(mp(-1000000000, v[w[i]].second-(int)(res/2-0.5)));
        multiset<int, setcm>::iterator to=s.lower_bound((int)v.size()-1);
        v.pb(mp(1000000000,v[w[i]].second+(int)(res/2-0.5)));
        multiset<int,setcm>::iterator end=s.upper_bound((int)v.size()-1);
        while(to!=end){
            int cur=*to;

            multiset<int,setcm>::iterator t2=to;
            ++t2;
            double dd=dist(v[w[i]], v[cur]);
            while(t2!=s.end()){
                int cur2=*t2;
                double d=dist(v[cur], v[cur2]) + dist(v[w[i]], v[cur2]) + dd;
                if(d<res){
                    res=d;
                    ans1=w[i];
                    ans2=cur;
                    ans3=cur2;
                }
                if(t2==end) break;
                ++t2;
            }
            ++to;
        }
        s.insert(w[i]);
    }

    printf("%.7lf\n%d %d %d\n", res , ans1+1, ans2+1, ans3+1);

    return 0;
}
