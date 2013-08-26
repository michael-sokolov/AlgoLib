import java.io.*;
import java.util.*;

public class acm {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out, true);
    static StringTokenizer st;
    static int nn;
    static node lastP, lastR;

    static class node {
        node l, r;
        int val;

        node(node a) {
            this.l = a.l;
            this.r = a.r;
            this.val = a.val;
        }

        node(int val) {
            l = r = null;
            this.val = val;
        }
    }

    public static int get(node v, int tl, int tr, int i) {
        if (tl == tr) return v.val;
        int tm = (tl + tr) / 2;
        if (i <= tm) return get(v.l, tl, tm, i);
        else return get(v.r, tm + 1, tr, i);
    }

    public static node set(node v, int tl, int tr, int i, int val) {
        node cur = new node(v);
        if (tl == tr) {
            cur.val = val;
            return cur;
        }
        int tm = (tr + tl) / 2;
        if (i <= tm) cur.l = set(v.l, tl, tm, i, val);
        else cur.r = set(v.r, tm + 1, tr, i, val);
        return cur;
    }

    public static int getParent(node v, int p) {
        int pp = get(v, 1, nn, p);
        if (pp == p) return p;
        else return getParent(v, pp);
    }

    public static void link(node v, node r, int a, int b) {
        a = getParent(v, a);
        b = getParent(v, b);
        int ra = get(r, 1, nn, a);
        int rb = get(r, 1, nn, b);
        if (ra < rb) {
            lastP = set(v, 1, nn, a, b);
        } else {
            lastP = set(v, 1, nn, b, a);
        }
        if (ra == rb) {
            lastR = set(r, 1, nn, a, ra + 1);
        } else lastR = r;
    }

    public static node build(int tl, int tr, boolean x) {
        if (tl == tr) {
            node cur = new node((x) ? (tl) : (1));
            return cur;
        }
        node cur = new node(-1);
        int tm = (tl + tr) / 2;
        cur.l = build(tl, tm, x);
        cur.r = build(tm + 1, tr, x);
        return cur;
    }

    public static void main(String[] args) throws Exception {
        //in = new BufferedReader(new FileReader("input.txt"));
        long startTime = System.currentTimeMillis();
        int n = nextInt(), m = nextInt();
        ArrayList<node> parents = new ArrayList<node>();
        ArrayList<node> ranks = new ArrayList<node>();
        nn = 1;
        while (nn < n) nn <<= 1;
        parents.add(build(1, nn, true));
        ranks.add(build(1, nn, false));
        for (int i = 0; i < m; ++i) {
            if (nextChar() == '+') {
                int v = nextInt(), a = nextInt(), b = nextInt();
                link(parents.get(v), ranks.get(v), a, b);

            } else {
                int v = nextInt(), a = nextInt(), b = nextInt();
                a = getParent(parents.get(v), a);
                b = getParent(parents.get(v), b);
                if (a == b) {
                    out.println("YES");
                } else out.println("NO");
            }
            parents.add(lastP);
            ranks.add(lastR);
        }
        out.println("Total Time: " + (System.currentTimeMillis() - startTime));
        out.flush();
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
        if (st == null || !st.hasMoreTokens()) st = new StringTokenizer(in.readLine());
        return st.nextToken();
    }

    public static char nextChar() throws Exception {
        if (st == null || !st.hasMoreTokens()) st = new StringTokenizer(in.readLine());
        return st.nextToken().charAt(0);
    }
}
