import java.io.*;
import java.util.*;

public class acm {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out, true);
    static StringTokenizer st;


    public static void main(String[] args) throws Exception {
        // in = new BufferedReader(new FileReader("windows.in"));
        // out = new PrintWriter("windows.out");
        int n = nextInt();
        int[][] v = new int[n * 2][];
        int max = 2 * 100005;

        for (int i = 0; i < n; ++i) {
            int x1 = nextInt() + max, y1 = nextInt() + max, x2 = nextInt() + max, y2 = nextInt() + max;
            v[i * 2] = (new int[]{x1, y1, y2, 1});
            v[i * 2 + 1] = (new int[]{x2 + 1, y1, y2, -1});
        }

        Arrays.sort(v, new Comparator<int[]>() {
            @Override
            public int compare(int[] a, int[] b) {
                return a[0] - b[0];
            }
        });
        SegTree tree = new SegTree(2 * max);
        int res[] = new int[]{-1, 0, 0};
        for (int i = 0, j = 0; j < v.length; ) {
            i = v[j][0];
            while (j < v.length) {
                if (v[j][0] == i) {
                    int cur[] = v[j];
                    tree.add(1, 1, tree.n, cur[1], cur[2], cur[3]);
                } else break;
                ++j;
            }
            int cur[] = tree.query();
            if (cur[0] > res[0]) {
                res[0] = cur[0];
                res[1] = i - max;
                res[2] = cur[1] - max;
            }

        }
        out.println(res[0] + "\n" + res[1] + " " + res[2]);
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
        if (st == null || !st.hasMoreTokens()) {
            String cur = in.readLine();
            st = new StringTokenizer(cur);
        }
        return st.nextToken();
    }

    public static char nextChar() throws Exception {
        if (st == null || !st.hasMoreTokens()) st = new StringTokenizer(in.readLine());
        return st.nextToken().charAt(0);
    }

    static class SegTree {
        int n;
        int[][] tree;
        int[] lazy;

        SegTree(int n) {
            this.n = 1;
            while (this.n < n) this.n <<= 1;
            tree = new int[this.n * 2][2];
            lazy = new int[this.n * 2];
            for (int i = this.n; i < this.n * 2; ++i) tree[i][1] = i + 1 - this.n;
            for (int i = this.n - 1; i > 0; --i) tree[i][1] = tree[i * 2][1];
        }

        void push(int v) {
            tree[v][0] += lazy[v];
            if (2 * v < tree.length) {
                lazy[v * 2] += lazy[v];
                lazy[2 * v + 1] += lazy[v];
            }
            lazy[v] = 0;
        }

        void add(int v, int tl, int tr, int l, int r, int d) {
            push(v);
            if (l > r) return;
            if (tl == l && tr == r) {
                lazy[v] += d;
                push(v);
                return;
            }
            int tm = (tl + tr) / 2;
            add(v * 2, tl, tm, l, Math.min(tm, r), d);
            add(v * 2 + 1, tm + 1, tr, Math.max(tm + 1, l), r, d);
            compose(v);
        }

        void compose(int v) {
            if (tree[v * 2][0] > tree[v * 2 + 1][0]) {
                tree[v][0] = tree[v * 2][0];
                tree[v][1] = tree[v * 2][1];
            } else {
                tree[v][0] = tree[v * 2 + 1][0];
                tree[v][1] = tree[v * 2 + 1][1];
            }
        }

        int[] query() {
            push(1);
            return tree[1];
        }

    }

}
