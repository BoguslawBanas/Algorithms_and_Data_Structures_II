#include <iostream>
#include <cstdio>

using std::cin;
using std::cout;
using std::string;
using std::getline;

inline char convert_char(const char &c){
    if(c==32) return ' ';
    else if(c>47 && c<58) return '0';
    else if(c>64 && c<91) return 'A';
    else if(c>96 && c<123) return 'a';
    else if(c==33 || c==44 || c==45 || c==46 || c==58 || c==59 || c==63) return '.'; 
    return 'L';
}

void create_prefix_sufix_arr(int *prefix_sufix, const int &size, const string &pttr){
    prefix_sufix[0]=0;
    int l=0;
    for(int i=1;i<size;++i){
        if(pttr[i]==pttr[l]){
            ++l;
            prefix_sufix[i]=l;
        }
        else{
            while(l>0){
                if(pttr[i]==pttr[l]){
                    ++l;
                    prefix_sufix[i]=l;
                    break;
                }
                l=prefix_sufix[l-1];
            }
            if(l==0){
                prefix_sufix[i]=0;
            }
        }
    }
}

int main(){
    string pattern;
    getline(cin, pattern);
    int pattern_length=pattern.length();
    int *arr=new int[pattern_length];
    create_prefix_sufix_arr(arr,pattern_length,pattern);
    int j=0;
    char c=getchar();
    while(c!='\n'){
        c=convert_char(c);
        if(c==pattern[j]){
            ++j;
            if(j==pattern_length){
                cout<<'T';
                return 0;
            }
        }
        else if(j>0){
            j=arr[j-1];
            continue;
        }
        c=getchar();
    }
    cout<<'N';
    return 0;
}