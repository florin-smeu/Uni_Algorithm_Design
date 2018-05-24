// Copyright 2018 Florin-Ion Smeu

#include <bits/stdc++.h>
    
using namespace std;

int main(void) 
{
	ios_base::sync_with_stdio(false);	

	// Open the I/O files
	freopen("revedges.in", "r", stdin);
	freopen("revedges.out", "w", stdout);

	int n, m, q;
	cin >> n >> m >> q;
	
	// Floyd-Warshall will be applied to solve the problem	
	int mat[n + 1][n + 1];
	
	// Initialize matrix
	for (int i = 1; i <= n; ++i) 
		for (int j = 1; j <= n; ++j) 
			mat[i][j] = numeric_limits<int>::max();
	
	// Adding edges
	int x, y;
	for (int i = 1; i <= m; ++i) {
		cin >> x >> y;	
		mat[x][y] = 0;
		if (mat[y][x] != 0) mat[y][x] = 1;
	}
	
	// Applying Floyd-Warshall
	for (int k = 1; k <= n; ++k)
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j) 
				if (mat[i][j] > mat[i][k] + mat[k][j] && 
					mat[k][j] < numeric_limits<int>::max() &&
					mat[i][k] < numeric_limits<int>::max())
					mat[i][j] = mat[i][k] + mat[k][j];

	// The result of a query (x y) is mat[x][y] or 0 if x = y
	for (int i = 1; i <= q; ++i) {
		cin >> x >> y;
		if (x == y) {
			cout << 0 << "\n";
			continue;
		}
		cout << mat[x][y] << "\n";
	}  	
	return 0;
}
