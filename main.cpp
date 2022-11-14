#include<iostream>
#include"gsuffix.cpp"


int Node::END = -1;
int Node::rsc = 0;
ActivePoint Node::ap = ActivePoint();

int main(){
    Node tree = Node();
    //string word = "abbc";
    //abcabxabcd //cdddcdc //aabaacaad banana$ //dogs$monkey$cats#
    string word = "aabaacaad";
    tree.attach_root();  // adds root of tree as current active point
    tree.add_to_tree(word);
    return 0;
}