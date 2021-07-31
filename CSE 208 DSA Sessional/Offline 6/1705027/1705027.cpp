#include<iostream>
#include<fstream>
#define RED 1
#define BLACK 2
using namespace std;

class RBT
{
    struct node
    {
        int data, color;
        node *left,*right,*parent;
    };

    node *root;

    node* Search(node *t,int x)
    {
        if(t==NULL) return NULL;
        if(x < t->data)
            return Search(t->left,x);
        if(x > t->data)
            return Search(t->right,x);
        return t;
    }

        node* RBTMin(node *t)
    {
        if(t==NULL) return NULL;
        else if(t->left!=NULL)
            return RBTMin(t->left);
        return t;
    }

    node* RBTMax(node *t)
    {
        if(t==NULL) return NULL;
        else if(t->right!=NULL)
            return RBTMax(t->right);
        return t;
    }

       node*  Left_Rotate(node *root, node *x){

        node *y=x->right;

        x->right=y->left;
        if(y->left!=NULL)
            y->left->parent=x;

        y->parent=x->parent;
        if(x->parent==NULL){
            root=y;

        }
        else if(x==x->parent->left)
            x->parent->left=y;
        else
            x->parent->right=y;

        y->left=x;
        x->parent=y;

        return root;
    }

    node* Right_Rotate(node *root, node *y){

        node *x=y->left;

        y->left=x->right;

        if(x->right!=NULL) x->right->parent=y;

        x->parent=y->parent;

        if(y->parent==NULL){
            root = x;

        }
        else if(y==y->parent->left)
            y->parent->left=x;
        else
            y->parent->right=x;

        x->right=y;
        y->parent=x;

        return root;
    }

    node* INSERT_FIXUP(node *root, int z){
        node *tz=Search(root,z);
        while(tz->parent!=NULL && tz->parent->color==RED){

            if(tz->parent==(tz->parent->parent->left)){

                node *y=tz->parent->parent->right;

                if(y!=NULL && y->color==RED){

                    tz->parent->color=BLACK;
                    y->color=BLACK;
                    tz->parent->parent->color=RED;
                    tz=tz->parent->parent;
                }

                else{

                    if(tz==tz->parent->right){

                        tz=tz->parent;
                        root=Left_Rotate(root,tz);
                    }

                    tz->parent->color=BLACK;
                    tz->parent->parent->color=RED;
                    root=Right_Rotate(root,tz->parent->parent);
                }

            }


            else{

                node *y=tz->parent->parent->left;
                    if(y!=NULL && y->color==RED){

                        tz->parent->color=BLACK;
                        y->color=BLACK;
                        tz->parent->parent->color=RED;
                        tz=tz->parent->parent;
                    }

                else{

                    if(tz==tz->parent->left){
                        tz=tz->parent;

                        root=Right_Rotate(root,tz);
                    }

                    if(tz->parent!=NULL) {
                            tz->parent->color=BLACK;
                            if(tz->parent->parent!=NULL){
                                tz->parent->parent->color=RED;
                                root=Left_Rotate(root,tz->parent->parent);
                            }
                    }
                }

            }

        }
        root->color=BLACK;
        return root;
    }

    node* Insert(int x,node *t)
    {
        if(t==NULL)
        {
            t=new node;
            t->data=x;
            t->color=RED;
            t->left=t->right=NULL;
            //t->left->parent=t->right->parent=t;
            t->parent=NULL;
        }
        else if(x < t->data){
            t->left=Insert(x,t->left);
            t->left->parent=t;
        }
        else if(x > t->data){
            t->right=Insert(x,t->right);
            t->right->parent=t;
        }
        return t;
    }



    node* Delete_Fixup(node *root,node *x, node *x_p,int d){
        while((x==NULL || x->color==BLACK) && x!=root){

                //x is left child
            if((x==NULL&&d==1) || (x!=NULL &&x==x->parent->left)){

                node *w=NULL;
                if(x!=NULL) w=x->parent->right;
                else w=x_p->right;
                //sibling is red

                if(w->color==RED){

                    w->color=BLACK;
                    if(x!=NULL){
                        x->parent->color=RED;
                        root=Left_Rotate(root,x->parent);

                        w=x->parent->right;
                    }
                    else{
                        x_p->color=RED;
                        root=Left_Rotate(root,x_p);

                        w=x_p->right;

                    }
                }

                if(w->left==NULL && w->right==NULL)
                    {

                        w->color=RED;
                        if(x!=NULL) x=x->parent;
                        else x=x_p;
                }
                else if(w->left!=NULL && w->right!=NULL && w->left->color==BLACK && w->right->color==BLACK){

                        w->color=RED;
                        if(x!=NULL) x=x->parent;
                        else x=x_p;
                }
                else{

                    if(w->right==NULL || w->right->color==BLACK){

                        w->left->color=BLACK;
                        w->color=RED;
                        root=Right_Rotate(root,w);
                        if(x!=NULL) w=x->parent->right;
                        else w=x_p->right;
                    }

                    if(x!=NULL){

                        w->color=x->parent->color;
                        x->parent->color=BLACK;
                        w->right->color=BLACK;
                        root=Left_Rotate(root,x->parent);
                    }
                    else{

                        w->color=x_p->color;
                        x_p->color=BLACK;
                        w->right->color=BLACK;
                        root=Left_Rotate(root,x_p);
                    }
                    x=root;
                }


            }

            else{
                node *w=NULL;
                if(x!=NULL) w=x->parent->left;
                else w=x_p->left;
                //sibling is red

                if(w!=NULL && w->color==RED){

                    w->color=BLACK;
                    if(x!=NULL){
                        x->parent->color=RED;
                        root=Right_Rotate(root,x->parent);
                        w=x->parent->left;
                    }
                    else{
                        x_p->color=RED;
                        root=Right_Rotate(root,x_p);
                        w=x_p->left;
                    }
                }

                if((w->left==NULL && w->right==NULL)||(w->left!=NULL && w->right!=NULL && w->left->color==BLACK && w->right->color==BLACK)){

                        w->color=RED;
                        if(x!=NULL) x=x->parent;
                        else x=x_p;
                }

                else{


                    if(w->left==NULL || w->left->color==BLACK){

                        w->right->color=BLACK;
                        w->color=RED;
                        root=Left_Rotate(root,w);
                        if(x!=NULL) w=x->parent->left;
                        else w=x_p->left;
                    }
                    if(x!=NULL){

                        w->color=x->parent->color;
                        x->parent->color=BLACK;
                        w->left->color=BLACK;
                        root=Right_Rotate(root,x->parent);
                    }
                    else{

                        w->color=x_p->color;
                        x_p->color=BLACK;
                        w->left->color=BLACK;

                        root=Right_Rotate(root,x_p);

                    }
                    x=root;
                }
            }

        }

       if(x!=NULL) x->color=BLACK;
       return root;

    }

    node* Delete(int z,node *root)
    {
        int L1R2;
        node *y=NULL;
        node *x=NULL;
        node *tz=Search(root,z);
        if(tz->left==NULL || tz->right==NULL){
            y=tz;
        }
        else{
            y=RBTMax(tz->left);
        }

        if(y->left!=NULL) x=y->left;
        else x=y->right;
        if(x!=NULL) x->parent=y->parent;
        if(y->parent==NULL)  root=x;
        else if(y==y->parent->left) {
                y->parent->left=x;
                L1R2=1;
        }
        else {
                y->parent->right=x;
                L1R2=2;
        }
        if(y!=tz)
            tz->data=y->data;

        if(y->color==BLACK){

            root=Delete_Fixup(root,x,y->parent,L1R2);

        }
        return root;

    }

    void Preorder(node *t)
    {
        if(t==NULL) return;
        cout<<t->data <<":";
        if(t->color==RED) cout<<"r";
        else cout<<"b";
        if(t->left!=NULL || t->right!=NULL) cout<<"(";
        Preorder(t->left);
        if(t->left!=NULL || t->right!=NULL) cout<<")(";
        Preorder(t->right);
        if(t->left!=NULL || t->right!=NULL) cout<<")";
    }



public:
    RBT()
    {
        root=NULL;
    }

    bool Search(int x)
    {
        node *tem = Search(root, x);
        if(tem==NULL) return false;
        return true;
    }

    void Insert(int x)
    {
        root = Insert(x, root);
        root = INSERT_FIXUP(root,x);
        //cout<<"root :"<<root->data<<endl;
    }

    void Delete(int x)
    {
        if(root==NULL)
        {
            //cout<<"RED BLACK Tree is empty"<<endl;
            return;
        }
        root = Delete(x, root);
        //if(root!=NULL)
       //cout<<"root :"<<root->data<<endl;
    }

    void PreOrder()
    {
        if(root!=NULL){
                //cout<<"Pre Order :"<<endl;
                Preorder(root);
                cout<<endl;
        }
        else
        {
            //cout<<"RED BLACK Tree is empty"<<endl;
        }
    }
};


int main()
{
    RBT t;
    char ch;
    int n,c;
    fstream in("input.txt");
    while(!in.eof()){

        in>>ch;
        in>>n;
        //cout<<ch<<" "<<n<<endl;
        if(ch=='I' || ch=='i'){
            //cout<<"inserting\n";
            t.Insert(n);
            t.PreOrder();
        }
        else if(ch=='D' ||ch=='d'){
            //cout<<"deleting\n";
            if(t.Search(n)) {
                    t.Delete(n);
                    t.PreOrder();
            }
            else{
                t.PreOrder();
                //cout<<"element is not in the tree\n";
            }
        }
        else if(ch=='F' || ch=='f'){
            //cout<<"searching\n";
            if(t.Search(n)){
                cout<<"True\n";
            }
            else
                cout<<"False\n";
        }
    }

}


