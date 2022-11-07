#include<iostream>
#include<unordered_map>

using namespace std;

int E = 0;
int *e;

struct End{
    int* ende;
    End(int *p) : ende(p) {}
};

int f(int* n){
    return *n;
}

int main(){
    string c = "abc";
    string b = "def";
    string d  = c + b;
    cout<<d<<endl;
    return 0;
}