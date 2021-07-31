#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<stack>
#include<queue>
#define NULL_VALUE -999999
#define INFINITY 9999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;

struct Edges
{
    int u,v,w;
};
/*class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int *data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************
*/
//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************
struct Node
    {
        int v;
        int d;
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
    void Insert(int v,int dis)
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

    void DecreaseKey(int i,int key)
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

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	ArrayList * weightList;
	struct Edges *ed;
	int *parent;

public:
	Graph(bool dir = false);
	~Graph();
	fstream out;
	int cycleCheck;
	int *d; //distance array for Bell_man Ford algo
	int *dd; //distance array for dijkstra algo
	void setnVertices(int n,int m=1000);
	void addEdge(int u, int v,int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getOutDegree(int u);
    int getInDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void BellmanFord(int source);
	void dijkstra(int source);
    void printPath(int v);
};


Graph::Graph(bool dir)
{
	nVertices = 0;
	nEdges = 0;
	adjList = 0;
	directed = dir ;//set direction of the graph
	weightList=0;
    d=0;
    ed=0;
    dd=0;
    parent=0;
    cycleCheck=-1;
	//define other variables to be initialized
}

void Graph::setnVertices(int n,int m)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices];
	weightList=new ArrayList[nVertices];
    d=new int[nVertices];
    dd=new int[nVertices];
    parent=new int[nVertices];
    ed=new Edges[m];
}

void Graph::addEdge(int u, int v,int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
            cout<<"vertex out of range"<<endl;
            return; //vertex out of range
    }
    ed[nEdges].u=u;
    ed[nEdges].v=v;
    ed[nEdges].w=w;
    this->nEdges++;
	adjList[u].insertItem(v);
    weightList[u].insertItem(w);
    //cout<<"added"<<endl;
	if(!directed) {
            adjList[v].insertItem(u) ;
            weightList[v].insertItem(w);
	}
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
        cout<<"vertex out of range"<<endl;
            return;
    }
    if(isEdge(u,v)){
    int p=adjList[u].searchItem(v);
    adjList[u].removeItem(v);
    weightList[u].removeItemAt(p);
    this->nEdges--;
    if(!directed) {
            int p1=adjList[v].searchItem(u);
            adjList[v].removeItem(u);
            weightList[v].removeItemAt(p1);
    }
    cout<<"Delete Successfully"<<endl;
    }
    else
    {
        cout<<"there is no edge to delete"<<endl;
    }
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
            cout<<"vertex out of range"<<endl;
            return false;
    }
    if(adjList[u].searchItem(v) != NULL_VALUE)
        return true;
    return false;
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getOutDegree(int u)
{
    if(u<0 || u>=nVertices) {
            cout<<"vertex out of range"<<endl;
            return NULL_VALUE;
    }
    return adjList[u].getLength();
}

int Graph::getInDegree(int u)
{
    if(u<0 || u>=nVertices) {
            cout<<"vertex out of range"<<endl;
            return NULL_VALUE;
    }
    int c=0;
    for(int i=0;i<nVertices;i++)
        {
            if(isEdge(i,u))
                c++;
        }
    return c;
}

void Graph::printAdjVertices(int u)
{
    if(u<0 || u>=nVertices) {
        cout<<"vertex out of range"<<endl;
        return;
    }
    int idx=-1;
    for(int i=0;i<adjList[u].getLength();i++){
        idx=1;
        cout<<"Adjacent Vertex :"<<adjList[u].getItem(i)<<"   Weight : "<<weightList[u].getItem(i)<<endl;
    }
    if(idx==-1) cout<<"there is no adjacent vertex of "<<u<<endl;
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
            cout<<"vertex out of range"<<endl;
            return false;
    }
    for(int i=0;i<adjList[u].getLength();i++)
    {
        for(int j=0;j<adjList[v].getLength();j++)
        {
            if(adjList[u].getItem(i)==adjList[v].getItem(j))
            {
                return true;
            }
        }
    }
    return false;
    //returns true if vertices u and v have common adjacent vertices

}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

void Graph::BellmanFord(int source)
{

        for(int i=0;i<nVertices;i++)
        {
            d[i]=INFINITY;
        }
        d[source]=0;
        parent[source]=-1;
        for(int i=0;i<nVertices-1;i++)
        {
            for(int j=0;j<nEdges;j++)
            {
                int u=ed[j].u;
                int v=ed[j].v;
                int w=ed[j].w;

                if(d[v]>d[u]+w)
                 {
                     parent[v]=u;
                    d[v]=d[u]+w;
                 }
            }
        }
        for(int i=0;i<nVertices-1;i++)
        {
            for(int j=0;j<nEdges;j++)
            {
                int u=ed[j].u;
                int v=ed[j].v;
                int w=ed[j].w;

                if(d[v]>d[u]+w)
                 {
                    out<<"Bellman Ford Algorithm : "<<endl;
                    out<<"The graph has negative weight cycle.So No shortest path"<<endl<<endl;
                    cout<<"The graph has negative weight cycle.So No shortest path"<<endl;
                    cycleCheck=1;
                    return;
                 }
            }
        }
        /*for(int i=0;i<nVertices;i++)
            cout<<d[i]<<" ";
        cout<<endl;*/
}

void Graph::dijkstra(int source)
{
    MinHeap Pq(nVertices);
    bool visited[nVertices];
    for(int i=0;i<nVertices;i++)
        {
            visited[i]=false;
            Pq.Insert(i,INFINITY);
        }
    dd[source]=0;
    parent[source]=-1;
    Pq.DecreaseKey(source,0);
    int u,v,w;
    while(!Pq.Empty())
    {
        struct Node temp=Pq.ExtractMin();
        u=temp.v;
        w=temp.d;
        visited[u]=true;
        for(int i=0;i<adjList[u].getLength();i++)
        {
            v=adjList[u].getItem(i);
            int wt=weightList[u].getItem(i);

            if(!visited[v]){
                if(wt<0)
                    wt=wt*-1;
                int idx=Pq.pos[v];
                if(Pq.arr[idx].d>wt+w)
                    {
                    parent[v]=u;
                    dd[v]=wt+w;
                    Pq.DecreaseKey(v,wt+w);
            }
          }
        }
    }
    /*for(int i=0;i<nVertices;i++)
        cout<<dd[i]<<" ";
    cout<<endl;*/
}

void Graph::printPath(int v)
{
    if(v<0)
        return;
    printPath(parent[v]);
    if(parent[v]>=0){
        out<<" -> "<<v;
        cout<<" -> "<<v;
    }
    else{
        out<<v;
        cout<<v;
    }
}

int Graph::getDist(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        cout<<"vertex out of range"<<endl;
        return INFINITY;
    }
    BellmanFord(u);
    return d[v];
}

Graph::~Graph()
{
    if(adjList) delete []adjList;
    if(weightList) delete []weightList;
    if(parent) delete []parent;
    if(d) delete[]d;
    if(dd) delete []dd;
    d=0;
    dd=0;
    parent=0;
    adjList=0;
    weightList=0;
}

int main(void)
{
    fstream in("in.txt");
    int n,edges,u,v,w,s1,s2;
    in>>n;
    in>>edges;
    cout<<n<<" "<<edges<<endl;
    int choice;
    bool dir=true;
    Graph g(dir);
    g.setnVertices(n,edges);

    while(edges>0)
    {
        in>>u;
        in>>v;
        in>>w;
        cout<<u<<" "<<v<<" "<<w<<endl;
        if(!g.isEdge(u,v))
                g.addEdge(u,v,w);
        edges=edges-1;
    }
    in>>s1;
    in>>s2;

    g.out.open("out.txt");
    g.BellmanFord(s1);
    if(g.cycleCheck<0){
    cout<<"Bellman Ford Algorithm : "<<endl;
    g.out<<"Bellman Ford Algorithm : "<<endl;
    g.out<<g.d[s2]<<endl;
    cout<<g.d[s2]<<endl;
    g.printPath(s2);
    cout<<endl;
    g.out<<endl<<endl;
    }
    g.dijkstra(s1);
    cout<<"Dijkstra Algorithm :"<<endl;
    g.out<<"Dijkstra Algorithm :"<<endl;
    g.out<<g.dd[s2]<<endl;
    cout<<g.dd[s2]<<endl;
    g.printPath(s2);
    cout<<endl;
    g.out.close();

    while(1)
    {
    cout << "Enter a number : " <<endl;
    cout << "1: Add edge" <<"        " << "6: Get In Degree" <<endl;
    cout << "2: Delete edge" <<"     " << "7: Print Adj Vertexes" <<endl;
    cout << "3: Is Edge"<<"         "<<"8: hasCommonAdjacent"<<endl;
    cout << "4: Get Out degree" <<"  " << "9: Print Graph" <<endl;
    cout << "5: Get Distance" <<"    " << "10: Exit" <<endl;
    cout<<"11: Dijkstra Algorithm"<<endl;
    cout<<"12: Bellman Ford Algorithm"<<endl;

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
            if(!g.isEdge(u,v))
                g.addEdge(u, v,w);
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
        }
        else if(ch==3)
        {
            cout<<"Enter the first vertex : "<<endl;;
            cin>>u;
            cout<<"Enter the Second vertex : "<<endl;
            cin>>v;
        if(g.isEdge(u,v))
            cout<<"there is a edge between "<<u<<" and "<<v<<endl;
        else
            cout<<"there is no edge"<<endl;
        }
        else if(ch==4)
        {
        int s;
        cout<<"Enter the vertex : "<<endl;
        cin>>s;
        cout<<g.getOutDegree(s)<<endl;
        }
        else if(ch==5)
        {
        cout<<"Enter the first vertex : "<<endl;;
        cin>>u;
        cout<<"Enter the Second vertex : "<<endl;
        cin>>v;
        int d;
        d=g.getDist(u,v);
        //if(d!=INFINITY)
        cout<<"the distance between "<<u<<" and "<<v <<" using Bellman Ford algorithm is : "<<d<<endl;
        g.dijkstra(u);
        cout<<"the distance between "<<u<<" and "<<v <<" using Dijkstra algorithm is : "<<g.dd[v]<<endl;
        }
        else if(ch==6)
        {
        cout<<"Enter the vertex :"<<endl;
        cin>>v;
        int d;
        d=g.getInDegree(v);
            cout<<"Degree : "<<d<<endl;
        }
        else if(ch==7)
        {
        cout<<"Enter the vertex : "<<endl;
        cin>>u;
        g.printAdjVertices(u);
        }
        else if(ch==8)
        {
            cout<<"Enter the first vertex : "<<endl;;
            cin>>u;
            cout<<"Enter the Second vertex : "<<endl;
            cin>>v;

            if(g.hasCommonAdjacent(u,v)) cout<<"Yes they have common adjacent"<<endl;
            else
                cout<<"there is no common adjacent"<<endl;
        }
        else if(ch==9)
        {
            g.printGraph();
        }
        else if(ch==10)
        {
            break;
        }
        else if(ch==11)
        {
            g.out.open("out.txt");
            g.dijkstra(s1);
            cout<<"Dijkstra Algorithm :"<<endl;
            g.out<<"Dijkstra Algorithm :"<<endl;
            g.out<<g.dd[s2]<<endl;
            cout<<g.dd[s2]<<endl;
            g.printPath(s2);
            cout<<endl;
            g.out.close();
        }
        else if(ch==12)
        {
            g.out.open("out.txt");
            g.BellmanFord(s1);
            if(g.cycleCheck<0){
            cout<<"Bellman Ford Algorithm: "<<endl;
            g.out<<"Bellman Ford Algorithm: "<<endl;
            g.out<<g.d[s2]<<endl;
            cout<<g.d[s2]<<endl;
            g.printPath(s2);
            cout<<endl;
            }
            g.out.close();
        }
    }

}
