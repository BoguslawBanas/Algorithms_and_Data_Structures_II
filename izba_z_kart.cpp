#include <iostream>
#include <vector>
#include <climits>

using std::cin;
using std::cout;
using std::vector;

struct Node{
    long int id;
    Node *left_son;
    Node *right_son;
    //konstruktory
    Node(){}

    Node(long int id){
        this->id=id;
        left_son=NULL;
        right_son=NULL;
    }

    //wstawianie do drzewa
    void insert_node(Node *node){
        if(node->id<this->id){
            if(left_son==NULL){
                left_son=node;
                return;
            }
            left_son->insert_node(node);
        }
        else{
            if(right_son==NULL){
                right_son=node;
                return;
            }
            right_son->insert_node(node);
        }
    }
};


//przycinanie drzewa
Node* trimming_tree(Node *root, const long &min, const long &max){
    if(root==NULL) return root;
         
    root->left_son=trimming_tree(root->left_son, min, max);
    root->right_son=trimming_tree(root->right_son, min, max);

    if(root->id<min && root->left_son==NULL){
        return root->right_son;
    }
    if(root->id>max && root->right_son==NULL){
        return root->left_son;
    }
    return root;
}

void insert_node_to_vector(Node *root, vector<long>&v){
    if(root->left_son!=NULL) insert_node_to_vector(root->left_son,v);
    v.push_back(root->id);
    if(root->right_son!=NULL) insert_node_to_vector(root->right_son,v);
}

//znajdowanie pary z jak najmniejszą różnicą
void find_pair(vector<long>&v, const long &result){
    long size=v.size();
    if(size==0 || size==1){
        cout<<"NIE ZNALEZIONO";
        return;
    }
    long i_c=-1,j_c=-1,diff=INT_MAX;
    for(long i=0;i<size-1;++i){
        long j=i+1;
        while(j<size && v[i]+v[j]<=result){
            if(v[i]+v[j]==result){
                if(v[j]-v[i]<diff){
                    i_c=i;
                    j_c=j;
                    diff=v[j]-v[i];
                }
            }
            ++j;
        }
    }
    if(i_c==-1) cout<<"NIE ZNALEZIONO";
    else cout<<v[i_c]<<' '<<v[j_c]; 
    return;
}

int main(){
    long n,k,a,b;
    cin>>n;
    if(n==0) return 0;
    cin>>k;
    Node *root=new Node(k); 
    for(long i=0;i<n-1;++i){
        cin>>k;
        root->insert_node(new Node(k));
    }
    cin>>a>>b>>k;
    root=trimming_tree(root,a,b);
    vector<long>v;
    insert_node_to_vector(root,v);
    find_pair(v,k);
    return 0;
}