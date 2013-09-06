import java.io.*;
import java.util.*;

public class acm {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out, true);
    static StringTokenizer st;
    static int res = 0;
    static String s;
    static int n;

    static class edge {
        int l, r, to;

        edge(int l, int r, int to) {
            this.l = l;
            this.r = r;
            this.to = to;
        }

        edge() {
            to = l = r = 0;
        }

    }

    static edge[][] trie;
    static int size = 1;

    public static void add(int l) {
        int v = 0;
        while (l < n) {
            edge to = trie[v][s.charAt(l) - 'a'];
            if (to.to == 0) {
                to.to = size++;
                to.l = l;
                to.r = n;
                res += n - l;
                return;
            }
            int i = to.l;
            while (l < n && i < to.r) {
                if (s.charAt(l) != s.charAt(i)) break;
                ++l;
                ++i;
            }
            if (l == n) return;
            if (to.r != i) {
                int cur = size++;
                trie[cur][s.charAt(l) - 'a'] = new edge(l, n, size++);
                trie[cur][s.charAt(i) - 'a'] = new edge(i, to.r, to.to);
                to.to = cur;
                to.r = i;
                res += n - l;
                return;
            }
            v = to.to;
        }
    }

    public static void main(String[] args) throws Exception {
        // in = new BufferedReader(new FileReader("005.in"));
        s = nextToken();
        n = s.length();
        trie = new edge[5000 * 2][26];
        for (int i = 0; i < trie.length; ++i) {
            for (int j = 0; j < 26; ++j) {
                trie[i][j] = new edge();
            }
        }
        for (int i = 0; i < n; ++i) add(i);
        out.println(res);
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
