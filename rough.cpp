#include<iostream>
#include<unordered_map>
#include<utility>
#include<vector>

using namespace std;

int E = 0;
int *e;

struct End{
    int* ende;
    End(int *p) : ende(p) {}
};

void f(int** n){
    if(*n){
        //cout<<**n;
    }
    int *c, d;
    d = 7;
    c = &d;
    (*n) = c;
}

int main(){
    vector<pair<int, int>> a;
    a.push_back({1,1});
    cout<<a[0].first <<"  "<< a[0].second<<endl;
    return 0;
}