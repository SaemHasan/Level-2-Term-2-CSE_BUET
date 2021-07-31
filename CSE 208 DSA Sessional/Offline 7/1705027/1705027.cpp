#include <bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<stack>
#include<string>
#include <stdlib.h>
#include <sstream>
using namespace std;

class Binomial_heap
{
    struct node
    {
        int value, degree;
        node *parent, *child, *sibling;
    };

    node* prev;
    node* root;

    node* makeHeap()
    {
        node *t=new node;
        t=NULL;
        return t;
    }
    node* newNode(int n)
    {
        node* t=new node;
        t->value=n;
        t->child=t->parent=t->sibling=NULL;
        t->degree=0;
        return t;
    }

    node* LINK(node* y, node* z)
    {
        y->parent=z;
        y->sibling=z->child;
        z->child=y;
        z->degree=z->degree+1;
    }

    node* UNION(node *H1, node* H2)
    {
        node* H = makeHeap();
        H = MERGE(H1,H2);
        if(H==NULL) return H;
        node* x;
        node* prev_x;
        node* next_x;
        x=H;
        next_x=x->sibling;
        prev_x=NULL;
        while(next_x!=NULL)
        {
            if((x->degree!=next_x->degree) || ((next_x->sibling!=NULL) && (next_x->sibling->degree==x->degree)))
            {
                prev_x=x; //case 1 and 2
                x=next_x; //case 1 and 2
                //updadated
                //next_x = next_x->sibling;
            }
            else
            {
                if(x->value<=next_x->value)
                {
                    x->sibling=next_x->sibling; //case 3
                    LINK(next_x,x);//case 3
                }
                else
                {
                    if(prev_x==NULL)  //case 4
                    {
                        H=next_x;//case 4
                    }
                    else
                    {
                        prev_x->sibling=next_x; //case 4
                    }
                    LINK(x,next_x); //case 4
                    x=next_x;//case 4
                }
            }
            next_x=x->sibling;
        }
        return H;
    }

    node* MERGE(node *H1, node *H2)
    {
        node* H = makeHeap();
        node* x;
        node* y;
        x=H1;
        y=H2;
        if(x!=NULL)
        {
            if(y!=NULL)
            {
                if(y->degree>=x->degree)
                {
                    H=x;
                }
                else
                {
                    H=y;
                }
            }
            else
            {
                H=x;
            }
        }
        else
        {
            H=y;
        }
        node *lastUpdated = NULL;
        while(x!=NULL and y!=NULL)
        {
            if(y->degree ==  x->degree )
            {
                if(y !=H)
                {
                    if(lastUpdated != NULL)
                        lastUpdated ->sibling = x;

                    lastUpdated = x;
                    x = x->sibling;
                    if(x == NULL)
                        lastUpdated->sibling =y;
                }
                else
                {
                    if(lastUpdated !=NULL)
                        lastUpdated->sibling=y;
                    lastUpdated = y;
                    y= y->sibling;
                    if(y==NULL)
                        lastUpdated->sibling = x;

                }
            }
            else if (y->degree > x->degree)
            {
                node * t = x->sibling;
                if(lastUpdated != NULL)
                    lastUpdated->sibling = x;
                lastUpdated =x;
                x = x->sibling;
                 if(x == NULL)
                        lastUpdated->sibling =y;
            }
            else
            {
                if(lastUpdated != NULL)
                    lastUpdated->sibling = y;
                lastUpdated = y;
                y = y->sibling;
                if(y==NULL)
                        lastUpdated->sibling = x;
            }
        }
        return H;
    }


    node* INSERT(node* H, int n)
    {
        node*  te = newNode(n);
        node *H1=new node;
        H1=te;
        H= UNION(H,H1);
        return H;
    }

    node* find_Min(node *H)
    {
        node *y=NULL;
        node* x=H;
        int Min = 99999;
        node* pre;
        pre=NULL;
        while(x!=NULL)
        {
            if(x->value<Min)
            {
                Min=x->value;
                y=x;
                prev=pre;
            }
            pre=x;
            x=x->sibling;
        }
        return y;
    }

    node* Extract_Min(node *H)
    {
        node* x= find_Min(H);
        if(x==H)
        {
            H=x->sibling;
        }
        if(prev!=NULL)
        {
            prev->sibling=x->sibling;
        }
        node *t= x->child;
        while(t!=NULL)
        {
            t->parent=NULL;
            node* t1=t->sibling;
            t->sibling=NULL;
            H=UNION(H,t);
            t=t1;
        }
        root=H;
        return x;

    }

    void printLevelOrder(node *h)
    {
        if (h == NULL) return;
        queue<node *> q;
        q.push(h);
        int level=0;
        while (q.empty() == false)
        {
            int nodeCount = q.size();
            cout<<"Level "<<level<<" : ";
            while (nodeCount > 0)
            {
                node *Node = q.front();
                cout << Node->value << " ";
                q.pop();
                node* t;
                if (Node->child != NULL)
                {
                    q.push(Node->child);
                    t=Node->child;
                }
                for(int i=0; i<Node->degree-1; i++)
                {
                    q.push(t->sibling);
                    t=t->sibling;
                }
                if (Node->sibling != NULL && Node->parent!=Node->sibling->parent)
                    printLevelOrder(Node->sibling);
                nodeCount--;
            }
            level++;
            cout << endl;
        }
    }

public:

    Binomial_heap()
    {
        root= makeHeap();
        prev=makeHeap();
    }
    node* getRoot()
    {
        return root;
    }
    void insert(int n)
    {
        root=INSERT(root,n);
    }

    void FIND_MIN()
    {
        node* t=find_Min(root);
        if(t!=NULL) cout<<"Find-Min returned "<<t->value<<endl;
        else cout<<"heap is empty\n";
    }

    void extract_MIN()
    {
        node* t=Extract_Min(root);
        if(t!=NULL) cout<<"Extract-Min returned "<<t->value<<endl;
        else cout<<"heap is empty\n";
    }

    void Union(node* H2)
    {
        root=UNION(root,H2);
    }

    void Print()
    {
        node* x;
        x=root;
        while(x!=NULL)
        {
            cout<<"Binomial Tree, B"<<x->degree<<endl;
            printLevelOrder(x);
            x=x->sibling;
        }
    }
};

int main()
{
    fstream in("input.txt");
    //freopen("output.txt", "w+", stdout);
    char ch;
    int m,n,i,j,k;

    Binomial_heap BH;
    while(!in.eof())
    {
        in>>ch;
        if(in.eof()) break;
        if(ch=='I')
        {
            in>>n;
            BH.insert(n);
        }
        else if(ch=='F')
        {
            BH.FIND_MIN();
        }
        else if(ch=='E' || ch=='e')
        {
            BH.extract_MIN();
        }
        else if(ch=='P')
        {
            cout<<"Printing Binomial Heap...\n";
            BH.Print();
        }
        else if(ch=='U')
        {
label:
            Binomial_heap bh;
            while(true)
            {
                string tem;
                in>>tem;
                char temp=tem[0];
                if(temp=='I')
                {
                    BH.Union(bh.getRoot());
                    in>>m;
                    BH.insert(m);
                }
                else if(temp=='E')
                {
                    BH.Union(bh.getRoot());
                    BH.extract_MIN();
                    break;
                }
                else if(temp=='F')
                {
                    BH.Union(bh.getRoot());
                    BH.FIND_MIN();
                    break;
                }
                else if(temp=='P')
                {
                    BH.Union(bh.getRoot());
                    cout<<"Printing Binomial Heap...\n";
                    BH.Print();
                    break;
                }
                else if(temp=='U')
                {
                    BH.Union(bh.getRoot());
                    goto label;
                    break;
                }
                else
                {
                    stringstream degree(tem);
                    degree>>n;
                    bh.insert(n);
                }
            }
        } //end union*/

    }//end while
}



