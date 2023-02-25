#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

#define MAX_N 2005
#define f first
#define s second

using namespace std;

typedef pair<int, int> ii;
typedef pair<int, ii> pii;

int n = 2005;

unordered_map<long long, int> DP;
pii cow[MAX_N];

int DP2[MAX_N][2 * MAX_N];
int N, A, B;

long long cnv(pii a) {
    return (n * n * a.f + n * a.s.f + a.s.s);
}

bool cmp(pii a, pii b) {
	return (a.s.s < b.s.s);
}

int main() {
	cin >> N >> A >> B;
	
	int ans = 0;

	for (int i = 0; i < N; i ++) {
		cin >> cow[i].f >> cow[i].s.f >> cow[i].s.s;
	}

    if (B == 0) {
        for (int i = 0; i < N; i ++) {
            for (int j = 0; j <= A; j ++) {
                if (j + cow[i].s.f < MAX_N) {
                    DP2[i + 1][j + cow[i].s.f] = max(DP2[i + 1][j + cow[i].s.f], DP2[i][j] + cow[i].f);
                }

                DP2[i + 1][j] = max(DP2[i + 1][j], DP2[i][j]);
            }
        }

        for (int i = 0; i <= A; i ++) {
            ans = max(ans, DP2[N][i]); 
        }

        cout << ans << endl;
        return (0);
    }

	sort(cow, cow + N, cmp);

	queue<pii> q;
	q.push(pii(0, ii(A, B)));

	while (!q.empty()) {
		pii cur = q.front();
		q.pop();

		int a = cur.s.f;
		int b = cur.s.s;

		if (cur.f == N) {
			continue;
		}

		pii new_without = pii(cur.f + 1, ii(cur.s.f, cur.s.s));

		//Don't take 
		
		if (!DP[cnv(new_without)] || DP[cnv(new_without)] < DP[cnv(cur)]) {
			DP[cnv(new_without)] = DP[cnv(cur)];
            q.push(new_without);
		}

		pii new_with = pii(cur.f + 1, ii(cur.s.f, cur.s.s));
		
		int disc = min(cow[cur.f].s.f, (b / cow[cur.f].s.s));

		if (cow[cur.f].s.f - disc <= a) {
			new_with.s.f = a - (cow[cur.f].s.f - disc);
			new_with.s.s = b - disc * cow[cur.f].s.s;

			if (DP[cnv(new_with)] < DP[cnv(cur)] + cow[cur.f].f) {
				DP[cnv(new_with)] = DP[cnv(cur)] + cow[cur.f].f;
			    
                ans = max(ans, DP[cnv(new_with)]);
				q.push(new_with);
			}
		}
	}
	
	cout << ans << endl;	
	return (0);
}

