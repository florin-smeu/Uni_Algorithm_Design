// Copyright 2018 Florin-Ion Smeu

#include <bits/stdc++.h>

using namespace std;

bool comp(const pair<int, int> &left, const pair<int, int> &right) {
	return (left.first + left.second > right.first + right.second);
}

bool second_comp(const pair<int, int> &left, const pair<int, int> &right) {
	return (left.first > right.first);
}

int main() {
	freopen("frati.in", "r", stdin);
	freopen("frati.out", "w", stdout);

	int n;
	cin >> n;
	vector<pair<int, int> > v(n);
	for (int i = 0; i < n; ++i)
		cin >> v[i].first >> v[i].second;

	// sortare dupa suma maxima a premiilor
	sort(v.begin(), v.end(), comp);

	int jon_sum = 0, sam_sum = 0;

	// initial este randul lui Jon sa aleaga un concurs
	bool turn = true;
	int size = n, idx = 0;
	while (size > 0) {
		int sum = v[idx].first + v[idx].second;
		vector<pair<int, int> > aux;

		aux.push_back(v[idx]);

		// cat timp concursurile au aceeasi suma
		// le vom stoca in vectorul aux
		while(v[idx + 1].first + v[idx + 1].second == sum) {
			aux.push_back(v[idx + 1]);
			idx++;
		}

		// sortarea zonei de suma egala dupa numarul de jocuri video
		sort(aux.begin(), aux.end(), second_comp);

		// alegerea concursurilor de catre cei doi frati si
		// calcularea numarului de obiecte preferate de fiecare
		int i = 0;
		int j = aux.size() - 1;
		while (i <= j) {
			if (turn) {
				jon_sum += aux[i].first;
				turn = false;
				i++;
			} else {
				sam_sum += aux[j].second;
				turn = true;
				j--;
			}
		}

		// scadem numarul de concursuri din care avem de ales
		size -= aux.size();

		idx++;
	}

	cout << jon_sum << ' ' << sam_sum << "\n";

	fclose(stdin);
	fclose(stdout);

	return 0;
}
