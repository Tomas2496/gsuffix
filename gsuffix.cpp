#include<iostream>
#include<unordered_map>
#include "gsuffix.hpp"


#define SEPERATOR '$'


using namespace std;


Node::Node(){
    children = {};
    links = nullptr;
    edge_label = {-1, nullptr};
    leaf = {};
}


Node::Node(Node *link, int s, int *e){
    links = link;
    children = {};
    edge_label = {s, e};
    leaf = {};
}


int Node::start(){
    return this->edge_label.first;
}


int Node::end(){
    return *(this->edge_label.second);
}


void Node::update_start(int new_start){
    this->edge_label.first = new_start;
}


void Node::update_end(int new_end){
    this->edge_label.second = new int(new_end);
}


bool Node::is_root(){
    return this->start() == -1;
}


void Node::reset_active_point(){
    ap.node = this;
    ap.length = 0;
}


void Node::attach_root(){
    ap.node = this;
}


bool Node::has_edge(char c){
    return (this->children.find(c)) != (this->children.end());
}


int Node::edge_length(){
    return this->end() - this->start() + 1;
}


void Node::update_suffix_link(){
    if(this->is_root())
        return;
    if(last_created_node){
        (last_created_node)->links = this;
    }

    last_created_node = last_created_node != ap.node ? this : nullptr;
}


bool Node::walk_down(){
    Node* active_node_edge = this->children[word[ap.edge]];
    if(ap.length >= active_node_edge->edge_length()){
        ap.node = active_node_edge;
        ap.edge += active_node_edge->edge_length();
        ap.length -= active_node_edge->edge_length();
        return true;
    }
    return false;
}


void Node::add_node(int phase){
    Node *leaf = new Node(this, phase, &END);
    ap.node->children[word[phase]] = leaf;
    ap.node->update_suffix_link();
    rsc-=1;
    update_active_point(phase);
}


void Node::insert_inner_node(int start, int end, int phase){
    Node* node_to_break = ap.node->children[word[ap.edge]];
    Node *inner_node = new Node(this, start, new int(end));                     //create inner_node
    inner_node->children[word[phase]] = new Node(this, phase, &END);            //add new leaf node to inner_node.
    inner_node->children[word[end+1]] = node_to_break;                          //add the remaining of the ex active node child to inner_node
    node_to_break->update_start(end+1);                                         // update the new start of edge
    ap.node->children[word[ap.edge]] = inner_node;                              //set the active node's active edge to inner_node     
    
    rsc-=1;
    // update last_created_node
    inner_node->update_suffix_link();
    update_active_point(phase);
}


void Node::dfs_leaf_edge_label(int len){
    if(this->children.empty()){
        if(!this->leaf.empty()){
            string a, b; 
            a.assign(word, this->leaf[0].first, len);
            b.assign(word, END - len + 1, len);
            if(a == b){
                this->leaf.push_back({END - len + 1, END});
            }
        } 
        else
            this->leaf.push_back({END - len + 1, END});
    }
    else{
        for(auto [_, tree] : this->children){
            tree->update_end(tree->end());
            tree->dfs_leaf_edge_label(len + tree->edge_length());
        }
    }
}


void Node::print_tree(string current){
    if(this->children.empty()){
        for(auto [start, end] : this->leaf){
            cout<<current<<"    "<<start<<" - "<<end<<endl;
        }
    }
    else{
        for(auto [_, tree] : this->children){
            string c;
            c.assign(word, tree->start(), tree->edge_length()); 
            tree->print_tree(current + c);
        }
    }
}


bool Node::handle_case_zero(int phase){
    if(ap.node->has_edge(word[phase])){
        ap.edge = phase;
        ap.length+=1;
        //rsc+=1;
        ap.node->update_suffix_link();
        return true;
    }
    return false;
}


bool Node::handle_case_one(int phase){
    Node* active_node_edge = ap.node->children[word[ap.edge]];
    int next = active_node_edge->start() + ap.length;
    if(word[phase] == word[next]){
        ap.length+=1;
        ap.node->update_suffix_link();
        //rsc+=1;
        return true;
    }
    return false;
}


void Node::update_active_point(int phase){
    if(ap.node->is_root() && ap.length > 0){
        // active node is root
        ap.length-=1;
        ap.edge = phase - rsc + 1;
    }  
    if(!ap.node->is_root()){
        //ANCFER2C2.
        ap.node = ap.node->links;
    }
}


void::Node::add_to_tree(){
    this->attach_root();
    int i = 0;
    while(i < word.length()){
        if(i >= 1 && word[i-1] == SEPERATOR){
            this->dfs_leaf_edge_label(0);
            rsc=0; // today
            this->reset_active_point(); // today
        }
        this->run_phase(i);
        i++;
    }
    cout<<"The rsc is "<<rsc<<endl;
    this->dfs_leaf_edge_label(0);         // for the last word.
    this->print_tree("");
}


void Node::run_phase(int phase){
    last_created_node = nullptr;
    END+=1;
    rsc+=1;
    while(rsc){
        if(ap.length > 0){
            if(ap.node->walk_down()){
                continue;
            }
            int start_of_edge = ap.node->children[word[ap.edge]]->start();
            int next_index = start_of_edge + ap.length ;
            if(handle_case_one(phase))
                break;
            this->insert_inner_node(start_of_edge, next_index - 1, phase);
        }
        else{
            // if ap.length == 0
            if(word[phase] == SEPERATOR){
                rsc-=1;
                break;
            }
            if(handle_case_zero(phase))
                break;
            // add new node
            this->add_node(phase);
        }
    }
}