#include<iostream>
#include<unordered_map>
#include<vector>
#include<utility>

class Node;
typedef std::pair<int, int> Leaf;
typedef std::pair<int , int*> Edge;
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
    Edge edge_label;
    std::vector<Leaf> leaf;


    Node(Node *link, int s, int* end);
    int start();
    int end();
    void update_start(int new_start);
    void update_end(int new_end);
    bool is_root();
    void reset_active_point();
    void attach_root();
    bool has_edge(char c);
    int edge_length();
    void update_suffix_link();
    bool walk_down();
    void add_node(int phase);
    void insert_inner_node(int start, int end, int phase);
    void dfs_leaf_edge_label(int len);
    void print_tree(std::string current);
    void run_phase(int phase);
    static bool handle_case_zero(int phase);
    static bool handle_case_one(int phase);
    static void update_active_point(int phase);

    public:
        Node();
        void add_to_tree();
        static ActivePoint ap;
        static int END;
        static int rsc;
        static Node* last_created_node;
        static std::string word;
        
        
};
