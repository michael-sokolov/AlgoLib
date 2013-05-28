#define _USE_MATH_DEFINES
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <set>
#include <utility>
#include <map>
#include <cstdlib>
#include <queue>
#include <stack>
#include <deque>
#include <iterator>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <complex>
#include <functional>
#include <numeric>

#include <exception>
using namespace std;
typedef long long ll;
typedef complex<double> base;
#define mp make_pair
#define pb push_back
#define ro(a) a.first, a.second
#define clx complex<double> 
int buf;
inline int in(){
	scanf("%d", &buf);
	return buf;
}
const int INF=~(1<<31);
const ll LINF=~(1ll<<63);
const double eps=1e-7;

inline bool getcurtime(){
	if(clock()/(CLOCKS_PER_SEC+0.)>0.45) return 0;
	else return 1;
}
vector<int>h;
int get(int a){
	if(h[a]==a) return a;
	return h[a]=get(h[a]);
}
bool link(int a, int b){
	a=get(a);
	b=get(b);
	if(a==b) return false;
	if(rand()&1) swap(a,b);
	h[a]=b;
	return true;
}
vector<vector<pair<int,int> > > g;
vector<int> tin, tout;
int timer=0;
int nn;
int lca[600][15];
int ma[600][15];
void dfs(int v, int p, int w){
	tin[v]=timer++;
	lca[v][0]=p;
	ma[v][0]=w;
	for(int j=1;j<=nn;++j){
		lca[v][j]=lca[lca[v][j-1]][j-1];
		ma[v][j]=max(ma[lca[v][j-1]][j-1], ma[v][j-1]);
	}
	for(int i=0;i<g[v].size();++i){
		int to=g[v][i].first;
		if(tin[to]==-1){
			dfs(to, v, g[v][i].second);
		}

	}
	tout[v]=timer++;
}
bool isp(int t, int p){
	int a=p;
	int b=t;
	if(tin[a]<=tin[b] && tout[a]>=tout[b]){
		return 1;
	}
	return 0;
}
int getans(int a, int b){
	if(isp(a,b)){
		swap(a,b);
	}
	int res=0;
	for(int i=nn;i>=0;--i){
		if(!isp(a,lca[b][i])){
			res=max(res, ma[b][i]);
			b=lca[b][i];
		}
	}
	res=max(res, ma[b][0]);
	return res;
}
int main(){
	int n=in(), m=in();
	vector<pair<int,pair<int,int> > > v, w;
	for(int i=0;i<m;++i){
		int a=in()-1, b=in()-1, c=in();
		if(a==b) return 2;
		v.pb(mp(c, mp(a,b)));
	}
	ll cost=0;
	sort(v.begin(), v.end());
	for(int i=0;i<n;++i) h.pb(i);
	int lub=0;
	for(int i=0;i<m;++i){
		if(link(v[i].second.first, v[i].second.second)){
			cost+=v[i].first;
			w.pb(v[i]);
			lub=v[i].second.second;
			v[i].first=-1;
		}
	}
	printf("Cost: %lld", cost);
	g.assign(n, vector<pair<int,int> >());
	for(int i=0;i<w.size();++i){
		pair<int,int >cur=w[i].second;
		g[cur.first].pb(mp(cur.second, w[i].first));
		g[cur.second].pb(mp(cur.first,w[i].first));
	}
	nn=1;
	int tn=n;
	while(tn){
		tn>>=1;
		nn++;
	}
	tin.assign(n, -1);
	tout.assign(n, -1);
	dfs(lub, lub, 0);
	ll ans=LINF;
	for(int i=0;i<m;++i){
		if(v[i].first<0) continue;
		pair<int,int> cur=v[i].second;
 		int rr=max(getans(cur.first, cur.second), getans(cur.second, cur.first));
		ans=min(ans, cost-rr+v[i].first);
	}
	if(ans==LINF) ans=-1; 
	printf("\nCost: %lld\n", ans);



	return 0;
}
