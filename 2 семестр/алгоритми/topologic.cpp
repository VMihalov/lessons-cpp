#include <iostream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

vector<vector<int> >adj;
stack<int> s;
bool *visited;
int n;

void createGraph()
{
	int a,b;
	adj.resize(n);

    for(int j=0;j<n;j++)
    {
        cin>>a>>b;
        adj[a].push_back(b);
    }
}

void topoSortUtil(int i)
{
	visited[i] = true;
	for(int j=0;j<adj[i].size();j++)
	{
		int node = adj[i][j];
		if(!visited[node])
            topoSortUtil(node);
	}
	s.push(i);
}

void topoSort()
{
	memset(visited,false,sizeof(visited));

	for(int i=0;i<n;i++)
	{
		if(!visited[i])
			topoSortUtil(i);
	}
}
void display()
{
	for(int i=0;i<n;i++)
	{
		cout<<s.top()<<" ";
		s.pop();
	}
}
int main()
{
	cin>>n;
	visited = new bool[n];
	createGraph();
	topoSort();
	display();
}