#include <iostream>
#include <list>
#include <queue>
#include <algorithm>
#include <set>
#include <map>
#include <climits>

using std::cin;
using std::cout;
using std::list;
using std::queue;
using std::set;
using std::map;

class Bipartite_Graph{
    public:
    int size;
    list<int>*adj_list;
    list<int>black_pawns;
    list<int>white_pawns;
    map<int, int>black_pawns_pairs;
    map<int, int>white_pawns_pairs;
    int *length;
    int nil;    

    Bipartite_Graph(const int &size){
        this->size=size;
        adj_list=new list<int>[size*size];
        length=new int[size*size+1];
        nil=size*size;
    }

    void find_black_pawns(){
        if(!(size%2)){ 
            for(int i=0;i<size;++i){
                for(int j=0;j<size;++j){
                    if(!(i%2)){
                        if(!(j%2)){
                            black_pawns.push_back(i*size+j);
                            black_pawns_pairs.insert({i*size+j,nil});
                        }
                        else{
                            white_pawns.push_back(i*size+j);
                            white_pawns_pairs.insert({i*size+j,nil});
                        }
                    }
                    else{
                        if(j%2){
                            black_pawns.push_back(i*size+j);
                            black_pawns_pairs.insert({i*size+j,nil});
                        }
                        else{
                            white_pawns.push_back(i*size+j);
                            white_pawns_pairs.insert({i*size+j,nil});
                        }
                    }
                }
            }
        }
        else{
            for(int i=0;i<size*size;++i){
                if(!(i%2)){
                    black_pawns.push_back(i);
                    black_pawns_pairs.insert({i,nil});
                }
                else{
                    white_pawns.push_back(i);
                    white_pawns_pairs.insert({i,nil});
                }
            }
        }
    }

    void add_edge(short **matrix, const int &value){
        short x=value/size, y=value%size;
        switch(matrix[x][y]){
            case 0: return;
            case 1:{
            if(y+3<size && matrix[x][y+3]!=0){
                adj_list[value].push_back(value+3);
                adj_list[value+3].push_back(value);
            }
            if(x-1>=0 && y+2<size && matrix[x-1][y+2]!=0){
                adj_list[value].push_back((x-1)*size+y+2);
                adj_list[(x-1)*size+y+2].push_back(value);
            }
            if(x+1<size && y+2<size && matrix[x+1][y+2]!=0){
                adj_list[value].push_back((x+1)*size+y+2);
                adj_list[(x+1)*size+y+2].push_back(value);
            }
            }break;
            case 2:{
            if(y+1<size && matrix[x][y+1]!=0){
                adj_list[value].push_back(value+1);
                adj_list[value+1].push_back(value);
            }
            if(x-1>=0 && matrix[x-1][y]!=0){
                adj_list[value].push_back(value-size);
                adj_list[value-size].push_back(value);
            }
            if(x+1<size && matrix[x+1][y]!=0){
                adj_list[value].push_back(value+size);
                adj_list[value+size].push_back(value);
            }
            }break;
            case 3:{
            if(y+1<size && matrix[x][y+1]!=0){
                adj_list[value].push_back(value+1);
                adj_list[value+1].push_back(value);
            }
            if(x-1>=0 && y+2<size && matrix[x-1][y+2]!=0){
                adj_list[value].push_back((x-1)*size+y+2);
                adj_list[(x-1)*size+y+2].push_back(value);
            }
            if(x+1<size && y+2<size && matrix[x+1][y+2]!=0){
                adj_list[value].push_back((x+1)*size+y+2);
                adj_list[(x+1)*size+y+2].push_back(value);
                }
            }break;
        }
        return;
    }

    bool bfs(){
        queue<int>q;
        for(auto it=black_pawns.begin();it!=black_pawns.end();++it){
            if(black_pawns_pairs[*it]==nil){
                length[*it]=0;
                q.push(*it);
            }
            else{
                length[*it]=INT_MAX;
            }
        }
        length[nil]=INT_MAX;
        while(!q.empty()){
            int front=q.front();
            q.pop();
            if(length[front]<length[nil]){
                for(auto it=adj_list[front].begin();it!=adj_list[front].end();++it){
                    if(length[white_pawns_pairs[*it]]==INT_MAX){
                        length[white_pawns_pairs[*it]]=length[front]+1;
                        q.push(white_pawns_pairs[*it]);
                    }
                }
            }
        }
        return length[nil]!=INT_MAX;
    }

    bool dfs(const int &vertex){
        if(vertex!=nil){
            for(auto it=adj_list[vertex].begin();it!=adj_list[vertex].end();++it){
                if(length[white_pawns_pairs[*it]]==length[vertex]+1){
                    if(dfs(white_pawns_pairs[*it])){
                        white_pawns_pairs[*it]=vertex;
                        black_pawns_pairs[vertex]=*it;
                        return true;
                    }
                }
            }
            length[vertex]=INT_MAX;
            return false;
        }
        return true;
    }

    int hopcroft_karp(){
        int counter=0;
        while(bfs()){
            for(int u : black_pawns){
                if(black_pawns_pairs[u]==nil && dfs(u)) ++counter;
            }
        }
        return counter;
    }
};

int main(){
    int n;
    cin>>n;
    short **chessboard=new short*[n];
    for(int i=0;i<n;++i){
        chessboard[i]=new short[n];
        for(int j=0;j<n;++j){
            cin>>chessboard[i][j];
        }
    }
    Bipartite_Graph *graph=new Bipartite_Graph(n);
    graph->find_black_pawns();
    for(int u : graph->black_pawns){
        graph->add_edge(chessboard, u);
    }
    cout<<(n*n)-graph->hopcroft_karp();
    return 0;
}