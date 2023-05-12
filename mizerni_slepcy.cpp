#include <iostream>

using std::cin;
using std::cout;
using std::string;

class List_Node{
    public:
    string value;
    List_Node *previous;
    List_Node *next;

    List_Node(){}

    List_Node(string value){
        this->value=value;
        previous=NULL;
        next=NULL;
    }
};


class Red_Black_Node{
    public:
    char color;
    string key;
    List_Node *value;
    Red_Black_Node *left_b;
    Red_Black_Node *right_b;
    Red_Black_Node *father;

    Red_Black_Node(){}

    Red_Black_Node(string s, List_Node *value){
        this->key=s;
        this->value=value;
        color='r';
        left_b=NULL;
        right_b=NULL;
        father=NULL;
    }

    inline bool is_root(){
        return father==NULL;
    }

    Red_Black_Node *find_root(){
        Red_Black_Node *ptr=this;
        while(ptr->father!=NULL){
            ptr=ptr->father;
        }
        return ptr;
    }

    Red_Black_Node *find_uncle(){
        Red_Black_Node *grandfather=this->father->father;
        if(this->key<grandfather->key) return grandfather->right_b;
        return grandfather->left_b;
    }

    void r_case1(){
        this->color='b';
        return;
    }

    void r_case2(){
        Red_Black_Node *uncle=this->find_uncle();
        uncle->color='b';
        this->father->color='b';
        this->father->father->color='r';
        this->father->father->rotation_cases();
        return;
    }

    void r_case3(){
        //x jest prawym bratem i wujek jest czarny (trojkat)
        Red_Black_Node *father=this->father;
        Red_Black_Node *grandparent=this->father->father;
        grandparent->left_b=this;
        this->father=grandparent;
        father->right_b=this->left_b;
        if(father->right_b!=NULL) father->right_b->father=father;
        this->left_b=father;
        father->father=this;
        this->r_case5();
        return;
    }

    void r_case4(){
        //x jest lewym bratem i wujek jest czarny (trojkat)
        Red_Black_Node *father=this->father;
        Red_Black_Node *grandparent=this->father->father;
        grandparent->right_b=this;
        this->father=grandparent;
        father->left_b=this->right_b;
        if(father->left_b!=NULL) father->left_b->father=father;
        this->right_b=father;
        father->father=this;
        this->r_case6();
        return;
    }

    void r_case5(){
        //x jest lewym bratem i wujek jest czarny (linia)
        Red_Black_Node *father=this->father;
        Red_Black_Node *grandparent=this->father->father;
        father->left_b=this->right_b;
        if(father->left_b!=NULL) father->left_b->father=father; 
        father->father=this;
        this->right_b=father;
        if(grandparent==NULL){
            this->father=NULL;
        }
        else if(this->key<grandparent->key){
            grandparent->left_b=this;
            this->father=grandparent;
        }
        else{
            grandparent->right_b=this;
            this->father=grandparent;
        }
        this->color='b';
        this->right_b->color='r';
        return;
    }

    void r_case6(){
        //x jest prawym bratem i wujek jest czarny (linia)
        Red_Black_Node *father=this->father;
        Red_Black_Node *grandparent=this->father->father;
        father->right_b=this->left_b;
        if(father->right_b!=NULL) father->right_b->father=father; 
        father->father=this;
        this->left_b=father;
        if(grandparent==NULL){
            this->father=NULL;
        }
        else if(this->key<grandparent->key){
            grandparent->left_b=this;
            this->father=grandparent;
        }
        else{
            grandparent->right_b=this;
            this->father=grandparent;
        }
        this->color='b';
        this->left_b->color='r';
        return;
    }

    // rotacje
    void rotation_cases(){
        if(this==NULL) return;

        if(this->is_root()){
            this->r_case1();
            return;
        }

        if(this->father->is_root()) return;
        Red_Black_Node *uncle=this->find_uncle();

        if(uncle!=NULL && uncle->color=='r'){
            this->r_case2();
        }

        else if(uncle==NULL || uncle->color=='b'){
            if(this->key>=this->father->key && this->father->key<this->father->father->key){
                this->r_case3();
            }
            else if(this->key<this->father->key && this->father->key>=this->father->father->key){
                this->r_case4();
            }
            else if(this->key<this->father->key && this->father->key<this->father->father->key){
                this->father->r_case5();
            }
            else if(this->key>=this->father->key && this->father->key>=this->father->father->key){
                this->father->r_case6();
            }
        }
        return;
    }

    Red_Black_Node *search(string s){
        if(this->key==s || this==NULL) return this;
        if(this->key>s){
            return this->left_b->search(s);
        }
        return this->right_b->search(s);
    }

    void insert(Red_Black_Node *to_insert){
        if(this->key>to_insert->key){
            if(this->left_b==NULL){
                this->left_b=to_insert;
                to_insert->father=this;
                to_insert->rotation_cases();
                return;
            }
            this->left_b->insert(to_insert);
        }
        else{
            if(this->right_b==NULL){
                this->right_b=to_insert;
                to_insert->father=this;
                to_insert->rotation_cases();
                return;
            }
            this->right_b->insert(to_insert);
        }
        return;
    }
};

class List{
    public:
    int size;
    List_Node *head;
    List_Node *tail;

    List(){
        size=0;
        head=new List_Node("!!!!");
        tail=new List_Node("!!!!!");
    }

    inline bool is_empty(){
        return size==0;
    }

    void push_back(List_Node *l){
        if(is_empty()){
            head->next=l;
            tail->previous=l;
            l->previous=head;
            l->next=tail;
        }
        else{
            List_Node *ptr=tail->previous;
            tail->previous=l;
            l->next=tail;
            ptr->next=l;
            l->previous=ptr;
        }
        ++size;
        return;
    }

    void my_swap(List_Node *l1, List_Node *l2){
        string tmp=l1->value;
        l1->value=l2->value;
        l2->value=tmp;
        return;
    }

    void move(int amount_of_moves, List_Node *l1){
        List_Node *ptr=l1;
        if(amount_of_moves<0){
            for(int i=0;i>amount_of_moves;--i){
                ptr=ptr->next;
            }
            List_Node *ptr1=l1->previous;
            List_Node *ptr2=ptr->next;
            ptr1->next=l1->next;
            l1->next->previous=ptr1;
            ptr->next=l1;
            l1->previous=ptr;
            ptr2->previous=l1;
            l1->next=ptr2;
        }
        else{
            for(int i=0;i<amount_of_moves;++i){
                ptr=ptr->previous;
            }
            List_Node *ptr1=l1->next;
            List_Node *ptr2=ptr->previous;
            ptr1->previous=l1->previous;
            l1->previous->next=ptr1;
            ptr2->next=l1;
            ptr->previous=l1;
            l1->previous=ptr2;
            l1->next=ptr;
        }
        return;
    }

    void print_list(){
        List_Node *ptr=head->next;
        for(int i=0;i<size;++i){
            cout<<ptr->value<<'\n';
            ptr=ptr->next;
        }
        return;
    }
};

void operations(List *list, Red_Black_Node *root){
    char op;
    cin>>op;
    switch (op){
        case('a'):{
            string s;
            cin>>s;
            List_Node *ptr=new List_Node(s);
            list->push_back(ptr);
            root->insert(new Red_Black_Node(s, ptr));
        } break;

        case('r'):{
            string s1,s2;
            cin>>s1>>s2;
            Red_Black_Node *ptr1=root->search(s1);
            Red_Black_Node *ptr2=root->search(s2);
            list->my_swap(ptr1->value, ptr2->value);
            List_Node *tmp=ptr1->value;
            ptr1->value=ptr2->value;
            ptr2->value=tmp;
        } break;

        case('m'):{
            string s;
            int amuont_of_moves;
            cin>>s>>amuont_of_moves;
            if(amuont_of_moves==0) return;
            list->move(amuont_of_moves, root->search(s)->value);
        } break;
    }
    return;
}

int main(){
    int n,k;
    cin>>n;
    string str;
    List *l=new List();
    Red_Black_Node *root=NULL;
    List_Node *list_node=NULL;
    cin>>str;
    list_node=new List_Node(str);
    l->push_back(list_node);
    root=new Red_Black_Node(str,list_node);
    root->color='b';
    for(int i=1;i<n;++i){
        cin>>str;
        list_node=new List_Node(str);
        l->push_back(list_node);
        Red_Black_Node *tree_node=new Red_Black_Node(str,list_node);
        root->insert(tree_node);
        root=root->find_root();
    }
    cin>>k;
    for(int i=0;i<k;++i){
        operations(l,root);
        root=root->find_root();
    }
    l->print_list();
    return 0;
}