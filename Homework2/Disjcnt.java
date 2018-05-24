// Copyright 2018 Florin-Ion Smeu

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class Disjcnt {
	static class Task {
		public static final String INPUT_FILE = "disjcnt.in";
		public static final String OUTPUT_FILE = "disjcnt.out";
		public static final int NMAX = 100005; // 10^5

		// n - number of vertices, m - number of edges
		int n;
		int m;

		// information used by the dfs method
		int time = 0;
		int[] idx;
		int[] low;
		int[] color;		

		// The critical edges of the graph
		ArrayList<Edge> bridges = new ArrayList<>();

		@SuppressWarnings("unchecked")
		ArrayList<Integer> adj[] = new ArrayList[NMAX];

		class Edge {
			int x;
			int y;

			public Edge(int x, int y) {
				this.x = x;
				this.y = y;
			}
		}

		private void readInput() {
			try {
				Scanner sc = new Scanner(new BufferedReader(new FileReader(
								INPUT_FILE)));
				n = sc.nextInt();
				m = sc.nextInt();

				idx = new int[n + 1];
				low = new int[n + 1];
				color = new int[n + 1];

				for (int i = 1; i <= n; i++) {
					adj[i] = new ArrayList<>();
					idx[i] = Integer.MIN_VALUE;
					color[i] = 0;	
				}
				for (int i = 1; i <= m; i++) {
					int x, y;
					x = sc.nextInt();
					y = sc.nextInt();
					adj[x].add(y);
					adj[y].add(x);
				}
				sc.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		private void writeOutput(long result) {
			try {
				PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(
								OUTPUT_FILE)));
				pw.printf("%d", result);
				pw.close();
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}

		/**
		 * The method is called to determine the critical edges of the graph.
 		 * @param node
		 * @param parent
		 */
		void dfs(int node, int parent) {
			idx[node] = time;
			low[node] = time;
			time++;

			for (int u : adj[node]) {
				if (parent != u) {
					if (idx[u] == Integer.MIN_VALUE) {
						dfs(u, node);
						low[node] = Math.min(low[node], low[u]);
						if (low[u] > idx[node]) {
							bridges.add(new Edge(node, u));
						}
					} else {
						low[node] = Math.min(low[node], idx[u]);
					}
				}
			}
		}

		/**
		 * The method computes the number of vertices that a connected sub-graph contains.
		 *
		 * @param node
		 * @return
		 */
		long getNumberOfSolutionVertices(int node) {
			long ctr = 1;
			color[node] = 1;
			for (int u : adj[node]) {
				if (color[u] == 0) {
					ctr += getNumberOfSolutionVertices(u);
				}
			}
			color[node] = 2;
			return ctr;		
		}

		/**
		 * The method will compute the final answer of the problem.
 		 * @return
		 */
		private long getResult() {
			dfs(1, -1);

			for (Edge e : bridges) {
				adj[e.x].remove((Object) e.y);
				adj[e.y].remove((Object) e.x);
			} 
 
			long ans = 0;
			for (int i = 1; i <= n; ++i) {
				if (color[i] == 0) {
					long ctr = getNumberOfSolutionVertices(i);
					System.out.println(i + " ctr: " + ctr);
					ans += (ctr * (ctr - 1)) / 2;
				}
			}
			
			return ans;
		}

		public void solve() {
			readInput();
			writeOutput(getResult());
		}
	}

	public static void main(String[] args) {
		new Task().solve();
	}
}
