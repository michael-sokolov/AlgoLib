import java.io.*;
import java.util.*;

public class acm implements Comparator<int[]> {
    static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
    static PrintWriter out = new PrintWriter(System.out, true);
    static StringTokenizer st;


    public static void main(String[] args) throws Exception {
        int m = nextInt();
        ArrayList<int[]> v = new ArrayList<int[]>();
        ArrayList<int[]> ab = new ArrayList<int[]>();
        int count = 0;
        while (true) {
            count++;
            int a = nextInt(), b = nextInt();
            if (a == 0 && b == 0) break;
            ab.add(new int[]{a, b});
            a = Math.max(a, 0);
            b = Math.min(b, m);
            if (b <= a) continue;
            v.add(new int[]{a, b, count - 1});
        }
        Collections.sort(v, new acm());
        int last = 0;
        ArrayList<Integer> ans = new ArrayList<Integer>();
        for (int i = 0, j = 0; i < m; ) {
            int cur = -1;
            while (j < v.size() && v.get(j)[0] <= i) {
                if (v.get(j)[1] > last) {
                    cur = v.get(j)[2];
                    last = Math.max(last, v.get(j)[1]);
                }
                ++j;
            }
            if (last == i) {
                out.println("No solution");
                out.flush();
                return;
            }
            i = last;
            ans.add(cur);
        }
        out.println(ans.size());
        for (int i : ans) {
            out.println(ab.get(i)[0] + " " + ab.get(i)[1]);
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


    @Override
    public int compare(int[] o1, int[] o2) {
        if (o1[0] == o2[0]) return o1[1] - o2[1];
        return o1[0] - o2[0];
    }
}
