#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<ctime>
#include <chrono>
#include <fstream>
#include <typeinfo>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;
using namespace std::chrono;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
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

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int *color,*dcolor;
	int *dist,*dis,*finish;
	int *parent,*dparent;
	int time;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	bool addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getOutDegree(int u);
    int getInDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(int source);
	void dfs_visit(int u);

};



Graph::Graph(bool dir)
{
	nVertices = 0;
	nEdges = 0;
	adjList = 0;
	directed = dir ; //set direction of the graph
    color=0;
    dist=0;
    parent=0;
    dcolor=0;
    dis=0;
    finish=0;
    dparent=0;
    time=0;
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
    color=new int[nVertices];
    dist=new int[nVertices];
    parent=new int[nVertices];
    dcolor=new int[nVertices];
    dis=new int[nVertices];
    finish=new int[nVertices];
    dparent=new int[nVertices];
}

bool Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
            //cout<<"vertex out of range"<<endl;
            return false; //vertex out of range
    }
    this->nEdges++;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
	//cout<<"Added Successfully"<<endl;
	return true;
}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) {
        cout<<"vertex out of range"<<endl;
            return;
    }
    if(isEdge(u,v)){
    adjList[u].removeItem(v);
    if(!directed) adjList[v].removeItem(u);
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
            //cout<<"vertex out of range"<<endl;
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
    /*if(!out){
        int c=0;
        for(int i=0;i<nVertices;i++)
        {
            if(isEdge(i,u))
                c++;
        }
    return c;
    }*/
    //returns the degree of vertex u
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
        cout<<"Adjacent Vertex :"<<adjList[u].getItem(i)<<endl;
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

void Graph::bfs(int source)
{
    if(source<0 || source>=nVertices) {
        //cout<<"vertex out of range"<<endl;
        return;
    }
    cout<<source<<" ";
    for(int i=0;i<nVertices;i++)
    {
        color[i]=WHITE;
    }
    Queue q;
    q.enqueue(source);
    color[source]=GREY;
    dist[source]=0;
    parent[source]=source;
    while(!q.empty())
    {
        int u=q.dequeue();

        for(int i=0;i<adjList[u].getLength();i++){
                int v=adjList[u].getItem(i);
                if(color[v]==WHITE)
                {
                    cout<<v<<" ";
                    color[v]=GREY;
                    dist[v]=dist[u]+1;
                    parent[v]=u;
                    q.enqueue(v);
                }
        }
        color[u]=BLACK;
    }
    cout<<endl;
    //complete this function
    //initialize BFS variables for all n vertices first

}

void Graph::dfs_visit(int u)
{
    cout<<u<<" ";
    dcolor[u]=GREY;
    time=time+1;
    dis[u]=time;
    for(int i=0;i<adjList[u].getLength();i++){
            int v=adjList[u].getItem(i);
                if(dcolor[v]==WHITE)
                {
                    dparent[v]=u;

                    dfs_visit(v);
                }
        }
    dcolor[u]=BLACK;
    time=time+1;
    finish[u]=time;
}

void Graph::dfs(int source)
{
    if(source<0 || source>=nVertices) {
        cout<<"vertex out of range"<<endl;
        return;
    }

    for(int i=0;i<nVertices;i++)
    {
        dcolor[i]=WHITE;
    }
    time=0;
    dfs_visit(source);
    cout<<endl;
}

int Graph::getDist(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)
    {
        cout<<"vertex out of range"<<endl;
        return INFINITY;
    }
    bfs(u);
    if(color[v]==WHITE)
    {
        cout<<"there is no path between "<<u <<" and "<<v<<endl;
        return INFINITY;
    }
    //cout<<dist[v]<<endl;
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    return dist[v];
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

Graph::~Graph()
{
    if(adjList) delete []adjList;
    if(color) delete []color;
    if(dist) delete []dist;
    if(parent) delete[]parent;
    if(dcolor) delete []dcolor;
    if(dis) delete []dis;
    if(finish) delete []finish;
    if(dparent) delete[]dparent;
    adjList=0;
    color=0;
    dist=0;
    parent=0;
    dcolor=0;
    dis=0;
    finish=0;
    dparent=0;
    //write your destructor here
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    srand(time(0));
    fstream file("datalist.txt");
    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir),gt(dir);
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
    cout << "Enter a number : " <<endl;
    cout << "1: Add edge" <<"        " << "6: Get Out Degree" <<endl;
    cout << "2: Delete edge" <<"     " << "7: Print Adj Vertexes" <<endl;
    cout << "3: Is Edge"<<"         "<<"8: hasCommonAdjacent"<<endl;
    cout << "4: BFS" <<"             " << "9: Print Graph" <<endl;
    cout << "5: Get In Degree" <<"   " << "10: DFS" <<endl;
    cout<< "11: Get Distance"<<"   "<<"12: Exit"<<endl;
    cout<<"13: Get BFS time"<<endl;

        int ch;
        int u, v;
        scanf("%d",&ch);
        if(ch==1)
        {
            cout<<"Enter the first vertex : "<<endl;;
            cin>>u;
            cout<<"Enter the Second vertex : "<<endl;
            cin>>v;
            if(!g.isEdge(u,v)){
                int rb=g.addEdge(u, v);
                if(rb) cout<<"true"<<endl;
                else cout<<"false"<<endl;
            }
            else{
                cout<<"there is already an edge between "<<u<<" and "<<v<<endl;
                cout<<"false"<<endl;
            }
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
        cout<<"Enter the source : "<<endl;
        cin>>s;
        g.bfs(s);
        }
        else if(ch==11)
        {
        cout<<"Enter the first vertex : "<<endl;;
        cin>>u;
        cout<<"Enter the Second vertex : "<<endl;
        cin>>v;
        int d;
        d=g.getDist(u,v);
        if(d!=INFINITY) cout<<"the distance between "<<u<<" and "<<v <<" is : "<<d<<endl;
        }
        else if(ch==5)
        {
            cout<<"Enter the vertex: "<<endl;
            cin>>v;
            int d1;
            d1=g.getInDegree(v);
            if(d1==NULL_VALUE) cout<<"this vertex is not in the graph"<<endl;
            else
                cout<<"In Degree : "<<d1<<endl;
        }
        else if(ch==6)
        {
        cout<<"Enter the vertex :"<<endl;
        cin>>v;
        int d;
        d=g.getOutDegree(v);
        if(d==NULL_VALUE) cout<<"this vertex is not in the graph"<<endl;
        else
            cout<<"Out Degree : "<<d<<endl;
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
            int s1;
            cout<<"Enter the source : "<<endl;
            cin>>s1;
            g.dfs(s1);
        }
        else if(ch==12)
        {
        break;
        }
        else if(ch==13)
            {
            int ver,time,ftime=0;
            double avtime;
            cout<<"Enter the Number of vertices : "<<endl;
            cin>>ver;
            gt.setnVertices(ver);
            for(int i=ver;i<(((ver*ver)-ver)/8);i=2*i)
            {
                for(int j=0;j<i;j++){
                    u=rand()%i;
                    v=rand()%i;
                    if(!gt.isEdge(u,v))
                    {
                        gt.addEdge(u,v);
                    }
                }

                for(int k=0;k<10;k++)
                {
                    u=rand()%i;
                    auto start = high_resolution_clock::now();
                    gt.bfs(u);
                    auto stop = high_resolution_clock::now();
                    auto duration = duration_cast<microseconds>(stop - start);
                    time=duration.count();
                    ftime+=time;
                }
                avtime=ftime/10.0;
                file<<ver<<" "<<i<<" "<<avtime<<endl;
                cout<<"vertices : "<<ver <<" edges: "<<i<<" . time for bfs in microseconds : "<<avtime<<endl;
            }


        }
    }

}
