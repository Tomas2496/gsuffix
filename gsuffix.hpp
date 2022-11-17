#include<iostream>
#include<unordered_map>
#include<vector>
#include<utility>

class Node;
//typedef std::pair<int, int> Leaf;
typedef std::unordered_map<char, Node*> Children;



struct ActivePoint {
    Node *node;
    int edge; 
    int length;
    ActivePoint() : node(nullptr), edge(-1), length(0) {}
};


class Node {

    Children children;  // children nodes
    Node *links;    // suffix link
    int start; //*end;  
    int *end;
    int leaf;

    bool walk_down();
    bool has_edge(char c);
    int edge_length();
    void update_suffix_link(Node ** node);
    void insert_inner_node(Node** lcn, int start, int end, int phase);
    void adjust_edge_labels();
    void dfs_leaf(int len);
    void print_tree(std::string current);
    void run_phase(int phase);
    

    public:
        static ActivePoint ap;
        static int END;
        static int rsc;
        static const std::string word;
        Node();
        Node(Node *link, int s, int *end);
        void add_to_tree();
        static void update_active_point(int phase);
        void reset_active_point();
        void attach_root();
};
