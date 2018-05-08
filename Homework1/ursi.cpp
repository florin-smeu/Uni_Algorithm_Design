// Copyright 2018 Florin-Ion Smeu

#include <bits/stdc++.h>
#define MOD (long) (1e+09 + 7)

using namespace std;

int main() {
	freopen("ursi.in", "r", stdin);
	freopen("ursi.out", "w", stdout);

	string characters;
	getline(cin, characters);

	int n = characters.size();
	int m = 0;

	for (int i = 0; i < n; ++i)
		if (characters[i] == '^')
			m++;

	long **mat = (long **) malloc(n * sizeof(long *));
	for (int i = 0; i < n; ++i)
		mat[i] = (long *) malloc(m * sizeof(long));

	// initializare matrice
	for (int i = 0; i < m; ++i)
		mat[0][i] = 0;

	mat[0][1] = 1;

	// calculare solutie
	for (int i = 1; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			// caz particular cand j = 0
			if (j == 0 && characters[i] == '^') {
				mat[i][j] = (mat[i - 1][j + 1] * (j + 1)) %
					    MOD;
				continue;
			}
			// caz particular cand j = m - 1
			if (j == m - 1 && characters[i] == '^') {
				mat[i][j] = (mat[i - 1][j - 1]) % MOD;
				continue;
			}
			// caracterul '_' este gasit
			if (characters[i] == '_')
				mat[i][j] = (mat[i - 1][j] * j) % MOD;
			// caracterul '^' este gasit
			if (characters[i] == '^')
				mat[i][j] = ((mat[i - 1][j - 1]) % MOD +
					     (mat[i - 1][j + 1] *
					      (j + 1)) % MOD) % MOD;
		}
	}

	// afisare raspuns final
	cout << mat[n - 1][0];

	fclose(stdin);
	fclose(stdout);

	return 0;
}
