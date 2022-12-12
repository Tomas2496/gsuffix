/*#include "gsuffix.hpp"


using namespace std;

template<typename T>
Node<T>::Node(){
    children = {};
    links = nullptr;
    edge_label = {-1, nullptr};
    leaf = {};
    edge_end = -1;
    occurences_count = 0;
}


template<typename T>
Node<T>::Node(Node<T> *link, int s, int **e){
    links = link;
    children = {};
    edge_label = {s, e};
    leaf = {};
    edge_end = -1;
    occurences_count = 0;
}


template<typename T>
Node<T>::~Node(){
    for(auto [_, node] : this->children){
        delete node;
    }
}


template<typename T>
int Node<T>::start(){
    return this->edge_label.first;
}


template<typename T>
int Node<T>::end(){
    if(this->edge_end == -1){
        //return **(this->edge_label.second);
        return **(this->edge_label.second);
    }
    return this->edge_end;
}


template<typename T>
void Node<T>::update_start(int new_start){
    this->edge_label.first = new_start;
}


template<typename T>
void Node<T>::update_end(int new_end){
    this->edge_end = new_end;
}


template<typename T>
bool Node<T>::is_root(){
    return this->start() == -1;
}


template<typename T>
bool Node<T>::is_leaf(){
    return word[this->end()] == SEPERATOR;
}


template<typename T>
void Node<T>::reset_active_point(){
    ap.node = this;
    ap.length = 0;
}


template<typename T>
void Node<T>::attach_root(){
    ap.node = this;
}


template<typename T>
bool Node<T>::has_edge(T c){
    return (this->children.find(c)) != (this->children.end());
}


template<typename T>
int Node<T>::edge_length(){
    if(this->edge_end == -1)
        return this->end() - this->start() + 1;
    return this->edge_end - this->start() + 1;
}


template<typename T>
void Node<T>::update_suffix_link(){
    if(this->is_root())
        return;
    if(last_created_node){
        (last_created_node)->links = this;
    }

    last_created_node = last_created_node != ap.node ? this : nullptr;
}


template<typename T>
bool Node<T>::walk_down(){
    Node* active_node_edge = this->children[word[ap.edge]];
    if(ap.length >= active_node_edge->edge_length()){
        ap.node = active_node_edge;
        ap.edge += active_node_edge->edge_length();
        ap.length -= active_node_edge->edge_length();
        return true;
    }
    return false;
}


template<typename T>
void Node<T>::add_node(int phase, int** new_leaf_end){
    Node *leaf = new Node(this, phase, new_leaf_end);
    ap.node->children[word[phase]] = leaf;
    ap.node->update_suffix_link();
    rsc-=1;
    update_active_point(phase);
}


template<typename T>
void Node<T>::insert_inner_node(int start, int end, int phase, int** new_leaf_end){
    Node* node_to_break = ap.node->children[word[ap.edge]];
    Node *inner_node = new Node(this, start, new int* (new int(end)));                                 //create inner_node
    inner_node->children[word[phase]] = new Node(this, phase, new_leaf_end);            //add new leaf node to inner_node.
    inner_node->children[word[end+1]] = node_to_break;                          //add the remaining of the ex active node child to inner_node
    node_to_break->update_start(end+1);                                         // update the new start of edge
    ap.node->children[word[ap.edge]] = inner_node;                              //set the active node's active edge to inner_node     
    
    rsc-=1;
    // update last_created_node
    inner_node->update_suffix_link();
    update_active_point(phase);
}


template<typename T>
void Node<T>::dfs_leaf_edge_label(int len){
    if(this->children.empty()){
        this->leaf = {this->end() - len + 1, this->end()};
    }
    else{
        for(auto [_, tree] : this->children){
            tree->update_end(tree->end());
            tree->dfs_leaf_edge_label(len + tree->edge_length());
        }
    }
}


template<typename T>
void Node<T>::print_tree(vector<T> current){
    if(this->children.empty()){
        cout<<current<<"   "<<this->leaf.first<<"-"<<this->edge_end<<endl;
        //cout<<current<<" "<<this->occurences_count<<endl;
    }
    else{
        for(auto [_, tree] : this->children){
            vector<T> c;
            c.insert(c.begin(), current.begin(), current.end());
            c.insert(c.end(), word.begin() + tree->start(), word.begin() + tree->start() + tree->edge_length());
            //c.assign(word, tree->start(), tree->edge_length());
            //cout<<current + c<<" "<<tree->occurences_count<<endl;
            //tree->print_tree(current + c);
            tree->print_tree(c);
        }
    }
}


template<typename T>
bool Node<T>::handle_case_zero(int phase){
    if(ap.node->has_edge(word[phase])){
        ap.edge = phase;
        ap.length+=1;
        //rsc+=1;
        ap.node->update_suffix_link();
        return true;
    }
    return false;
}


template<typename T>
bool Node<T>::handle_case_one(int phase){
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


template<typename T>
void Node<T>::update_active_point(int phase){
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


template<typename T>
void::Node<T>::add_to_tree(){
    this->attach_root();
    int i = 0, current_word = 0;
    vector<int**> ends {new int*(&END)};
    while(i < word.length()){
        if(i >= 1 && word[i-1] == SEPERATOR){
            *ends[current_word] = new int(END);
            current_word+=1;
            ends.push_back(new int*(&END));
            rsc=0; // today
            this->reset_active_point(); // today
        }
        this->run_phase(i, ends[current_word]);
        i++;
    }
    cout<<"The rsc is "<<rsc<<endl;
    this->dfs_leaf_edge_label(0);         // for the last word.
    for(auto x : ends)                    // free allocated memory
        delete x;
}


template<typename T>
void Node<T>::run_phase(int phase, int** end){
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
            this->insert_inner_node(start_of_edge, next_index - 1, phase, end);
        }
        else{
            // if ap.length == 0
            if(word[phase] == SEPERATOR && ap.node->is_root()){ // ignore adding unique char in root
                rsc-=1;
                break;
            }
            if(handle_case_zero(phase))
                break;
            // add new node
            this->add_node(phase, end);
        }
    }
}


template<typename T>
void Node<T>::set_occurences_count(){
    bool first = true;
    int current = 0, size = word.length(), next=current+1;
    Node* temp = this, *next_node = nullptr;
    while(current < size){
        temp = temp->children[word[current]];
        if(first){
            first = false;
            next_node = temp->links;
        }
        current += temp->edge_length();
        temp->occurences_count +=1;
        if(temp->is_leaf()){        // reset if end of current suffix
            next = word[next] == SEPERATOR ? next + 2 : next + 1;
            first = true;
            current = next-1;
            temp = next_node;                      // start from the suffix link.
            if(temp->is_root())
                continue;
            current+=temp->edge_length();
            temp->occurences_count+=1;
            next_node = temp->links;
            first = false;
        }          
    }
}


template<typename T>
void Node<T>::extract_most_freq_occur_subs(int n){
    int most_freq = 0;
    std::set<std::pair<int, int>> subs;
    this->set_occurences_count();
    this->get_substrings(subs, 0, &most_freq, n);
    std::cout<<"The most freq occurs "<<most_freq<<" times"<<std::endl;
    for(auto [start, len] : subs){
        std::string c;
        c.assign(Node::word, start, len);
        std::cout<<c<<" "<<std::endl;
    }
}


template<typename T>
void Node<T>::get_substrings(std::set<std::pair<int, int>>& subs, int string_dept, int* most_frequent, int minimum){
    
    for(auto [_, node] : this->children){
        node->get_substrings(subs, string_dept + node->edge_length(), most_frequent, minimum);
    }

    if(this->is_root() || string_dept < minimum || (word[this->end()] == SEPERATOR && string_dept == minimum))
        return;

    int len = word[this->end()] == SEPERATOR ? string_dept - 1 : string_dept;

    if(this->occurences_count == *most_frequent){
        subs.insert({this->end() - string_dept + 1, len});
    }

    if(this->occurences_count > *most_frequent){
        *most_frequent = this->occurences_count;
        subs = {{this->end() - string_dept + 1, len}};
    }
}

*/