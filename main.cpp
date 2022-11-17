#include<iostream>
#include"gsuffix.cpp"



int Node::END = -1;
int Node::rsc = 0;
ActivePoint Node::ap = ActivePoint();
const string Node::word = "DOGS$CATS#";

int main(){
    //string word = "abbc";
    //abcabxabcd //cdddcdc //aabaacaad banana$ //dogs$monkey$cats# //xabxa$babxba#
    Node tree = Node();
    tree.add_to_tree();
    return 0;
}