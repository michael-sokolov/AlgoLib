#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <set>
#include <map>
using namespace std;
#define pb push_back
#define mp make_pair
int buf;
int in(){
	scanf("%d", &buf);
	return buf;
}
struct rib{
	int a, b;
	int c;
	int flow;
	int cap;
	rib(int aa, int bb, int cc, int fflow, int ccap){
		a=aa;
		b=bb;
		c=cc;
		flow=fflow;
		cap=ccap;
	}
};
const int INF=~(1<<31);
vector<rib> edge;
int main(){
	int n=in();
	vector<vector<int> > g(n, vector<int>(n,0));
	vector<int> sums;
	for(int i=0;i<n;++i){
		int sum=0;
		for(int j=0;j<n;++j){
			g[i][j]=in();
			sum+=g[i][j];
		}
		sums.pb(sum);
	}

	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			g[i][j]=sums[i]-g[i][j];
		}
	}
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			edge.pb(rib(i, j+n, g[i][j], 0,1));
			edge.pb(rib(j+n, i, -g[i][j], 0,0));
		}
	}
	int s=n+n;
	int t=n+1+n;
	for(int i=0;i<n;++i){
		edge.pb(rib(s, i, 0, 0,1));
		edge.pb(rib(i, s, 0, 0,0));
	
		edge.pb(rib(t, i+n, 0, 0,0));
		edge.pb(rib(i+n, t, 0, 0,1));
	}
	long long ans=0;
	for(int i=0;i<n;++i){
		vector<int> d(n+n+2,INF-10000000);
		d[s]=0;
		vector<int> p(n+n+2, -1);
		bool tt=1;
		for(int j=0;j<n;++j){
			tt=1;
			for(int k=0;k<edge.size();++k){
				if(d[edge[k].b]>d[edge[k].a]+edge[k].c && edge[k].flow<edge[k].cap){
					d[edge[k].b]=d[edge[k].a]+edge[k].c;
					p[edge[k].b]=k;
					tt=0;
				}
			}
			if(tt) break;
		}
		ans+=d[t];
		//cout<<d[t]<<endl;
		int cur=p[t];
		while(cur!=-1){
			edge[cur].flow++;
			edge[cur^1].flow--;
			cur=p[edge[cur].a];
		}
	}
	cout<<ans<<endl;
	




	return 0;
}
