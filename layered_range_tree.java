import java.io.*;
import java.util.*;

public class acm {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out, true);
    static StringTokenizer st;
    static node[][] tree;
    static int[][] low;

    public static class node {
        int[] vals, lv, rv;

        node(int val) {
            vals = new int[]{val, Integer.MAX_VALUE};
            lv = new int[]{0, 0};
            rv = new int[]{0, 0};
        }

        node(node l, node r) {
            int n = l.vals.length + r.vals.length - 1;
            vals = new int[n];
            lv = new int[n];
            rv = new int[n];
            int i = 0, j = 0, k = 0;
            while (k < n) {
                lv[k] = i;
                rv[k] = j;
                if (j >= r.vals.length || i < l.vals.length && l.vals[i] < r.vals[j]) {
                    vals[k] = l.vals[i++];
                } else {
                    vals[k] = r.vals[j++];
                }
                ++k;
            }
        }

    }

    public static void built(int t, pair[] v) {
        Arrays.sort(v);
        int n = v.length;
        tree[t] = new node[2 * n];
        low[t] = new int[v.length];
        for (int i = 0; i < v.length; ++i) {
            low[t][i] = v[i].fi;
        }
        for (int i = n, j = 0; i < tree[t].length; ++i, ++j) {
            if (j < v.length) {
                tree[t][i] = new node(v[j].se);
            } else {
                tree[t][i] = new node(Integer.MAX_VALUE);
            }
        }
        for (int i = n - 1; i > 0; --i) {
            tree[t][i] = new node(tree[t][i * 2], tree[t][i * 2 + 1]);
        }
    }

    public static int query(int t, int v, int tl, int tr, int l, int r, int x, int y) {
        if (l > r) return 0;
        if (tl == l && tr == r) return y - x;
        int tm = tl + (tr - tl) / 2;
        int cur = 0;
        if (l <= tm) cur += query(t, 2 * v, tl, tm, l, Math.min(tm, r), tree[t][v].lv[x], tree[t][v].lv[y]);
        if (r >= tm + 1)
            cur += query(t, 2 * v + 1, tm + 1, tr, Math.max(tm + 1, l), r, tree[t][v].rv[x], tree[t][v].rv[y]);
        return cur;
    }

    public static int lowerBound(int[] array, int k) {
        int l = -1, r = array.length;
        while (l + 1 < r) {
            int m = l + (r - l) / 2;
            if (array[m] <= k - 1) l = m;
            else r = m;
        }
        return l + 1;
    }

    public static int getans(int t, int l, int r, int x, int y) {
        l = lowerBound(low[t], l);
        r = lowerBound(low[t], r + 1) - 1;
        x = lowerBound(tree[t][1].vals, x);
        y = lowerBound(tree[t][1].vals, y + 1);
        return query(t, 1, 1, tree[t][1].vals.length - 1, l + 1, r + 1, x, y);
    }

    public static void main(String[] args) throws Exception {
        int n = nextInt();
        pair[] v;
        tree = new node[25][];
        low = new int[25][];
        int[] is = new int[25];
        for (int j = 0; j < 25; ++j) {
            if ((n & (1 << j)) == 0) continue;
            v = new pair[1 << j];
            for (int i = 0; i < (1 << j); ++i) {
                int a = nextInt(), b = nextInt();
                v[i] = new pair(a, b);
            }
            is[j] = 1;
            built(j, v);
        }
        int m = nextInt();
        int last = 0;
        for (int i = 0; i < m; ++i) {
            if (nextChar() == '?') {
                int x1 = nextInt(), y1 = nextInt(), x2 = nextInt(), y2 = nextInt();
                int res = 0;
                for (int j = 0; j < 25; ++j) {
                    if (is[j] == 1) {
                        res += getans(j, x1, x2, y1, y2);
                    }
                }
                out.println(res);
                last = res;
            } else {
                int a = nextInt() + last % 100, b = nextInt() + last % 101;
                int newn = 1;
                for (int j = 0; j < 25; ++j) {
                    if (is[j] == 0) break;
                    newn += (1 << j);
                }
                v = new pair[newn];
                v[0] = new pair(a, b);
                int k = 1;
                for (int j = 0; j < 25; ++j) {
                    if (is[j] == 0) {
                        is[j] = 1;
                        built(j, v);
                        break;
                    }
                    is[j] = 0;
                    int mn = 1 << j;
                    for (int h = 0; h < mn; ++h) {
                        v[k++] = new pair(low[j][h], tree[j][mn + h].vals[0]);
                    }
                }
            }
        }

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

    static class pair implements Comparable {
        int fi, se;

        pair(int fi, int se) {
            this.fi = fi;
            this.se = se;
        }

        @Override
        public int compareTo(Object o) {
            pair cur = (pair) o;
            if (fi == cur.fi) return se - cur.se;
            return fi - cur.fi;
        }
    }
}
