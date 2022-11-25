#include<iostream>
#include<string>
#include"gsuffix.hpp"
#include"reader.hpp"


int Node::END = -1;
int Node::rsc = 0;
ActivePoint Node::ap = ActivePoint();
Node* Node::last_created_node = nullptr;
std::string Node::word = "xabxa babxba ";
std::string Reader::filename = "sample.traces";
int Reader::input_size = 0;

int main(){
    //"xabxa$bx$"
    //"xabxa$babxba$c$deef$deg$"
    //"abbc";
    //abcabxabcd //cdddcdc //aabaacaad banana$//
    //Node tree = Node();
    //tree.add_to_tree();
    std::string word =  Reader::read();
    std::cout<<Reader::input_size<<std::endl;
    return 0;
}