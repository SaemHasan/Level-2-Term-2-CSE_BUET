//#include <bits/stdc++.h>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include<unordered_map>
#include<iostream>
#include<fstream>
#include<stack>
#include<queue>
#define NULL_VALUE -999999
#define INF 99999
using namespace std;

class Edge{
    int u,v;
    double w;
public:
    Edge()
    {
        u=0;
        v=0;
        w=0;
    }
    Edge(int u,int v,int w)
    {
        this->u=u;
        this->v=v;
        this->w=w;
    }
    void setu(int x)
    {
        u=x;
    }
    void setv(int x)
    {
        v=x;
    }
    void setW(double x)
    {
        w=x;
    }
    int getu(){
        return u;
        }
    int getv() {
        return v;
        }
    double getw() {
        return w;
        }
};

struct Node
    {
        int v;
        double d;
    };


class MinHeap
{
    int Size;
    int Maxsize;
public:
    int *pos;
    struct Node *arr;
    MinHeap(int n)
    {
        Size=0;
        Maxsize=n;
        arr=new Node[n];
        pos=new int[n];
    }
    void Insert(int v,double dis)
    {
        if(Size==Maxsize)
        {
            cout<<"Queue overflow"<<endl;
            return;
        }
        arr[Size].v=v;
        arr[Size].d=dis;
        pos[arr[Size].v]=Size;
        Size++;
        heapify(Size,Size-1);
    }
    void heapify(int n,int i)
        {
            int p=(i-1)/2;
            if(p>=0){
                if(arr[i].d<arr[p].d)
                  {
                    pos[arr[i].v]=p;
                    pos[arr[p].v]=i;
                    struct Node temp=arr[i];
                    arr[i]=arr[p];
                    arr[p]=temp;
                    heapify(n,p);
                  }
            }
        }

    void Minheapify(int n,int i)
        {
            int m=i;
            int l=2*i+1;
            int r=2*i+2;
            if(l<n && arr[l].d<arr[m].d)
                m=l;
            if(r<n && arr[r].d<arr[m].d)
                m=r;
            if(m!=i)
            {
                    pos[arr[i].v]=m;
                    pos[arr[m].v]=i;
                 struct Node t=arr[i];
                    arr[i]=arr[m];
                    arr[m]=t;
                Minheapify(n,m);
            }
        }

    struct Node ExtractMin()
    {
        struct Node Min;
        if(Size==0)
        {
            cout<<"Queue Underflow"<<endl;
        }
        else{
            pos[arr[Size-1].v]=0;
            Min=arr[0];
            struct Node last=arr[Size-1];
            arr[0]=last;
            Size=Size-1;
            Minheapify(Size,0);
        }
        return Min;
    }

    void DecreaseKey(int i,double key)
        {
            if(i<0)
            {
                cout<<"Queue overflow in decrease key"<<endl;
                return;
            }
            arr[pos[i]].d=key;
            heapify(Size,pos[i]);
        }
    bool Empty()
    {
        if(Size==0)
            return true;
        return false;
    }

    void print()
    {
        for(int i=0;i<Size;i++)
            cout<<arr[i].v<<" "<<arr[i].d<<endl;
    }
};

class Graph
{
    int nVertices,nEdges;
    vector<vector<Edge*>> adjlist;
    vector<Edge*> edges;
    double **distanceMatrix;
	int **parentMatrix;
	double *distance,*distance1;
	int *parent,*parent1;
public:
    Graph();
    ~Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v, double w);
    void removeEdge(int u, int v);
    Edge* searchEdge(int u, int v);
    void reweightEdge(int u, int v, double w);
    bool isEdge(int u, int v);
    double getWeight(int u, int v);
    void printDistanceMatrix();
    void printPredecessorMatrix();
    void printGraph();

    bool BellmanFord(int source);
	void dijkstra(int source);

    void floydWarshall();
    double getShortestPathWeight(int u ,int v);
    void printShortestPath(int u, int v);
    void cleanSPinfo();
    void johnsonsAlgo();
};

Graph::Graph()
{
    nVertices=0;
    nEdges=0;
    parentMatrix=0;
    distanceMatrix=0;
    distance=0;
    distance1=0;
    parent=0;
    parent1=0;
}

void Graph::setnVertices(int n)
{
    nVertices=n;
    for(int i=0;i<nVertices;i++)
    {
        vector<Edge*> *ed=new vector<Edge*>;
        adjlist.push_back(*ed);
    }
    distanceMatrix = new double*[nVertices];
    parentMatrix = new int*[nVertices];
    distance=new double[nVertices];
    distance1=new double[nVertices];
    parent=new int[nVertices];
    parent1=new int[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        distanceMatrix[i] = new double[nVertices];
        parentMatrix[i] = new int[nVertices];
    }
}

bool Graph::isEdge(int u,int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
            cout<<"vertex out of range"<<endl;
            return false;
    }
    for(Edge *ed : adjlist[u])
    {
        if(ed->getv()==v){
                return true; }
    }
    return false;
}

bool Graph::addEdge(int u,int v,double w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
            cout<<"vertex out of range"<<endl;
            return false;
    }
    if(!isEdge(u,v)){
    nEdges++;
    Edge *ed=new Edge;
    ed->setu(u);
    ed->setv(v);
    ed->setW(w);
    edges.push_back(ed);
    adjlist[u].push_back(ed);
    return true;
    }
    else{
        return false;
    }
}
Edge* Graph::searchEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
            cout<<"vertex out of range"<<endl;
            return NULL;
    }
    for(Edge *ed : adjlist[u])
    {
        if(ed->getv()==v){
                return ed;
            }
    }
    return NULL;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
            cout<<"vertex out of range"<<endl;
            return;
    }
    Edge *ed=searchEdge(u,v);
    if(ed==NULL) return;
    int c=0,idx=-1;
    for(Edge *ed : edges)
    {
        if(ed->getv()==v && ed->getu()==u)
        {
            idx=c;
            break;
        }
        c++;
    }
    edges[idx]=edges[edges.size()-1];
    edges.pop_back();
    c=0;
    idx=-1;
    for(Edge *ed: adjlist[u])
    {
        if(ed->getv() ==v)
        {
            idx=c;
            break;
        }
        c++;
    }
    adjlist[u][c]=adjlist[u][adjlist[u].size()-1];
    adjlist[u].pop_back();
    delete ed;
}

double Graph::getWeight(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
            cout<<"vertex out of range"<<endl;
            return INF;
    }
    Edge *ed=searchEdge(u,v);
    if(ed==NULL) return INF;
    return ed->getw();

}
void Graph::reweightEdge(int u, int v, double w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
            cout<<"vertex out of range"<<endl;
            return;
    }
    Edge *ed=searchEdge(u,v);
    if(ed==NULL)
    {
        addEdge(u,v,w);
    }
    else{
        ed->setW(w);
    }
}
void Graph::cleanSPinfo()
{
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            distanceMatrix[i][j]=INF;
            parentMatrix[i][j]=-1;
        }
    }
}

void Graph::printDistanceMatrix()
{
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            if(distanceMatrix[i][j]!=INF){
                cout<<distanceMatrix[i][j]<<"\t";
            }
            else{
                cout<<"INF\t";
            }
        }
        cout<<endl;
    }
}
void Graph::printPredecessorMatrix()
{
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            if(parentMatrix[i][j]!=-1)
                cout<<parentMatrix[i][j]+1<<"\t";
            else{
                cout<<"NIL\t";
            }
        }
        cout<<endl;
    }
}

void Graph::printGraph()
{
    for(int i=0;i<nVertices;i++)
    {
        cout<<i+1<<" : ";
        for(Edge *ed : adjlist[i])
        {
            cout<<"--> ";
            cout<<ed->getv()+1<<"("<<ed->getw()<<")";

        }
        cout<<endl;
    }
}


bool Graph::BellmanFord(int source)
{
    for(int i=0;i<nVertices;i++)
        {
            distance[i]=INF;
        }
        distance[source]=0;
        parent[source]=-1;
        for(int i=0;i<nVertices-1;i++)
        {
            for(Edge *ed : edges)
            {
                int u=ed->getu();
                int v=ed->getv();
                double w=ed->getw();

                if(distance[v]>distance[u]+w)
                 {
                    parent[v]=u;
                    distance[v]=distance[u]+w;
                 }
            }
        }
        for(int i=0;i<nVertices-1;i++)
        {
            for(Edge *ed : edges)
            {
                int u=ed->getu();
                int v=ed->getv();
                int w=ed->getw();

                if(distance[v]>distance[u]+w)
                 {
                    return true;
                 }
            }
        }
        return false;
}

void Graph::dijkstra(int source)
{
    MinHeap Pq(nVertices);
    bool visited[nVertices];
    for(int i=0;i<nVertices;i++)
        {
            visited[i]=false;
            Pq.Insert(i,INF);
        }
    distance1[source]=0;
    parent1[source]=-1;
    Pq.DecreaseKey(source,0);
    int u,v;
    double w;
    while(!Pq.Empty())
    {
        struct Node temp=Pq.ExtractMin();
        u=temp.v;
        w=temp.d;
        visited[u]=true;
        for(Edge *ed :adjlist[u])
        {
            v=ed->getv();
            double wt=ed->getw();
            if(!visited[v]){
                wt=abs(wt);
                int idx=Pq.pos[v];
                if(Pq.arr[idx].d>wt+w)
                    {
                    parent1[v]=u;
                    distance1[v]=wt+w;
                    Pq.DecreaseKey(v,wt+w);
            }
          }
        }
    }
}

void Graph::floydWarshall()
{
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            if(i==j) distanceMatrix[i][j]=0;
            else distanceMatrix[i][j]=INF;
            parentMatrix[i][j]=-1;
        }
    }

    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            Edge *ed=searchEdge(i,j);
            if(ed!=NULL)
            {
                distanceMatrix[i][j]=ed->getw();
                parentMatrix[i][j]=i;
            }
        }
    }
    for(int k=0;k<nVertices;k++)
    {
        for(int i=0;i<nVertices;i++)
        {
            for(int j=0;j<nVertices;j++)
            {
                if(distanceMatrix[i][j]>distanceMatrix[i][k]+distanceMatrix[k][j])
                {
                    parentMatrix[i][j]=parentMatrix[k][j];
                    distanceMatrix[i][j]=distanceMatrix[i][k]+distanceMatrix[k][j];
                }
            }
        }
    }
}

double Graph::getShortestPathWeight(int u ,int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
            //cout<<"vertex out of range"<<endl;
            return INF;
    }
    return distanceMatrix[u][v];
}

void Graph::johnsonsAlgo()
{
    double **prevWeight;
    int vertices=nVertices;
    nVertices++;
    vector<Edge*> *ed=new vector<Edge*>;
    adjlist.push_back(*ed);
    prevWeight = new double*[nVertices];
    distanceMatrix = new double*[nVertices];
    parentMatrix = new int*[nVertices];
    distance=new double[nVertices];
    parent=new int[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        prevWeight[i] = new double[nVertices];
        distanceMatrix[i] = new double[nVertices];
        parentMatrix[i] = new int[nVertices];
    }
    for(int i=0;i<vertices;i++)
    {
        addEdge(vertices,i,0);
    }
    bool cycle=BellmanFord(vertices);
    if(cycle)
    {
        cout<<"There is a negative weight cycle in the graph"<<endl;
    }
    else{
        BellmanFord(vertices);
        for(Edge *ed : edges)
            {
                int u=ed->getu();
                int v=ed->getv();
                double w=ed->getw();
                prevWeight[u][v]=w;
                double w1;
                w1=w+distance[u]-distance[v];
                reweightEdge(u,v,w1);
            }
        for(int i=0;i<nVertices;i++)
            {
                for(int j=0;j<nVertices;j++)
                {
                    if(i==j)
                    {
                        distanceMatrix[i][j]=0;
                        parentMatrix[i][j]=-1;
                    }
                    else{
                        parentMatrix[i][j]=i;
                    }
                }
            }

        for(int i=0;i<vertices;i++)
        {
            removeEdge(vertices,i);
        }

        for(int i=0;i<vertices;i++)
            {
                dijkstra(i);
                for(int j=0;j<vertices;j++)
                {
                    if(i!=j){
                    distanceMatrix[i][j]=distance1[j]+distance[j]-distance[i];
                    parentMatrix[i][j]=parent1[j];
                    }
                }
            }


        for(Edge *ed : edges)
        {
            int u=ed->getu();
            int v=ed->getv();
            //cout<<u<<" "<<v<<" "<<ed->getw()<<endl;
            reweightEdge(u,v,prevWeight[u][v]);
        }

    }
    nVertices=vertices;
}
void Graph::printShortestPath(int u, int v)
{
    if(u==v)
    {
        cout<<u+1;
        return;
    }
    int p=parentMatrix[u][v];
    printShortestPath(u,p);

    cout<<"-->"<<v+1<<"("<<getWeight(p,v)<<")";
}



Graph::~Graph()
{
    if(distance) delete []distance;
    if(distance1) delete []distance1;
    if(parent) delete []parent;
    if(parent1) delete []parent1;
    for(int i = 0; i < nVertices; ++i) {
        delete []distanceMatrix[i];
        delete []parentMatrix[i];
        distanceMatrix[i]=0;
        parentMatrix[i]=0;
    }
    delete []parentMatrix;
    delete []distanceMatrix;
}



int main()
{
    fstream in("in.txt");
    int n,edges,u,v;
    double w;
    in>>n;
    in>>edges;
    cout<<n<<" "<<edges<<endl;
    int choice;
    Graph g;
    g.setnVertices(n);
    while(edges>0)
    {
        in>>u;
        in>>v;
        in>>w;
        //cout<<u<<" "<<v<<" "<<w<<endl;
        if(!g.isEdge(u-1,v-1))
                g.addEdge(u-1,v-1,w);
        edges=edges-1;
    }
    in.close();
    cout<<"Graph Created"<<endl;
    g.cleanSPinfo();
    while(1)
    {
    cout << "Enter a number : " <<endl;
    cout << "1: call Clear SP values" <<"        " << "2:Floyd warshall algo" <<endl;
    cout << "3: Johnson's algo" <<"              " << "4: Shortest path between two vertices" <<endl;
    cout << "5: Print Graph"<<"                 "<<"6:distance matrix"<<endl;
    cout << "7: parent matrix" <<endl;

        int ch;
        int u, v;
        scanf("%d",&ch);
        if(ch==1)
        {
            g.cleanSPinfo();
            cout<<"APSP matrices cleared"<<endl;

        }
        else if(ch==2)
        {
            g.floydWarshall();
            cout<<"Floyd warshall Algorithm Implemented"<<endl;

        }
        else if(ch==3)
        {
            g.johnsonsAlgo();
            cout<<"johnson's algorithm implemented"<<endl;
        }
        else if(ch==4)
        {
            cout<<"Enter the starting vertex: "<<endl;
            cin>>u;
            cout<<"Enter the destination : "<<endl;
            cin>>v;
            int sd=g.getShortestPathWeight(u-1,v-1);
            cout<<"Shortest path weight : "<<sd<<endl;
            g.printShortestPath(u-1,v-1);
            cout<<endl;
        }
        else if(ch==5)
        {
            cout<<"Graph :"<<endl;
            g.printGraph();

        }
        else if(ch==6)
        {
            cout<<"Distance Matrix : "<<endl;
            g.printDistanceMatrix();
        }
        else if(ch==7)
        {
            cout<<"Predecessor Matrix : "<<endl;
            g.printPredecessorMatrix();
        }
        else{
            break;
        }
    }
}
