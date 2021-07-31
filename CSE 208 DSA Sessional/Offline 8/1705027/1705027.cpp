#include<bits/stdc++.h>
using namespace std;


class Node{
    public:
        string key;
        int value;
        Node* next;

        Node(){
            next=NULL;
        }
        Node(string k,int v){
            value=v;
            key=k;
            next=NULL;
        }
};


class RANDOM_WORD_GENERATOR{
    string word;
     vector<string> words;
     vector<string> searchedwords;
    int length;//string length

    string random_word()
    {
        int n;
        string s;
        char alphabets[52]={'a','b','c','d','e','f','g','h', 'i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
        for(int i=0;i<length;i++){
            n=rand()%52;
            s=s+alphabets[n];
        }
        return s;
    }

public:
    int order;//string order
    RANDOM_WORD_GENERATOR(int l=7){
        order=0;
        length=l;
    }

    Node* getKeyValue(){
        while(true){
        word=random_word();
        if(find(words.begin(),words.end(), word)==words.end()){
            words.push_back(word);
            order++;
            break;
            }
        }
       Node *newNode=new Node(word,order);
       return newNode;
    }

    string getWordforSearch(){
        int n;
        string w;
        while(true){
                n=rand()%order;
                w=words[n];
                if(find(searchedwords.begin(),searchedwords.end(), w)==searchedwords.end()){
                    searchedwords.push_back(w);
                    break;
            }
        }
        return w;
    }
    string getWord()
    {
        int n;
        n=rand()%order;
        string w=words[n];
        return w;
    }

};

int Hash1(string s, int N)
{
    int s_len=7;
    int B=347;
    int h=0;
    int power=1;
    for(int i=s_len-1;i>=0;i--){
        h = h+ (s[i]*power)%N;
        h=h%N;
        power=(power*B)%N;
    }
    return h;
}

int Hash2(string s, int N)
{
    int s_len=7;
    int h=5381;
    for(int i=s_len-1;i>=0;i--){
        h = ((h<<5)+h)+s[i];
        h=h%N;
    }
    return h;
}

int auxHash(string s, int N)
{
    int s_len=7;
    int h=0;
    for(int i=s_len-1;i>=0;i--){
        h=h+s[i]%N;
        h=h%N;
    }
    return h;
}


class ChainMethodHashing{
    Node **nodes;
    int length; //hash table length
    bool hash1;

public:
    int collission;
    int probe;
    int size;
    ChainMethodHashing(int n,bool h1=true){
        length=n;
        hash1=true;
        collission=0;
        probe=0;
        size=0;
        nodes = new Node*[length];
        for(int i=0;i<length;i++){
            nodes[i]=NULL;
        }
    }

    void INSERT(string k, int v){
        Node* t=new Node(k,v);
        int idx;
        if(hash1) idx=Hash1(k,length);
        else idx=Hash2(k,length);
        Node* p=NULL;
        p=nodes[idx];
        if(p==NULL){
            nodes[idx]=t;
            size++;
        }
        else{
            collission++;
            Node* prev=NULL;
            while(p!=NULL){
                prev=p;
                p=p->next;
            }
            prev->next=t;
            size++;
        }
    }

    Node* SEARCH(string k){
        int idx;
        int cnt=0;
        if(hash1) idx=Hash1(k,length);
        else idx=Hash2(k,length);
        if(nodes[idx]==NULL) return NULL;
        Node* p=nodes[idx];
        Node* result=NULL;
        while(p!=NULL){
            if(p->key==k){
                    result=p;
                    probe+=cnt;
                    break;
            }
            cnt++;
            p=p->next;
        }

        return result;
    }

    Node* DELETE(string k){
        int idx;
        if(hash1) idx=Hash1(k,length);
        else idx=Hash2(k,length);
        if(nodes[idx]==NULL) return NULL;
        Node* prev=NULL;
        Node* p=NULL;
        Node* t=NULL;
        p=nodes[idx];
        while(p!=NULL){
            if(p->key==k){
                t=p;
                if(prev!=NULL) prev->next=p->next;
                else nodes[idx]=p->next;
                size--;
                break;
            }
            prev=p;
            p=p->next;
        }
        return t;
    }

};


class DoubleHashing
{
    Node **nodes;
    bool hash1;
    int length;//hash table size

    int Iterate_doubleHashing(string k,int i)
    {
        int hv,auxv;
        if(hash1) hv=Hash1(k,length);
        else hv=Hash2(k,length);
        auxv=auxHash(k,length);
        int idx = (hv + ((i * auxv)%length))%length;
        return idx;
    }

public:
    int collission;
    int probe;

    DoubleHashing(int n,bool h1=true){
        length=n;
        hash1=h1;
        collission=0;
        probe=0;
        nodes=new Node*[length];
        for(int i=0;i<length;i++)
            nodes[i]=NULL;
    }


    void INSERT(string k,int v)
    {
        int idx;
        int cnt=0;
        bool inserted=false;
        idx=Iterate_doubleHashing(k,0);
        if(nodes[idx]==NULL){
            Node *t=new Node(k,v);
            nodes[idx]=t;
            inserted=true;
            return;
        }
        for(int i=1;i<length;i++){
            idx=Iterate_doubleHashing(k,i);
            cnt++;
            //cout<<"idx: "<<idx<<endl;
            if(nodes[idx]==NULL){
                 //cout<<"**********inserting ********    "<<idx<<endl;
                Node *t=new Node(k,v);
                nodes[idx]=t;
                inserted=true;
                collission+=cnt;
                break;
            }
        }
        //if(!inserted) cout<<"Error! Can't Insert into Hash table(double hashing) \t key: "<<k<<endl;
    }

    Node* SEARCH(string k){
        Node* result=NULL;
        int idx;
        int cnt=0;
        for(int i=0;i<length;i++){
            idx=Iterate_doubleHashing(k,i);

            if(nodes[idx]==NULL) {
                result=NULL;
                break;
            }
            if(nodes[idx]->key==k){
                 probe+=cnt;
                result=nodes[idx];
                break;
            }
            cnt++;
        }
        return result;
    }

    Node* DELETE(string k)
    {
        Node* result=NULL;
        int idx;
        for(int i=0;i<length;i++){
            idx=Iterate_doubleHashing(k,i);
            if(nodes[idx]==NULL) {
                result=NULL;
                break;
            }
            if(nodes[idx]->key==k){
                result=nodes[idx];
                nodes[idx]=NULL;
                break;
            }
        }
        return result;
    }

};

class CustomProbingHashing
{
    Node **nodes;
    bool hash1;
    int length;//hash table size
    int c1,c2;

    int Iterate_customProbing(string k,int i)
    {
        int hv,auxv;
        if(hash1) hv=Hash1(k,length);
        else hv=Hash2(k,length);
        auxv=auxHash(k,length);
        int idx = (hv + c1*i*auxv + c2*i*i)%length;
        return idx;
    }

public:
    int collission;
    int probe;

    CustomProbingHashing(int n,bool h1=true){
        length=n;
        hash1=h1;
        collission=0;
        probe=0;
        c1=3;
        c2=7;
        nodes=new Node*[length];
        for(int i=0;i<length;i++)
            nodes[i]=NULL;
    }


    void INSERT(string k,int v)
    {
        int idx;
        int cnt=0;
        bool inserted=false;
        idx=Iterate_customProbing(k,0);
        if(nodes[idx]==NULL){
            Node *t=new Node(k,v);
            nodes[idx]=t;
            inserted=true;
            return;
        }
        for(int i=1;i<length;i++){
            idx=Iterate_customProbing(k,i);
            cnt++;
            if(nodes[idx]==NULL){
                Node *t=new Node(k,v);
                nodes[idx]=t;
                inserted=true;
                collission+=cnt;
                break;
            }
        }
        //if(!inserted) cout<<"Error! Can't Insert into Hash table(Custom Probing) \t key: "<<k<<endl;
    }

    Node* SEARCH(string k){
        Node* result=NULL;
        int idx;
        int cnt=0;
        for(int i=0;i<length;i++){
            idx=Iterate_customProbing(k,i);

            if(nodes[idx]==NULL) {
                result=NULL;
                break;
            }
            if(nodes[idx]->key==k){
                 probe+=cnt;
                result=nodes[idx];
                break;
            }
            cnt++;
        }
        return result;
    }

    Node* DELETE(string k)
    {
        Node* result=NULL;
        int idx;
        for(int i=0;i<length;i++){
            idx=Iterate_customProbing(k,i);
            if(nodes[idx]==NULL) {
                result=NULL;
                break;
            }
            if(nodes[idx]->key==k){
                result=nodes[idx];
                nodes[idx]=NULL;
                break;
            }
        }
        return result;
    }

};



int main()
{

    srand(time(NULL));
    int i,j,k;
    int n,choice,value=0;
    string s;
    cout<<"Enter length of hash table: ";
    cin>>n;

    RANDOM_WORD_GENERATOR rwg;
    ChainMethodHashing cmh(n);
    DoubleHashing dh(n);
    CustomProbingHashing cph(n);
    ChainMethodHashing cmh2(n,false);
    DoubleHashing dh2(n,false);
    CustomProbingHashing cph2(n,false);


    while(true){
        cout<<"Enter Your Choice:\n";
        cout<<"1:INSERT\n";
        cout<<"2:SEARCH\n";
        cout<<"3:DELETE\n";
        cout<<"4:REPORT GENERATE\n";
        cin>>choice;

        if(choice==1){
            Node *t = rwg.getKeyValue();
            cout<<"Inserting:\t"<<t->key<<endl;
            cmh.INSERT(t->key,t->value);
            dh.INSERT(t->key,t->value);
            cph.INSERT(t->key,t->value);
            cmh2.INSERT(t->key,t->value);
            dh2.INSERT(t->key,t->value);
            cph2.INSERT(t->key,t->value);
        }

        else if(choice==2){
            if(rwg.order==0 || cmh.size==0){
                cout<<"hash table is empty"<<endl;
                continue;
            }
            s=rwg.getWord();
            cout<<"Searching :\t "<<s<<endl;
            Node* t1=cmh.SEARCH(s);
            Node* t2=cmh2.SEARCH(s);
            Node* t3=dh.SEARCH(s);
            Node* t4=dh2.SEARCH(s);
            Node* t5=cph.SEARCH(s);
            Node* t6=cph2.SEARCH(s);
            if(t1!=NULL) cout<<"found it in Chaining Method(hash1) value: "<<t1->value<<endl;
            else cout<<"Not found in Chaining Method(hash1)\n";
            if(t2!=NULL) cout<<"found it in Chaining Method(hash2) value: "<<t2->value<<endl;
            else cout<<"Not found in Chaining Method(hash2)\n";
            if(t3!=NULL) cout<<"found it in Double Hashing Method(hash1) value: "<<t3->value<<endl;
            else cout<<"Not found in Double Hashing Method(hash1)\n";
            if(t4!=NULL) cout<<"found it in Double Hashing Method(hash2) value: "<<t4->value<<endl;
            else cout<<"Not found in Double Hashing Method(hash2)\n";
            if(t5!=NULL) cout<<"found it in Custom Probing Method(hash1) value: "<<t5->value<<endl;
            else cout<<"Not found in Custom Probing Method(hash1)\n";
            if(t6!=NULL) cout<<"found it in Custom Probing Method(hash2) value: "<<t6->value<<endl;
            else cout<<"Not found in Custom Probing Method(hash2)\n";

        }

        else if(choice==3){
             if(rwg.order==0 || cmh.size==0){
                cout<<"hash table is empty"<<endl;
                continue;
            }
            s=rwg.getWord();
            cout<<"trying to delete value:\t"<<s<<endl;
            Node* t1=cmh.DELETE(s);
            Node* t2=cmh2.DELETE(s);
            Node* t3=dh.DELETE(s);
            Node* t4=dh2.DELETE(s);
            Node* t5=cph.DELETE(s);
            Node* t6=cph2.DELETE(s);
            if(t1!=NULL) cout<<"found it & Delete it from Chaining Method(hash1)\n";
            else cout<<"Not found in Chaining Method(hash1)\n";
            if(t2!=NULL) cout<<"found it & Delete it from Chaining Method(hash2)\n";
            else cout<<"Not found in Chaining Method(hash2)\n";
            if(t3!=NULL) cout<<"found it & Delete it from Double Hashing Method(hash1)\n";
            else cout<<"Not found in Double Hashing Method(hash1)\n";
            if(t4!=NULL) cout<<"found it & Delete it from Double Hashing Method(hash2)\n";
            else cout<<"Not found in Double Hashing Method(hash2)\n";
            if(t5!=NULL) cout<<"found it & Delete it from Custom Probing Method(hash1)\n";
            else cout<<"Not found in Custom Probing Method(hash1)\n";
            if(t6!=NULL) cout<<"found it & Delete it from Custom Probing Method(hash2)\n";
            else cout<<"Not found in Custom Probing Method(hash2)\n";
        }

        else if(choice==4){
           //freopen("output.txt", "w+", stdout);
            n=10000;
            RANDOM_WORD_GENERATOR rwg;
            ChainMethodHashing cmh(n);
            DoubleHashing dh(n);
            CustomProbingHashing cph(n);
            ChainMethodHashing cmh2(n,false);
            DoubleHashing dh2(n,false);
            CustomProbingHashing cph2(n,false);
            for(i=0;i<n; i++){
                    Node* t=rwg.getKeyValue();
                    //cout<<t->value<<"\t"<<t->key<<endl;
                    cmh.INSERT(t->key,t->value);
                    dh.INSERT(t->key,t->value);
                    cph.INSERT(t->key,t->value);
                    cmh2.INSERT(t->key,t->value);
                    dh2.INSERT(t->key,t->value);
                    cph2.INSERT(t->key,t->value);
                }
            //cout<<cmh.collission<<"\t"<<dh.collission<<"\t"<<cph.collission<<endl;
            //cout<<cmh2.collission<<"\t"<<dh2.collission<<"\t"<<cph2.collission<<endl;
            for(i=0;i<n/10;i++){
                 string sw=rwg.getWordforSearch();
                cmh.SEARCH(sw);
                cmh2.SEARCH(sw);
                dh.SEARCH(sw);
                dh2.SEARCH(sw);
                cph.SEARCH(sw);
                cph2.SEARCH(sw);
            }
            //cout<<cmh.probe/1000.0<<"\t"<<dh.probe/1000.0<<"\t"<<cph.probe/1000.0<<endl;
            //cout<<cmh2.probe/1000.0<<"\t"<<dh2.probe/1000.0<<"\t"<<cph2.probe/1000.0<<endl;

            cout<<"Collision Resolution method\t\t\t"<<"hash1\t\t\t\t\t"<<"hash2"<<endl;
            cout<<"\t\t\t\tNo. of Collision\tAvg. Probes\t"<<"No. of Collision\tAvg. probes"<<endl;
            cout<<"Chaining Method\t\t\t\t"<<cmh.collission<<"\t\t"<<cmh.probe/1000.0<<"\t\t\t"<<cmh2.collission<<"\t\t"<<cmh2.probe/1000.0<<endl;
            cout<<"Double hashing\t\t\t\t"<<dh.collission<<"\t\t"<<dh.probe/1000.0<<"\t\t\t"<<dh2.collission<<"\t\t"<<dh2.probe/1000.0<<endl;
            cout<<"Custom Probing\t\t\t\t"<<cph.collission<<"\t\t"<<cph.probe/1000.0<<"\t\t\t"<<cph2.collission<<"\t\t"<<cph2.probe/1000.0<<endl;
            break;
            }
          else{
            break;
          }
    }
    return 0;
}
