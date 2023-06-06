#include <iostream>
#include <list>
#include <stack>
#include <cmath>
#include <algorithm>

using std::stack;
using std::list;
using std::sort;
using std::swap;

class Point{
    public:
    short x;
    short y;

    Point(){
        this->x=0;
        this->y=0;
    }

    Point(short x, short y){
        this->x=x;
        this->y=y;
    }

    double length(const Point *p1){
        return (this->x-p1->x)*(this->x-p1->x)+(this->y-p1->y)*(this->y-p1->y);
    }
};

Point zero_point;

double find_length(stack<Point*>&s){
    double result=0.0;
    Point *first_point=s.top();
    Point *p=s.top();
    s.pop();
    while(!s.empty()){
        result+=sqrt(p->length(s.top()));
        p=s.top();
        s.pop();
    }
    result+=sqrt(first_point->length(p));
    return result;
}

int calc_det(const Point &p1, const Point &p2, const Point &p3){
    return (p2.x*p3.y)+(p3.x*p1.y)+(p1.x*p2.y)-(p1.y*p2.x)-(p2.y*p3.x)-(p3.y*p1.x);
}

double calc_length_of_hull(stack<Point>&s){
    double result=0.0;
    Point p1=zero_point;
    Point p2=s.top();
    s.pop();
    while(!s.empty()){
        result+=sqrt(p1.length(&p2));
        p1=p2;
        p2=s.top();
        s.pop();
    }
    result+=sqrt(p1.length(&p2));
    return result;
}

Point next_to_top(stack<Point>&s){
    Point tmp=s.top();
    s.pop();
    Point result=s.top();
    s.push(tmp);
    return result;
}

double grahams_algorithm(list<Point>&my_list){
    stack<Point>s;
    for(int i=0;i<3;++i){
        s.push(my_list.front());
        my_list.pop_front();
    }
    while(!my_list.empty()){
        if(calc_det(next_to_top(s), s.top(), my_list.front())<=0){
            s.pop();
        }
        else{
            s.push(my_list.front());
            my_list.pop_front();
        }
    }
    double result=calc_length_of_hull(s);
    return result;
}

void find_left_bottom_point(list<Point>&my_list, const int &size){
    auto min=my_list.begin();
    for(auto it=my_list.begin();it!=my_list.end();++it){
        if((min->y>it->y) || (min->y==it->y && min->x>it->x)){
            min=it;
        }
    }
    swap(*min,*my_list.begin());
    return;
}

void remove_collinear(list<Point>&my_list){
    auto it=my_list.begin();
    auto it2=++my_list.begin();
    do{
        int c=calc_det(zero_point,*it,*it2);
        if(c==0){
            it=my_list.erase(it);
        }
        else{
            ++it;
        }
        ++it2;
    }while(it2!=my_list.end());
    return;
}

void print_list(list<Point>&my_list){
    std::cout<<'\n';
    for(Point p : my_list){
        std::cout<<p.x<<' '<<p.y<<'\n';
    }
    std::cout<<'\n';
}

int main(){
    int n;
    scanf("%d", &n);
    list<Point>my_list;
    Point p;
    for(int i=0;i<n;++i){
        scanf("%hd", &p.x);
        scanf("%hd", &p.y);
        my_list.push_back(p);
    }
    find_left_bottom_point(my_list,n);
    zero_point=my_list.front();
    my_list.pop_front();
    my_list.sort([](const Point &p1, const Point &p2){
        int result=calc_det(zero_point,p1,p2);
        if(result==0){
            return zero_point.length(&p1)<zero_point.length(&p2);
        }
        return result>0 ? true : false;
    });
    
    print_list(my_list);

    remove_collinear(my_list);
    my_list.push_front(zero_point);

    print_list(my_list);

    printf("%.2f", grahams_algorithm(my_list));
    return 0;
}