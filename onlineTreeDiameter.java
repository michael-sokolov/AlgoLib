import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.StringTokenizer;

public class acm {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out, true);
    static StringTokenizer st;
    static int[][] up;
    static int dp[];
    static final int lg = 20;

    static void fillUp() {
        for (int i = 1; i < lg; ++i) {
            for (int j = 0; j < up[0].length; ++j) {
                up[i][j] = up[i - 1][up[i - 1][j]];
            }
        }
    }

    static int getDist(int a, int b) {
        if (dp[a] < dp[b]) {
            int buf = a;
            a = b;
            b = buf;
        }
        int aa = a;
        int bb = b;
        int d = dp[a] - dp[b];
        int j = lg - 1;
        while (j >= 0) {
            if ((1 << j) <= d) {
                d -= (1 << j);
                a = up[j][a];
            }
            --j;
        }
        if (a == b) return dp[bb] - dp[aa];
        for (int i = lg - 1; i >= 0; --i) {
            if (up[i][a] != up[i][b]) {
                a = up[i][a];
                b = up[i][b];
            }
        }
        return -2 * dp[up[0][a]] + dp[aa] + dp[bb];
    }

    public static void main(String[] args) throws Exception {
        // in = new BufferedReader(new FileReader("2in2.txt"));
        //out = new PrintWriter("facebookOutput22.txt");
        int q = nextInt();
        int n = 4;

        int[] vs = new int[q];
        int[] sizes = new int[2 * q + 4];
        sizes[0] = 3;
        sizes[1] = sizes[2] = sizes[3] = 1;
        for (int i = 0; i < q; ++i) {
            int v = nextInt() - 1;
            vs[i] = v;
            sizes[v] += 2;
            sizes[n++]++;
            sizes[n++]++;
        }
        dp = new int[n];
        dp[1] = dp[2] = dp[3] = 1;
        up = new int[lg][n];

        n = 4;
        for (int i = 0; i < q; ++i) {
            int v = vs[i];
            dp[n] = dp[v] + 1;
            up[0][n] = v;
            n++;
            dp[n] = dp[v] + 1;
            up[0][n] = v;
            n++;
        }

        fillUp();
        int curDia = 2;
        int d1 = 1, d2 = 2;
        int m = 4;
        for (int i = 0; i < q; ++i) {
            int x = m++;
            int y = m++;
            int d1xDist = getDist(d1, x);
            if (d1xDist > curDia) {
                curDia = d1xDist;
                d2 = x;
            }
            int d2xDist = getDist(d2, x);
            if (d2xDist > curDia) {
                curDia = d2xDist;
                d1 = x;
            }
            int d1yDist = getDist(d1, y);
            if (d1yDist > curDia) {
                curDia = d1yDist;
                d2 = y;
            }
            int d2yDist = getDist(d2, y);
            if (d2yDist > curDia) {
                curDia = d2yDist;
                d1 = y;
            }
            System.out.println(curDia);
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


}


