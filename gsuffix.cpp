#include<iostream>
#include<unordered_map>
#include<cassert>


using namespace std;

class Node;

int END = -1, rsc = 0;


struct Leaf {
    int word_nr, start;
    Leaf() : word_nr(-1), start(-1) {}
    Leaf(int wnr, int s) : word_nr(wnr), start(s) {}
};

struct ActivePoint {
    Node *node; // contemplate changing this to a node pointer for line 54
    int edge; 
    int length;
    ActivePoint() : node(nullptr), edge(-1), length(0) {}
};


class Node {

    unordered_map<char, Node*> children;  // children nodes
    Node *links;    // suffix link
    int start; //*end;  
    int *end;
    int inner_end; // inner node end.
    Leaf leaf;

    bool walk_down(string word);
    void insert_leaf(int start);
    bool has_edge(char c);
    int edge_length(Node* tree);
    void dfs_leaf(Node* tree, int len, int word_size);
    void run_phase(int phase, string word);

    public:
        ActivePoint ap;
        Node();
        Node(Node *link, int s, int *end);
        Node(Node *link, int s, int e);
        void add_to_tree(string word);
        void print_tree(Node* tree, string word, string current);
 
};


Node::Node(){
    children = {};
    links = nullptr;
    start = -1;
    end = nullptr;
    ap = ActivePoint();
    leaf = Leaf();
}


Node::Node(Node *link, int s, int *e){
    links = link;
    children = {};
    start = s;
    end = e;
    inner_end = -1;
    leaf = Leaf();
}

Node::Node(Node *link, int s, int e){
    links = link;
    children = {};
    start = s;
    inner_end = e;
    end = nullptr;
    leaf = Leaf();
}


bool Node::walk_down(string word){
    int* current_end = this->ap.node->children[word[ap.edge]]->end;
    int current_start = this->ap.node->children[word[ap.edge]]->start;
    if((current_start + this->ap.length) == *current_end){
        //if at the end then jump to next node
        ap.node = ap.node->children[word[ap.edge]];
        ap.length = 0;
        return true;
    }
    // if not at the end just increment the length **should be do nothing.
    //ap.length++;
    return false;
}


void::Node::add_to_tree(string word){
    for(int i = 0; i<word.length(); i++)
        run_phase(i, word);
    dfs_leaf(this, 0, word.length());
    print_tree(this, word, "");
}


void Node::insert_leaf(int start){
    
}

bool Node::has_edge(char c){
    return (this->ap.node->children.find(c)) != (this->ap.node->children.end());
}

int Node::edge_length(Node* tree){
    int c_start, c_end;
    c_start = tree->start;
    if(tree->end){
        c_end = *(tree->end);
    } else{
        c_end = tree->inner_end;
    }
    //cout<<"c_end "<<c_end<<endl;
    //cout<<"c_start "<<c_start<<endl;
    return c_end - c_start + 1; 
}

void Node::dfs_leaf(Node *tree, int len, int word_size){
    if(tree->children.empty()){
        //cout<<"First   "<<word_size-len<<endl;
        tree->leaf = Leaf(0, word_size - len);
    }
    else{
        for(auto i : tree->children){
            dfs_leaf(i.second, len + edge_length(i.second), word_size);
        }
    }
}

void Node::print_tree(Node* tree, string word, string current){
    if(tree->children.empty()){
        cout<<current<<"    "<<tree->leaf.start<<endl;
    }
    else{
        for(auto i : tree->children){
            string c;
            c.assign(word, i.second->start, edge_length(i.second)); 
            print_tree(i.second, word, current + c);
        }
    }
}




void Node::run_phase(int phase, string word){
    Node *last_created_node = nullptr;
    END+=1;
    rsc+=1;
    while(rsc){
        if(ap.length > 0){
            if(walk_down(word)){
                continue;
            }
            int start_of_edge = ap.node->children[word[ap.edge]]->start;
            int next_index = start_of_edge + ap.length ;
            char next = word[next_index];
            if(next == word[phase]){
                // rule 3
                ap.length+=1;
                break;
            } else {
                // insert a leaf edge here and update ap according to c1 or c2.
                rsc-=1;                                                                      // decrement rsc because adding a new leaf node.
                int np = next_index - 1;
                Node *inner_node = new Node(this, start_of_edge, np);  //create inner_node
                ap.node->children[word[ap.edge]] = inner_node;                              //set the active node's active edge to inner_node
                inner_node->children[next] = new Node(this, next_index, &END);             //add the remaining of the ex active node child to inner_node
                inner_node->children[word[phase]] = new Node(this, phase, &END);           //add new leaf node to inner_node.

                if(last_created_node){
                    last_created_node->links = inner_node;
                } else {
                    last_created_node = inner_node;
                }
                //ANCFER2C1.
                if(ap.node->start == -1){
                    // active node is root
                    ap.length-=1;
                    ap.edge = phase - rsc + 1;
                } else {
                    //ANCFER2C2.
                    ap.node = inner_node->links;
                }
            }
        }
        else{
            // if ap.length == 0
            ap.edge = phase;            // point at the new character
            if(has_edge(word[phase])){
                //rule 3
                ap.length+=1;
                break;
            } else {
                Node *leaf = new Node(this, phase, &END);
                ap.node->children[word[phase]] = leaf;
                last_created_node = leaf;                     //not sure about this
                rsc-=1;
            }
        }
    }
}


int main(){
    Node tree = Node();
    string word = "abbc";
    tree.ap.node = &tree;
    tree.add_to_tree(word);
    //cout<<"Hello"<<endl;
    return 0;
}