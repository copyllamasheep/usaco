#include <iostream>
#include <algorithm>
#include <vector>

#define MAX_N 100005
#define f first
#define s second

using namespace std;

typedef pair<int, int> ii;

vector<int> con[MAX_N];
vector<int> groups[MAX_N];

int cnv[MAX_N], color[MAX_N], start[MAX_N], deg[MAX_N];
int N, M;

void DFS(int ind, int col) {
	color[ind] = col;
	groups[col].push_back(ind);

	for (int i = 0; i < con[ind].size(); i ++) {
		if (!color[con[ind][i]]) {
			DFS(con[ind][i], col);
		}	
	}
}

void DFS2(int ind, int col) {
    color[ind] = col;
    groups[col].push_back(ind);

    for (int i = 0; i < con[ind].size(); i ++) {
        if (!color[con[ind][i]] && deg[con[ind][i]] > 0) {
            DFS2(con[ind][i], col);
        }
    }
}

int main() {
	cin >> N >> M;

	int a, b;
	for (int i = 0; i < M; i ++) {
		cin >> a >> b;
		a --; b --;

		con[a].push_back(b);
		con[b].push_back(a);
	}

	int col = 1;
	for (int i = 0; i < N; i ++) {
		if (!color[i]) {
			DFS(i, col);
			col ++;
		}
	}

    long long ans = 0ll;
    if (false) {
	    int v = 0;
	    for (int c = 1; c < col; c ++) {
		    start[c] = v;

		    vector<ii> s;
		    for (int i = 0; i < groups[c].size(); i ++) {
			    cnv[groups[c][i]] = v;
			    v ++;
		
			    s.push_back(ii(groups[c][i], con[groups[c][i]].size()));
			    deg[groups[c][i]] = con[groups[c][i]].size();
	    	}
		
		    while (s.size() > 0) {
			    int mn = MAX_N;

			    for (int i = 0; i < s.size(); i ++) {
				    mn = min(mn, s[i].s);
			    }

			    ans = max(ans, mn * (long long)(s.size()));

			    for (int i = 0; i < s.size(); i ++) {
				    if (s[i].s == mn) {
					    deg[s[i].f] = 0;

					    for (int j = 0; j < con[s[i].f].size(); j ++) {
						    deg[con[s[i].f][j]] --;
					    }		
				    
                        break;
                    }
			    }
			
			    vector<ii> tmp;
			    for (int i = 0; i < s.size(); i ++) {
				    if (deg[s[i].f] > 0) {
					    tmp.push_back(ii(s[i].f, deg[s[i].f]));
				    }
			    }   	
			
			    s.clear();
			    for (int i = 0; i < tmp.size(); i ++) {
				    s.push_back(tmp[i]);
			    }
		    }
	    }
    } else {
        for (int i = 0; i < N; i ++) {
            deg[i] = con[i].size();
        }

        while (true) {
            bool flag = true;

            for (int i = 0; i < N; i ++) {
                if (deg[i] > 0) {
                    flag = false;
                }
                
                groups[i].clear();
                color[i] = 0;
            }

            if (flag) {
                break;
            }

            int col = 1;
            for (int i = 0; i < N; i ++) {
                if (!color[i] && deg[i] > 0) {
                    DFS2(i, col);
                    col ++; 
                }
            }

            for (int i = 1; i < col; i ++) {
                int small_deg = MAX_N;

                for (int j = 0; j < groups[i].size(); j ++) {
                    small_deg = min(small_deg, deg[groups[i][j]]);
                } 
                
                ans = max(ans, small_deg * (long long)(groups[i].size()));

                for (int j = 0; j < groups[i].size(); j ++) {
                    if (deg[groups[i][j]] == small_deg) {
                        deg[groups[i][j]] = 0;

                        for (int k = 0; k < con[groups[i][j]].size(); k ++) {
                            deg[con[groups[i][j]][k]] --;
                        }
                    }
                }
            }
        }  
    }

	cout << ans << endl;
	return (0);	
}

