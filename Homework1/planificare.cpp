// Copyright 2018 Florin-Ion Smeu

#include <bits/stdc++.h>

using namespace std;

int main() {
	freopen("planificare.in", "r", stdin);
	freopen("planificare.out", "w", stdout);

	int p, d, b;
	cin >> p >> d >> b;
	vector<int> v(p + 1);
	v.push_back(0);

	for (int i = 1; i <= p; ++i)
		cin  >> v[i];

	vector<long long> dp(p + 1);
	int number_of_contests = 0;

	// initializare - 0 probe distribuite
	dp[0] = 0;

	for (int i = 1; i <= p; ++i) {
		// initializare cost minim
		long long crt_min = numeric_limits<long long>::max();
		long long ant_min = crt_min;
		long long sum = v[i];

		for (int j = i - 1; j >= 0; --j) {
			// tratarea cazului in care avem de adaugat ultima
			// proba intr-un nou concurs
			if (i == p && j == i - 1) {
				ant_min = crt_min;
				crt_min = dp[p - 1];
				sum += v[j];
				continue;
			}

			// in cazul in care probele alese nu incap intr-un
			// concurs, voi opri cautarea
			if ((d - (i - j - 1) * b - sum) < 0)
				break;

			// daca pierderile sunt minimizate, voi face alegerea
			// optima
			if (dp[j] + pow((d - (i - j - 1) * b - sum), 3) <
			    crt_min) {
				ant_min = crt_min;
				crt_min = dp[j] +
					  pow((d - (i - j - 1) * b - sum), 3);
			}
			sum += v[j];
		}
		dp[i] = crt_min;

		// in cazul in care pierderea este mai mare sau egala dupa
		// distribuirea unei probe, este clar ca am creat un nou
		// concurs
		if (dp[i] >= dp[i - 1])
			number_of_contests++;
	}

	// dp[p] contine pierderile totale dupa distribuirea tuturor probelor
	cout << dp[p] << ' ' << number_of_contests;

	fclose(stdin);
	fclose(stdout);

	return 0;
}
