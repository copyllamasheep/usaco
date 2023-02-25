#include <iostream>
#include <algorithm>
#include <set>

#define MAX_N 2005

using namespace std;

typedef pair<int, double> ii;

set<ii> slopes[MAX_N];

int H[MAX_N];
int N, Q;

int main() {
	cin >> N;

	for (int i = 0; i < N; i ++) {
		cin >> H[i];
	}

	double INF = 2000000000.0;

	for (int i = 0; i < N; i ++) {
		double prev = -INF;

		for (int j = i + 1; j < N; j ++) {
			double diff = (H[j] - H[i] * 1.0) / (j * 1.0 - i);
			
			if (diff >= prev) {
				slopes[i].insert(ii(j, diff));
				prev = diff;
			}
		}
	}

	cin >> Q;

	int x, y;
	for (int i = 0; i < Q; i ++) {
		cin >> x >> y;
		x --;

		H[x] += y;
		
		//Update
		for (int j = 0; j < x; j ++) {
			double n_slope = (H[x] - H[j] * 1.0) / (x * 1.0 - j);
			
			set<ii>::iterator idx = slopes[j].lower_bound(ii(x, -INF));
		
			if (idx->first == x) {
				idx = slopes[j].erase(idx);
			}
				
			if (idx == slopes[j].begin()) {
				slopes[j].insert(idx, ii(x, n_slope));
			} else {
				idx --;
		
				if (idx->second <= n_slope) {
					idx ++;
					slopes[j].insert(idx, ii(x, n_slope));
				} else {
					continue;
				}
			}
			
			while (idx != slopes[j].end() && idx->second < n_slope) {
				set<ii>::iterator tmp = idx;
				idx ++;

				slopes[j].erase(tmp);
			}
		}

		slopes[x].clear();

		double prev = -INF;
		for (int j = x + 1; j < N; j ++) {
			double diff = (H[j] - H[x] * 1.0) / (j * 1.0 - x);
			
			if (diff >= prev) {
				slopes[x].insert(ii(j, diff));
				prev = diff;
			}
		}

		int ans = 0;

		for (int i = 0; i < N; i ++) {
			/*
			for (set<ii>::iterator it = slopes[i].begin(); it != slopes[i].end(); it ++) {
				cout << it->first << " " << it->second << endl;
			}

			cout << endl; */

			ans += slopes[i].size();
		}

		cout << ans << endl;
	}

	return (0);
}
