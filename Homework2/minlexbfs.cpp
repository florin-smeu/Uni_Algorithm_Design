// Copyright 2018 Florin-Ion Smeu

#include <bits/stdc++.h>

#define kMaxN (int) 1e5 + 1

using namespace std;

int main(void) 
{
	// Open I/O files
	freopen("minlexbfs.in", "r", stdin);
	freopen("minlexbfs.out", "w", stdout);

	// Read data
	int n, m;
	cin >> n >> m;
	vector<int> adj[kMaxN];
	
	int source = numeric_limits<int>::max();	
	for (int i = 1; i <= m; ++i) {
		int a, b;
		cin >> a >> b;
		if (a  < source || b < source) source = min(a, b);
		adj[a].push_back(b);
 		adj[b].push_back(a);
	}	

	// Sort adjacency lists of each vertex
	for (int i = 1; i <= n; ++i) sort(adj[i].begin(), adj[i].end());
		
	queue<int> q;
	vector<bool> visited(n + 1, false);
	vector<int> ans;
	ans.push_back(-1);
	
	// Initialization
	q.push(source);
	visited[source] = true;
	ans.push_back(source);
	
	// BFS
	while (!q.empty()) {
		int s = q.front();
		q.pop();
		for (auto u : adj[s]) {
			if (visited[u]) continue;
			visited[u] = true;
			ans.push_back(u);
			q.push(u);
		}
	}
	
	// Print result
	for (int i = 1; i <= n; ++i) {
		cout << ans[i] << ' ';
	}

	return 0;
}
