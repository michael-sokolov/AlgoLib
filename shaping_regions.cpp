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

struct event{
    int l, r;
    short color;
    short time;
    int u, d;
    event(int l, int r, short color, short time, int u, int d){
        this->l=l;
        this->r=r;
        this->color=color;
        this->time=time;
        this->u=u;
        this->d=d;
    }
    event(){

    }


};
inline bool operator< (const event & s1, const event & s2)
{
    return  s1.time < s2.time;
}
bool comp(const event & s1, const event & s2){
    return s1.l<s2.l;
}
event v[1003];

struct coms{
    inline bool operator()(const short a, const short b){
        return v[a].time < v[b].time;
    }
};

int ans[2505];
int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //  freopen("output.txt", "w", stdout);
#endif

    int a=in(), b=in(), n=in();
            vector<int> y;
            y.reserve(2*n);

            for(int i=0;i<n;++i){
                int llx=in(), lly=in(), urx=in(), ury=in(), color=in();
                
                    v[i]=(event(llx, urx, color, i + 1, lly, ury - 1));
                    y.pb(lly);
                    y.pb(ury);
                
            }
            y.pb(0);
            y.pb(a);
            sort(y.begin(), y.end());
            y.erase(unique(y.begin(), y.end()), y.end());
            stable_sort(v, v+n,comp);
            vector<int> nums;
            v[n]=event(0,a,1,0, 0,0);
            nums.pb(0);
            nums.pb(a);
            for(int j=0;j<n;++j){
                nums.pb(v[j].l);
                nums.pb(v[j].r);
            }
            sort(nums.begin(), nums.end());
            nums.erase(unique(nums.begin(), nums.end()), nums.end());
            priority_queue<int, vector<int>, coms > q;

            for(int i=0;i<y.size()-1;++i){
                while(!q.empty()) q.pop();
                q.push(n);
                int ct=y[i];
                int mn=y[i+1]-ct;
                int last=0, lastc=1;
                for(int j=0, k=0;j<nums.size();++j){
                    int curt=nums[j];
                    while(k<n && curt>=v[k].l){
                        if(v[k].d>=ct && v[k].u<=ct)
                        q.push(k);
                        ++k;
                    }
                    ans[lastc]+=(curt-last)*mn;
                    lastc=1;
                    while(q.empty()==0){
                        int ne=q.top();
                        lastc=v[ne].color;
                        if(v[ne].r<=curt){
                            q.pop();
                        }else break;
                    }
                    last=curt;
                }
                ans[lastc]+=(b-last)*mn;

            }
            // ans[1]-=a;
            for(int i=1;i<=2503;++i){
                if(ans[i]>0){
                   printf("%d %d\n",i,ans[i]);
                }
            }




    return 0;
}
