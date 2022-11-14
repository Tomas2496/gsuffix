#include<iostream>
#include<unordered_map>


class Node;

struct ActivePoint {
    Node *node;
    int edge; 
    int length;
    ActivePoint() : node(nullptr), edge(-1), length(0) {}
};

struct Leaf {
    int word_nr, start;
    Leaf() : word_nr(-1), start(-1) {}
    Leaf(int wnr, int s) : word_nr(wnr), start(s) {}
};

class Node {

    std::unordered_map<char, Node*> children;  // children nodes
    Node *links;    // suffix link
    int start; //*end;  
    int *end;
    int inner_end; // inner node end.
    Leaf leaf;

    bool walk_down(std::string word);
    bool has_edge(char c);
    int edge_length();
    void update_suffix_link(Node ** node);
    void insert_inner_node(Node** lcn, int start, int end, int phase, std::string word);
    void dfs_leaf(int len, int word_size);
    void print_tree(std::string word, std::string current);
    void run_phase(int phase, std::string word);
    

    public:
        static ActivePoint ap;
        static int END;
        static int rsc;
        Node();
        Node(Node *link, int s, int *end);
        Node(Node *link, int s, int e);
        void add_to_tree(std::string word);
        static void update_active_point(int phase);
        void attach_root();
};
