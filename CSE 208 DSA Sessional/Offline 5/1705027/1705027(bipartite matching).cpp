//#include<bits/stdc++.h>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<ctime>
#include<stack>
#include<queue>
#include<algorithm>
#define NULL_VALUE -999999
using namespace std;
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

ofstream out;
struct Edge{
    int u,v,w;
};

vector<Edge> iniEdges, flowEdges;

int *colour1;
class Graph{
    vector<vector <Edge>> adjList;
    vector<Edge> edges;
    int nVertices, nEdges;
    bool directed;
    int *colour;
    int *dis;
    int *parent;
public:
    Graph();
    void setnVertices(int n, bool directed=true);
    bool addEdge(int u,int v, int w);
    int getWeight(int u,int v);
    bool isEdge(int u,int v);
    void deleteEdge(int u,int v);
    void reweightEdge(int u,int v,int newWeight);
    void printGraph();
    int BFS(int source,int sink);
    int Ford_Fulkerson(int s,int t);
    void Printflow();
    bool Bipartite();
    bool bfs(int source);
    void AugmentedGraph(int s, int t);
};

Graph::Graph(){
    nVertices=0;
    nEdges=0;
    directed=true;
}

void Graph::setnVertices(int n,bool directed)
{
    nVertices=n;
    for(int i=0;i<nVertices;i++){
        vector<Edge> ed;
        adjList.push_back(ed);
    }
    this->directed=directed;
    colour=new int[nVertices];
    colour1=new int[nVertices];
    dis=new int[nVertices];
    parent=new int[nVertices];
}

bool Graph::addEdge(int u,int v,int w)
{
    if(!isEdge(u,v)){
        nEdges++;
        Edge ed;
        ed.u=u;
        ed.v=v;
        ed.w=w;
        edges.push_back(ed);
        adjList[u].push_back(ed);
        return true;
    }
    return false;
}

int Graph::getWeight(int u,int v){
    if(isEdge(u,v)){
        int idx=-1;
        for(int i=0;i<edges.size();i++)
        {
            if(edges[i].u==u && edges[i].v==v){
                idx=i;
                return edges[i].w;
            }
        }
    }
    return INFINITY;
}

bool Graph::isEdge(int u,int v)
{
    int idx=-1;
    for(int i=0;i<edges.size();i++)
    {
        if(edges[i].u==u && edges[i].v==v){
            idx=i;
            return true;
        }
    }
    return false;
}

void Graph::deleteEdge(int u,int v)
{
    if(isEdge(u,v)){
        int idx=-1;
        nEdges--;
        for(int i=0;i<edges.size();i++)
        {
          if(edges[i].u==u && edges[i].v==v){
                idx=i;
                break;
            }
        }
        edges[idx]=edges[edges.size()-1];
        edges.pop_back();
        int c=0;
        for(Edge ed: adjList[u])
        {
            if(ed.v==v)
            {
                idx=c;
                break;
            }
            c++;
        }

        adjList[u][idx]=adjList[u][adjList[u].size()-1];
        adjList[u].pop_back();
    }
}

void Graph::reweightEdge(int u,int v,int newWeight)
{
    if(isEdge(u,v)){
        int idx=0;
        for(int i=0;i<edges.size();i++)
        {
            if(edges[i].u==u && edges[i].v==v){
                edges[i].w=newWeight;
                break;
            }
        }
        for(Edge ed: adjList[u])
        {
            if(ed.v==v)
            {
                adjList[u][idx].w=newWeight;
                break;
            }
            idx++;
        }
    }
}

void Graph::printGraph()
{
    for(int i=0;i<adjList.size();i++)
    {
        for(int j=0;j<adjList[i].size();j++)
        {
            printf("u: %d v: %d weight: %d\n",adjList[i][j].u,adjList[i][j].v,adjList[i][j].w);
        }
        //printf("\n");
    }
}


bool Graph::Bipartite()
{
    for(int i=0;i<nVertices;i++)
    {
        colour1[i]=WHITE;
    }

   for(int i=0;i<nVertices;i++)
   {
       if(colour1[i]==WHITE) {
            if(!bfs(i)) return false;
       }
   }
   return true;
}


bool Graph::bfs(int source)
{
    queue<int> q;
    q.push(source);
    colour1[source]=GREY;
    parent[source]=source;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(Edge ed: adjList[u])
        {
            //cout<<"bfs u:"<<u<<"\t v: "<<ed.v<<endl;
            if(colour1[ed.v]==WHITE)
            {
                if(colour1[u]==GREY) colour1[ed.v]=BLACK;
                else colour1[ed.v]=GREY;
                parent[ed.v]=u;
                q.push(ed.v);
            }
            else if(colour1[ed.v]==colour1[u]){
                return false;
            }
        }
    }
    return true;
}

int Graph::BFS(int source,int sink)
{
    int minCapacity=INFINITY;
    for(int i=0;i<nVertices;i++)
    {
        colour[i]=WHITE;
    }
    queue<int> q;
    q.push(source);
    colour[source]=GREY;
    parent[source]=source;
    while(!q.empty())
    {
        int u=q.front();
        q.pop();
        for(Edge ed: adjList[u])
        {
            if(colour[ed.v]==WHITE && ed.w>0)
            {
                colour[ed.v]=GREY;
                parent[ed.v]=u;
                minCapacity=min(minCapacity,ed.w);
                if(ed.v==sink)
                {
                    return minCapacity;
                }
                q.push(ed.v);
            }
            colour[u]=BLACK;
        }
    }
    return 0;
}

int Graph::Ford_Fulkerson(int s,int t)
{
    int flow=0;
    int newMinflow;
    while(newMinflow=BFS(s,t))
    {
        flow+=newMinflow;
        int v=t;
        while(v!=s)
        {
            int u=parent[v];
            reweightEdge(u,v,getWeight(u,v)-newMinflow);
            if(isEdge(v,u)) reweightEdge(v,u,getWeight(v,u)+newMinflow);
            else addEdge(v,u,newMinflow);
            v=u;
        }
    }
    return flow;
}

void Graph::Printflow()
{
    for(int i=0;i<flowEdges.size();i++)
    {
        if(flowEdges[i].w-getWeight(flowEdges[i].u,flowEdges[i].v)==1){
                out<<flowEdges[i].u<<" "<<flowEdges[i].v<<endl;
                cout<<flowEdges[i].u<<" "<<flowEdges[i].v<<endl;
        }
    }
}

void Graph::AugmentedGraph(int s, int t)
{
    for(Edge ed:iniEdges)
    {
        if(colour1[ed.u]==GREY){
            addEdge(s,ed.u,1);
            addEdge(ed.u,ed.v,1);
            addEdge(ed.v,t,1);
            flowEdges.push_back(ed);
        }
        else if(colour1[ed.u]==BLACK){
            addEdge(ed.u,t,1);
            addEdge(ed.v,ed.u,1);
            addEdge(s,ed.v,1);
            Edge e; e.u=ed.v; e.v=ed.u; e.w=1;
            flowEdges.push_back(e);
        }
    }
}

int main()
{
    fstream in("in.txt");
    int nVertics,u,v,w, edges, s, t,n;
    Graph g,ag;
    in>>nVertics;
    in>>edges;
    n=nVertics;
    g.setnVertices(n);
    ag.setnVertices(n+2);

    for(int i=0;i<edges;i++)
    {
        in>>u;
        in>>v;
        g.addEdge(u,v,1);
        g.addEdge(v,u,1);
        Edge ed;
        ed.u=u;
        ed.v=v;
        ed.w=1;
        iniEdges.push_back(ed);
    }
    //g.printGraph();
    bool r=g.Bipartite();
    out.open("output(Bipartite).txt");
    if(r) {
            ag.AugmentedGraph(n,n+1);
            int flow=ag.Ford_Fulkerson(n,n+1);
            out<<flow<<endl;
            cout<<flow<<endl;
            ag.Printflow();
    }
    else{
        out<<"The graph is not bipartite";
        cout<<"The graph is not bipartite\n";
    }
    out.close();
    return 0;
}


