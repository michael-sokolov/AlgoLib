

import java.io.*;
import java.util.*;

public class acm {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out, true);
    static StringTokenizer st;
    static node tree[];
    public static int n;
    static int query(int v, int tl, int tr, int l, int r, int a, int b){
        if(l>r) return 0;
        if(l==tl && r==tr){
            return Math.max(tree[v].cur.length - 1 - a, 0) - Math.max(tree[v].cur.length - 1 - b, 0) ;
        }
        int tm=tl+(tr-tl)/2;
        int res=0;
        if(tl<=tm) res+=query(2*v, tl, tm, l, Math.min(r, tm), tree[v].l[a], tree[v].l[b]);
        if(tr>tm) res+=query(2*v+1, tm+1, tr, Math.max(l, tm+1), r, tree[v].r[a], tree[v].r[b]);
        return res;
    }
    public static void main(String[] args) throws Exception {
          n=nextInt();
        ArrayList<Integer> a,b;
        a=new ArrayList<Integer>();
        b=new ArrayList<Integer>();
        for(int i=0;i<n;++i){
            a.add(nextInt());
        }
        for(int i=0;i<n;++i){
            b.add(nextInt());
        }
        int map[]=new int[n+1];
        for(int i=0;i<a.size();++i){
            map[a.get(i)]=i+1;
        }
        a.clear();
        for(int i=0;i<b.size();++i){
                a.add(map[b.get(i)]);
        }
        int nn=1;
        while(nn<n){
            nn<<=1;
        }
        tree=new node[2*nn+10];
        for(int i=0, j=nn;j<2*nn;++i,++j){
            if(i<a.size())
              tree[j]=new node(a.get(i));
            else tree[j]=new node();
        }
        for(int i=nn-1;i>0;--i){
            tree[i]=new node();
            tree[i].merge(tree[2*i], tree[2*i+1]);
        }
        int m=nextInt();
        int x=0;       //!!!!!!
        ArrayList<Integer> cur=new ArrayList<Integer>();
        for(int i=0;i<tree[1].cur.length;++i) cur.add(tree[1].cur[i]);
        for(int i=0;i<m;++i){
            int a1=nextInt(), b1=nextInt(), c1=nextInt(), d1=nextInt();
            int l1=Math.min(f(a1,x,n), f(b1,x,n));
            int r1=Math.max(f(a1,x,n), f(b1,x,n));
            int l2=Math.min(f(c1,x,n), f(d1,x,n));
            int r2=Math.max(f(c1,x,n), f(d1,x,n));
            int ll=Math.abs(Collections.binarySearch(cur, l1));
            int rr=Math.abs(Collections.binarySearch(cur, r1 + 1));
            //int ans=query(1, 1, nn, l2, r2, ll)-query(1, 1, nn, l2, r2, rr);
            int ans=query(1, 1, nn, l2, r2,ll ,rr);
            x=ans+1;
            out.println(ans);
           // out.flush();
           // out.println(query(1, 1, nn, l2, r2, ll)+"  "+query(1, 1, nn, l2, r2, rr));
        }
    }
    public static int f(int z, int x, int n){
        return (z-1+x)%n+1;
    }
    public static int nextInt() throws Exception {
        if (st == null || !st.hasMoreTokens()) st = new StringTokenizer(in.readLine());
        return Integer.parseInt(st.nextToken());
    }

    public static long nextLong() throws Exception {
        if (st == null || !st.hasMoreTokens()) st = new StringTokenizer(in.readLine());
        return Long.parseLong(st.nextToken());
    }

    public static double nextDouble() throws Exception {
        if (st == null || !st.hasMoreTokens()) st = new StringTokenizer(in.readLine());
        return Double.parseDouble(st.nextToken());
    }

    public static String nextToken() throws Exception {
        if (st == null || !st.hasMoreTokens()) st = new StringTokenizer(in.readLine(), "-");
        return st.nextToken();
    }
}

class node {
    int cur[], l[], r[];

    node() {
        cur=new int[0];
    }

    node(int a) {
        cur=new int[2];
        cur[0]=a;
        cur[1]=acm.n+1;
    }

    public void merge(node a, node b) {
        cur=new int[Math.max(a.cur.length-1,0)+Math.max(0,b.cur.length-1) + 1];
        l=new int[Math.max(a.cur.length-1,0)+Math.max(0,b.cur.length-1) + 1];
        r=new int[Math.max(a.cur.length-1,0)+Math.max(0,b.cur.length-1) + 1];
        int i = 0, j = 0;
        int kl = 0, kr = 0;
        int h=0;
        while (i < a.cur.length-1 || j < b.cur.length-1) {
            int c=0;
            if(i<a.cur.length && (j>=b.cur.length || a.cur[i]<b.cur[j])){
                c=a.cur[i];
                ++i;
            }else{
                c=b.cur[j];
                ++j;
            }
            while(kl<a.cur.length && a.cur[kl]<c){
                ++kl;
            }
            while(kr<b.cur.length && b.cur[kr]<c){
                ++kr;
            }
            cur[h]=c;
            l[h]=kl;
            r[h]=kr;
            h++;
        }
        cur[h]=acm.n+1;
        l[h]=a.cur.length-1;
        r[h]=b.cur.length-1;
    }
}
