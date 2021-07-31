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
    Edge(int u,int v,double w)
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
 bool compByweight( Edge* a,Edge* b)
    {
        return a->getw() < b->getw();
    }
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

class Set
{
    int *p,*r,Max;
public:
    int v;
    Set(int n)
    {
        Max=n;
        v=0;
        p=new int[Max];
        r=new int[Max];
        for(int i=0;i<Max;i++)
        {
            p[i]=v;
            r[i]=v;
        }
    }
    ~Set()
    {
        delete []p;
        delete []r;
    }
    void Make_set(int x)
    {
        p[x]=x;
        r[x]=0;
    }

    int Find(int x)
    {
        if(x!=p[x])
            p[x]=Find(p[x]);
        return p[x];
    }

    void Union(int x,int y)
    {
        int a=Find(x);
        int b=Find(y);
        if(a==b)
            return;
        if(r[a]>r[b])
            p[b]=a;
        else{
            p[a]=b;
            if(r[a]==r[b])
                r[b]++;
        }
    }

    int pFind(int x)
    {
        if(x!=p[x])
            pFind(p[x]);
        return p[x];
    }

    void print(int x)
    {
        int a=pFind(x);
        cout<<a<<" ";
        for(int i=0;i<Max;i++)
        {
            if(i!=a && a==pFind(i))
                cout<<i<<" ";
        }
        cout<<endl;
    }
};


class Graph
{
    fstream out;
    int nVertices,nEdges;
    vector<vector<Edge*>> adjlist;
    vector<Edge*> edges;
	double *distance;
	int *parent;
public:
    Graph();
    ~Graph();
    void setnVertices(int n);
    bool addEdge(int u, int v, double w);
    void removeEdge(int u, int v);
    Edge* searchEdge(int u, int v);
    bool isEdge(int u, int v);
    double getWeight(int u, int v);
    void printGraph();

	void Prim(int source);
	void kruskal();

};

Graph::Graph()
{
    out.open("out.txt");
    nVertices=0;
    nEdges=0;
    distance=0;
    parent=0;
}

void Graph::setnVertices(int n)
{
    nVertices=n;
    for(int i=0;i<nVertices;i++)
    {
        vector<Edge*> *ed=new vector<Edge*>;
        adjlist.push_back(*ed);
    }
    distance=new double[nVertices];
    parent=new int[nVertices];
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
    this->nEdges--;
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
    adjlist[u][idx]=adjlist[u][adjlist[u].size()-1];
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

void Graph::printGraph()
{
    for(int i=0;i<nVertices;i++)
    {
        cout<<i<<" : ";
        for(Edge *ed : adjlist[i])
        {
            cout<<"--> ";
            cout<<ed->getv()<<"("<<ed->getw()<<")";

        }
        cout<<endl;
    }
}

void Graph::Prim(int source)
{
    vector <Edge*> taken;
    MinHeap Pq(nVertices);
    bool visited[nVertices];
    for(int i=0;i<nVertices;i++)
        {
            visited[i]=false;
            Pq.Insert(i,INF);
        }
    distance[source]=0;
    parent[source]=-1;
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
                //wt=abs(wt);
                int idx=Pq.pos[v];
                if(Pq.arr[idx].d>wt)
                    {
                    taken.push_back(ed);
                    parent[v]=u;
                    distance[v]=wt;
                    Pq.DecreaseKey(v,wt);
            }
          }
        }
    }
    int sum=0;
    for(int i=0;i<nVertices;i++)
    {
        sum+=distance[i];
        //cout<<distance[i]<<" ";
    }
    cout<<sum<<endl;
    out<<sum<<endl;
    cout<<"Prim's Algorithm : "<<endl;
    out<<"Prim's Algorithm : "<<endl;
    cout<<"Root node = "<<source<<endl;
    out<<"Root node = "<<source<<endl;
    for(Edge *ed:taken)
    {
        if(ed->getu() == parent[ed->getv()]){
                cout<<ed->getu()<<" "<<ed->getv()<<endl;
                out<<ed->getu()<<" "<<ed->getv()<<endl;
        }
    }
    //cout<<endl;
    //out<<endl;
}

void Graph::kruskal()
{
    int sum=0;
    vector <Edge*> taken;
    Set s(nVertices);
    for(int i=0;i<nVertices;i++)
    {
        s.Make_set(i);
    }
    sort(edges.begin(),edges.end(),compByweight);
    for(Edge *ed: edges)
    {
        int a=s.Find(ed->getu());
        int b=s.Find(ed->getv());
        if(a!=b)
        {
            sum+=ed->getw();
            taken.push_back(ed);
            s.Union(a,b);
        }
    }
    cout<<sum<<endl;
    out<<sum<<endl;
    cout<<"Kruskal's Algorithm : "<<endl;
    out<<"Kruskal's Algorithm : "<<endl;
    for(Edge *ed:taken)
    {
        out<<ed->getu()<<" "<<ed->getv()<<endl;
        cout<<ed->getu()<<" "<<ed->getv()<<endl;
    }
    //out<<endl;
    //cout<<endl;
}


Graph::~Graph()
{
    if(distance) delete []distance;
    if(parent) delete []parent;
}



int main()
{
    srand(time(0));
    fstream in("in.txt");
    int n,edges,u,v;
    double w;
    in>>n;
    in>>edges;
    //cout<<n<<" "<<edges<<endl;
    int choice;
    Graph g;
    g.setnVertices(n);
    while(edges>0)
    {
        in>>u;
        in>>v;
        in>>w;
        //cout<<u<<" "<<v<<" "<<w<<endl;
        if(!g.isEdge(u,v)){
                g.addEdge(u,v,w);
                g.addEdge(v,u,w);
        }
        edges=edges-1;
    }
    in.close();
    //cout<<"Graph Created"<<endl;
    int root=rand()%n;
    g.kruskal();
    g.Prim(root);
    while(1)
    {
    cout << "Enter a number : " <<endl;
    cout << "1: add edge" <<"                      " << "2: Remove edge" <<endl;
    cout << "3: Prim's algorithm" <<"              " << "4: Kruskal's algorithm" <<endl;
    cout << "5: Print Graph"<<endl;

        int ch;
        int u, v;
        scanf("%d",&ch);
        if(ch==1)
        {
            cout<<"Enter the first vertex : "<<endl;;
            cin>>u;
            cout<<"Enter the Second vertex : "<<endl;
            cin>>v;
            cout<<"Enter the weight : "<<endl;
            int w;
            cin>>w;
            if(!g.isEdge(u,v)){
                g.addEdge(u,v,w);
                g.addEdge(v,u,w);
            }
            else
                cout<<"there is already an edge between "<<u<<" and "<<v<<endl;
        }
        else if(ch==2)
        {
            cout<<"Enter the first vertex : "<<endl;;
            cin>>u;
            cout<<"Enter the Second vertex : "<<endl;
            cin>>v;
            g.removeEdge(u,v);
            g.removeEdge(v,u);

        }
        else if(ch==3)
        {
            int root=rand()%n;
            g.Prim(root);

        }
        else if(ch==4)
        {
            g.kruskal();

        }
        else if(ch==5)
        {
            g.printGraph();

        }
        else{
            break;
        }
    }
}
