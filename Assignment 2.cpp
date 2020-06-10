// C++ code
#include <iostream>
#include <vector>
#include <list>
#include <iomanip>      
#include <algorithm>
using namespace std;

int n, e;

struct Edge{
    int from, to, weight;
    Edge(){};
    Edge(int u, int v, int w):from(u), to(v), weight(w){};
};

class GraphMST{
private:
    int num_vertex;
    std::vector<std::vector<int>> AdjMatrix;
public:
    GraphMST():num_vertex(0){};
    GraphMST(int n):num_vertex(n){
        AdjMatrix.resize(num_vertex);
        for (int i = 0; i < num_vertex; i++) {
            AdjMatrix[i].resize(num_vertex);
        }
    }
    void AddEdge(int from, int to, int weight);

    void KruskalMST();
    void GetSortedEdge(std::vector<struct Edge> &vec);
    friend int FindSetCollapsing(int *subset, int i);
    friend void UnionSet(int *subset, int x, int y);
};
int FindSetCollapsing(int *subset, int i){ 

    int root;  // root
    for (root = i; subset[root] >= 0; root = subset[root]);

    while (i != root) {
        int parent = subset[i];
        subset[i] = root;
        i = parent;
    }

    return root;
}
void UnionSet(int *subset, int x, int y){

    int xroot = FindSetCollapsing(subset, x),
        yroot = FindSetCollapsing(subset, y);

    if (subset[xroot] <= subset[yroot]) {        
        subset[xroot] += subset[yroot];
        subset[yroot] = xroot;
    }
    else {   
        subset[yroot] += subset[xroot];
        subset[xroot] = yroot;
    }
}
bool WeightComp(struct Edge e1, struct Edge e2){
    return (e1.weight < e2.weight);
}
void GraphMST::GetSortedEdge(std::vector<struct Edge> &edgearray){

    for (int i = 0; i < num_vertex-1; i++) {
        for (int j = i+1; j < num_vertex; j++) {
            if (AdjMatrix[i][j] != 0) {
                edgearray.push_back(Edge(i,j,AdjMatrix[i][j]));
            }
        }
    }
   
    sort(edgearray.begin(), edgearray.end(), WeightComp);
}
void GraphMST::KruskalMST(){

    struct Edge *edgesetMST = new struct Edge[num_vertex-1];
    int edgesetcount = 0;

    int subset[num_vertex];
    for (int i = 0; i < num_vertex; i++) {
        subset[i] = -1;
    }

    vector<struct Edge> increaseWeight;
    GetSortedEdge(increaseWeight);             

    for (int i = 0; i < increaseWeight.size(); i++) {
        if (FindSetCollapsing(subset, increaseWeight[i].from) != FindSetCollapsing(subset, increaseWeight[i].to)) {
            edgesetMST[edgesetcount++] = increaseWeight[i];
            UnionSet(subset, increaseWeight[i].from, increaseWeight[i].to);
        }
    }
	
	for (int i = 0; i < num_vertex - 1; i++) {
		for (int j = 0; j < e; j++)	{
			if(edgesetMST[i].from == increaseWeight[j].from &&
			   edgesetMST[i].to == increaseWeight[j].to &&
			   edgesetMST[i].weight == increaseWeight[j].weight) {
				increaseWeight[j].from = 0;
				increaseWeight[j].to = 0;
				increaseWeight[j].weight = 0;
			}
		}
	}	

	for (int j = 0; j < e; j++) {
		if(increaseWeight[j].weight != 0) {
			cout << increaseWeight[j].weight << " ";           
        }
	}
	cout << endl;
}
void GraphMST::AddEdge(int from, int to, int weight){
    AdjMatrix[from][to] = weight;
}

int main() {

	while(cin >> n >> e) {	    		

		GraphMST g6(n);

		for (int i = 0; i < e; i++) {
			int x, y, w;
			cin >> x >> y >> w;
			g6.AddEdge(x, y, w);
		}
       
		g6.KruskalMST();

    }
	
	return 0;
}