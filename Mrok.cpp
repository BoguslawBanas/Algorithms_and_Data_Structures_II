#include <iostream>
#include <algorithm>
#include <list>
#include <queue>
#include <vector>
#include <climits>
#include <cmath>

using std::cin;
using std::cout;
using std::list;
using std::priority_queue;
using std::vector;

//struktura opisująca położenie izotopu cezu 137
struct Point{
    int x;
    int y;
    int id; //id jako połozenie początkowe w tablicy przy sort nam się przyda
    int length; //odległość od startu
    bool is_visited; //flaga która mówi nam czy odwiedziliśmy już nasz punkt wcześniej

    //konstruktory
    Point(){}
    
    Point(int x, int y, int id){
        this->x=x;
        this->y=y;
        this->id=id;
        this->length=INT_MAX;
        this->is_visited=false;
    }

    //metoda, która służy nam do oblicznia odległości między punktami
    inline int find_min(Point p1){
        return abs(this->x-p1.x)<abs(this->y-p1.y) ? abs(this->x-p1.x): abs(this->y-p1.y);
    }
};

//Comparator do kolejki priorytetowej
struct Cmp{
    inline bool operator()(const Point *p1, const Point *p2){
        return p1->length>p2->length;
    }
};

void create_graph(Point *arr, int size, list<int>*adjacency_list){
    std::sort(arr,arr+size,[](const Point &p1, const Point &p2){return p1.x<p2.x;}); //sortuje po x

    //do danej listy sąsiedztwa wrzucam wartości id, które znajdują się pomiędzy wartością
    //np. 0 3 4 1 2 to do adjacency_list[1] wrzucę 4 i 2, wyjątek stanowi wartości pierwsza i ostatnia
    adjacency_list[arr[0].id].push_back(arr[1].id); 
    for(int i=1;i<size-1;++i){
        adjacency_list[arr[i].id].push_back(arr[i-1].id);
        adjacency_list[arr[i].id].push_back(arr[i+1].id);
    }
    adjacency_list[arr[size-1].id].push_back(arr[size-2].id);

    //analogicznie po posortowaniu z y
    std::sort(arr,arr+size,[](const Point &p1, const Point &p2){return p1.y<p2.y;});
    adjacency_list[arr[0].id].push_back(arr[1].id);
    for(int i=1;i<size-1;++i){
        adjacency_list[arr[i].id].push_back(arr[i-1].id);
        adjacency_list[arr[i].id].push_back(arr[i+1].id);
    }
    adjacency_list[arr[size-1].id].push_back(arr[size-2].id);

    //przywracam początkowe położenie tablicy dzięki polu 'id'
    std::sort(arr,arr+size,[](const Point &p1, const Point &p2){return p1.id<p2.id;});
    for(int i=0;i<size;++i){
        //ponieważ w pojedynczej liście może znaleźć się max. 4 elementy to sortowanie listy odbywa się w praktyce w O(1)
        adjacency_list[i].sort(); //sort jest nam potrzebny do wywołania metody unique
        adjacency_list[i].unique(); //odrzucam duplikaty
    }
}

//główna funkcja programu
int dijkstra_algorithm(int begin, int end, Point *arr, int size){
    //część 1 - budowanie grafu 
    
    list<int> *adjacency_list=new list<int>[size]; //lista sąsiedztwa
    create_graph(arr,size,adjacency_list);

    //część 2 - właściwy algorytm Dijkstry

    priority_queue<Point*, vector<Point*>, Cmp>pq; //kolejka priorytetowa z customowym komparatorem trzymająca wskaźniki 
    Point *p=nullptr;
    //START
    arr[begin].length=0; 
    arr[begin].is_visited=true;
    pq.push(&arr[begin]);
    //wykonuje algorytm do momentu odwiedzenia docelowego punktu (korzystam z cechy zachłanności alg. Dijkstry)
    while (arr[end].is_visited==false)
    {
        //pobieram górę kolejki
        p=pq.top();
        //dla wszystkich elementów w danej liście sprawdzam czy dany el. jest nieodwiedzony 
        //i czy nowa odległość jest mniejsza od obecnej...
        for(auto i=adjacency_list[p->id].begin();i!=adjacency_list[p->id].end();++i){
            if(arr[*i].is_visited==false && arr[*i].length>p->length+p->find_min(arr[*i])){
                //...jeżeli tak to ustaw nową odległość i wrzuć do pq
                arr[*i].length=p->length+p->find_min(arr[*i]);
                pq.push(&arr[*i]);
            }
        }
        p->is_visited=true;
        pq.pop(); 
    }
    delete[] adjacency_list;
    return arr[end].length;
}

int main(){
    int n;
    cin>>n;
    Point *arr=new Point[n];
    int x,y;
    for(int i=0;i<n;++i){
        cin>>x>>y;
        arr[i]=Point(x,y,i);
    }
    int begin,end;
    cin>>begin>>end;
    cout<<dijkstra_algorithm(begin,end,arr,n);
    return 0;
}