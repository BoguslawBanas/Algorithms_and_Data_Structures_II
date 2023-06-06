#include <iostream>
#include <cmath>

using namespace std;

//given function
double butelka(const double &cm) {
	return 10 - (cm-2) * (cm-2);
}

double calc_integral(const double &v){
    const double epsilon=v/50;
    double step=0.0;
    double result=0.0;
    for(int i=0;i<50;++i){
        result+=M_PI*(butelka(step)*butelka(step)+butelka(step+epsilon)*butelka(step+epsilon))*epsilon*0.5;
        step+=epsilon;
    }
    return result;
}

int main(){
    short x,y,z,n;
    double p;
    cin>>x>>y>>z>>p>>n;
    int max_capacity=x*y*z;
    double initial_value=max_capacity*p;
    double c;
    for(int i=1;i<=n;++i){
        cin>>c;
        initial_value+=calc_integral(c);
        if(initial_value>max_capacity){
            cout<<i<<'\n';
            return 0;
        }
    }
    cout<<"NIE"<<'\n';
    return 0;
}