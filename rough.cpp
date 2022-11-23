#include<iostream>
#include<unordered_map>
#include<utility>
#include<vector>

using namespace std;

class a{
    public:
        static int *index;
        static string word;
        static const vector<string> words;
};

int* a::index = new int(0);
const vector<string> a::words{"dogs", "cats"};
//vector<string>::iterator a::word = words.begin();


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
    a b;
    cout<<b.word<<endl;
    b.index+=1;
    cout<<b.word<<endl;
    return 0;
}