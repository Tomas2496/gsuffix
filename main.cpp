#include<iostream>
#include"gsuffix.cpp"



int Node::END = -1;
int Node::rsc = 0;
ActivePoint Node::ap = ActivePoint();
Node* Node::last_created_node = nullptr;
string Node::word = "xabxa$babxba$";


int main(){
    //"xabxa$bx$"
    //"xabxa$babxba$c$deef$deg$"
    //"abbc";
    //abcabxabcd //cdddcdc //aabaacaad banana$//
    Node tree = Node();
    tree.add_to_tree();
    return 0;
}