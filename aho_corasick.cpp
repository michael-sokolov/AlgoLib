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



using namespace std;
int _bufint;
inline int in(){
    scanf("%d", &_bufint);
    return _bufint;
}
const ll LINF=(~((1ll)<<63));
const int INF=~(1<<31);
const double eps=1e-6;
const int maxn=100000+5;
vector<int> head(maxn,-1);
vector<char> val;
vector<int> nexti, togo;
struct node{
    bool isleaf;
    int link;
    int len;
    node(){
        link=-1;
        isleaf=0;
    }
} trie[100000+5];
int tpos=1;
char buf[10000+5];
int root;
inline void add(){
    int v=root;
    int n=strlen(buf);
    for(int i=0;i<n;++i){
        int w=head[v];
        while(w!=-1){
            if(val[w]==buf[i]){
                v=togo[w];
                goto end;
            }
            w=nexti[w];
        }
        nexti.pb(head[v]);
        val.pb(buf[i]);
        togo.pb(tpos);
        head[v]=nexti.size()-1;
        trie[tpos].len=i+1;
        v=tpos++;
end:
        continue;
    }
    trie[v].isleaf=1;
}
inline bool count(int v, char c){
    int i=head[v];
    while(i!=-1){
        if(val[i]==c) return true;
        i=nexti[i];
    }
    return false;
}
inline int get(int v, int c){
    int i=head[v];
    while(i!=-1){
        if(val[i]==c) return togo[i];
        i=nexti[i];
    }
    return -1;
}
inline void add(int v, int c, int to){
    nexti.pb(head[v]);
    val.pb(c);
    togo.pb(to);
    head[v]=nexti.size()-1;
}

inline void setlinks(){
    queue<int>q;
    q.push(root);
    while(!q.empty()){
        int v=q.front();
        q.pop();
        for(int i=head[v];i!=-1;i=nexti[i]){
            q.push(togo[i]);
            int up=trie[v].link;
            int k=0;
            while(up!=-1 && count(up, val[i])==0){
                up=trie[up].link;
                ++k;
            }
            if(up==-1) up=root;
            else up=get(up, val[i]);
            trie[togo[i]].link=up;
            int up2=trie[v].link;
            for(int j=0;j<k;++j){
                add(up2, val[i], up);
                up2=trie[up2].link;
            }
        }
    }
}
inline void setnext(int v, char c){
    int cur=v;
    int k=0;
    while(cur!=-1 && count(cur,c)==0) cur=trie[cur].link,++k;
    if(cur==-1) cur=root;
    else cur=get(cur,c);
    for(int i=0;i<k;++i){
        add(v,c,cur);
        v=trie[v].link;
    }
}
inline int getup(int v){
    int w=v;
    while(v!=root && trie[v].isleaf==0){
        v=trie[v].link;
    }
    while(w!=root && trie[w].isleaf==0){
        trie[w].isleaf=1;
        trie[w].len=trie[v].len;
    }
    return trie[v].len;
}

int main(){
#ifdef SSU
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#else
    // freopen("path.in", "r", stdin);
    // freopen("path.out", "w", stdout);
#endif

    int n;
    scanf("%d%*c",&n);
    root=0;
    //root->link=root;
    for(int i=0;i<n;++i){
        gets(buf);
        add();
    }
    setlinks();
    int m;
    scanf("%d%*c",&m);
    int cur=root;
    for(int i=0,j=0;i<m;++i){
        cur=root;
        int mine=INF;
        while(true){
            char c=getchar();
            if(c=='\n'){
                j=0;
                break;
            }
            if(count(cur,c)==0) setnext(cur,c);
            cur=get(cur,c);
            if(getup(cur)>0){
                mine=min(mine, j-getup(cur)+2);
            }
            ++j;

        }
        if(mine!=INF){
            cout<<i+1<<' '<<mine<<endl;
            return 0;
        }


    }
    cout<<"Passed"<<endl;



    return 0;
}
