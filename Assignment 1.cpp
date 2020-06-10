#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

#define ii pair<int,int>
#define pb push_back
int n;
int e, source = 0;
vector<ii> g[100000];
int dist[100000];
bool marked[100000];

void apply_dijkstra()
{
	set<ii> s;
	s.insert(ii(0, source));
	dist[source] = 0;
	marked[source] = 1;
	while (!s.empty())
	{
		ii p = *s.begin();
		s.erase(p);
		marked[p.second] = 2;
		for (int i = 0; i < g[p.second].size(); i++)
			if (marked[g[p.second][i].second] == 0)
			{
				s.insert(ii(dist[p.second] + g[p.second][i].first, g[p.second][i].second));
				marked[g[p.second][i].second] = 1;
				dist[g[p.second][i].second] = dist[p.second] + g[p.second][i].first;
			}
			else if (marked[g[p.second][i].second] == 1 && dist[g[p.second][i].second] > dist[p.second] + g[p.second][i].first)
			{
				s.erase(ii(dist[g[p.second][i].second], g[p.second][i].second));
				s.insert(ii(dist[p.second] + g[p.second][i].first, g[p.second][i].second));
				dist[g[p.second][i].second] = dist[p.second] + g[p.second][i].first;
			}
	}

	int min = 0;
	int a[1000] = { 0 };
	for (int i = 0; i < n; i++)
	{
		a[i] = dist[i];
	}

	for (int i = 0; i < n; i++)
	{
		if (min < a[i + 1])
			min = a[i + 1];
	}
	cout << min << endl;

}

int main()
{

	cin >> n;

	int e;
	cin >> e;

	for (int i = 0; i < e; i++)
	{
		int x, y, w;
		cin >> x >> y >> w;
		g[x].pb(ii(w, y));
	}

	apply_dijkstra();

	system("pause");
	return 0;
}