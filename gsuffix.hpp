#pragma once

#include <cassert>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

template <typename T> class Node {
  typedef std::pair<int, int> Leaf;
  typedef std::unordered_map<int, Leaf> Leaves;
  typedef std::pair<int, int **> Edge;
  typedef std::map<T, Node<T> *> Children;

  Children children; // children
  Leaf leaf;
  int occurences_count; // number of times this node is visited
  Node *links;          // suffix link
  Edge edge_label;
  int edge_end;

  Node(Node *link, int s, int **end);
  int start();
  int end();
  void update_start(int new_start);
  void update_end(int new_end);
  bool is_root();
  bool is_leaf();
  void reset_active_point();
  void attach_root();
  bool has_edge(T c);
  int edge_length();
  void update_suffix_link();
  bool walk_down();
  void add_node(int phase, int **new_leaf_end);
  void insert_inner_node(int start, int end, int phase, int **new_leaf_end);
  void dfs_leaf_edge_label(int len);
  void run_phase(int phase, int **end);
  void get_substrings(std::set<std::pair<int, int>> &subs, int string_dept,
                      int *most_frequent, int minimum);
  static bool handle_case_zero(int phase);
  static bool handle_case_one(int phase);
  static void update_active_point(int phase);

public:
  struct ActivePoint {
    Node<T> *node;
    int edge;
    int length;
    ActivePoint() : node(nullptr), edge(-1), length(0) {}
  };
  Node();
  ~Node();
  void print_tree(std::vector<T> current); // TODO:: Fix the string.
  void add_to_tree();
  std::vector<T> extract_most_freq_occur_subs(int n, int *frequency);
  void set_occurences_count();
  bool operator==(const Node &other);
  static ActivePoint ap;
  static T SEPERATOR;
  static int END;
  static int rsc;
  static Node *last_created_node;
  static std::vector<T> word;
};

template <typename T> Node<T>::Node() {
  children = {};
  links = nullptr;
  edge_label = {-1, nullptr};
  leaf = {};
  edge_end = -1;
  occurences_count = 0;
}

template <typename T> Node<T>::Node(Node<T> *link, int s, int **e) {
  links = link;
  children = {};
  edge_label = {s, e};
  leaf = {};
  edge_end = -1;
  occurences_count = 0;
}

template <typename T> Node<T>::~Node() {
  for (auto [_, node] : this->children) {
    delete node;
  }
}

template <typename T> bool Node<T>::operator==(const Node &other) {
  assert(this->children.size() == other.children.size());
  for (auto [t, node] : this->children) {
    if (!(node == other.children[t]))
      return false;
  }
  if (this->is_root() && other.is_root())
    return true;
  return this->start() == other.start() && this->end() == other.end();
}

template <typename T> int Node<T>::start() { return this->edge_label.first; }

template <typename T> int Node<T>::end() {
  assert(!this->is_root() && "A root does not have an end");
  return this->edge_end == -1 ? **this->edge_label.second : this->edge_end;
}

template <typename T> void Node<T>::update_start(int new_start) {
  assert(!this->is_root() && "Trying to update root's start");
  this->edge_label.first = new_start;
}

template <typename T> void Node<T>::update_end(int new_end) {
  assert(!this->is_root() && "A root does not have an end");
  this->edge_end = new_end;
}

template <typename T> bool Node<T>::is_root() { return this->start() == -1; }

template <typename T> bool Node<T>::is_leaf() { return this->children.empty(); }

template <typename T> void Node<T>::reset_active_point() {
  ap.node = this;
  ap.length = 0;
}

template <typename T> void Node<T>::attach_root() { ap.node = this; }

template <typename T> bool Node<T>::has_edge(T c) {
  return (this->children.find(c)) != (this->children.end());
}

template <typename T> int Node<T>::edge_length() {
  assert(!this->is_root() && "Root has no edges coming to it");
  int end = this->edge_end == -1 ? this->end() : this->edge_end;
  return end - this->start() + 1;
}

template <typename T> void Node<T>::update_suffix_link() {
  if (this->is_root())
    return;
  if (last_created_node)
    (last_created_node)->links = this;
  last_created_node = last_created_node != ap.node ? this : nullptr;
}

template <typename T> bool Node<T>::walk_down() {
  Node *active_node_edge = this->children[word[ap.edge]];
  if (ap.length >= active_node_edge->edge_length()) {
    ap.node = active_node_edge;
    ap.edge += active_node_edge->edge_length();
    ap.length -= active_node_edge->edge_length();
    return true;
  }
  return false;
}

template <typename T> void Node<T>::add_node(int phase, int **new_leaf_end) {
  Node *leaf = new Node(this, phase, new_leaf_end);
  ap.node->children[word[phase]] = leaf;
  ap.node->update_suffix_link();
  rsc -= 1;
  update_active_point(phase);
}

template <typename T>
void Node<T>::insert_inner_node(int start, int end, int phase,
                                int **new_leaf_end) {
  Node *node_to_break = ap.node->children[word[ap.edge]];
  Node *inner_node =
      new Node(this, start, new int *(new int(end))); // create inner_node
  inner_node->children[word[phase]] =
      new Node(this, phase, new_leaf_end); // add new leaf node to inner_node.
  inner_node->children[word[end + 1]] =
      node_to_break; // add the remaining of the ex active node child to
                     // inner_node
  node_to_break->update_start(end + 1); // update the new start of edge
  ap.node->children[word[ap.edge]] =
      inner_node; // set the active node's active edge to inner_node

  rsc -= 1;
  // update last_created_node
  inner_node->update_suffix_link();
  update_active_point(phase);
}

template <typename T> void Node<T>::dfs_leaf_edge_label(int len) {
  for (auto [_, tree] : this->children) {
    tree->update_end(tree->end());
    tree->dfs_leaf_edge_label(len + tree->edge_length());
  }
  if (this->is_leaf())
    this->leaf = {this->end() - len + 1, this->end()};
}

template <typename T> void Node<T>::print_tree(std::vector<T> current) {
  for (auto [_, tree] : this->children) {
    std::vector<T> c;
    c.insert(c.begin(), current.begin(), current.end());
    c.insert(c.end(), word.begin() + tree->start(),
             word.begin() + tree->start() + tree->edge_length());
    tree->print_tree(c);
  }
  if (!this->is_leaf())
    return;
  for (auto x : current)
    std::cout << x;
  std::cout << "   " << this->leaf.first << "-" << this->edge_end << std::endl;
}

template <typename T> bool Node<T>::handle_case_zero(int phase) {
  if (ap.node->has_edge(word[phase])) {
    ap.edge = phase;
    ap.length += 1;
    // rsc+=1;
    ap.node->update_suffix_link();
    return true;
  }
  return false;
}

template <typename T> bool Node<T>::handle_case_one(int phase) {
  Node *active_node_edge = ap.node->children[word[ap.edge]];
  int next = active_node_edge->start() + ap.length;
  if (word[phase] == word[next]) {
    ap.length += 1;
    ap.node->update_suffix_link();
    // rsc+=1;
    return true;
  }
  return false;
}

template <typename T> void Node<T>::update_active_point(int phase) {
  if (ap.node->is_root() && ap.length > 0) {
    // active node is root
    ap.length -= 1;
    ap.edge = phase - rsc + 1;
  }
  if (!ap.node->is_root()) {
    // ANCFER2C2.
    ap.node = ap.node->links;
  }
}

template <typename T> void ::Node<T>::add_to_tree() {
  this->attach_root();
  int i = 0, current_word = 0;
  std::vector<int **> ends{new int *(&END)};
  while (i < word.size()) {
    if (i >= 1 && word[i - 1] == SEPERATOR) {
      *ends[current_word] = new int(END);
      current_word += 1;
      ends.push_back(new int *(&END));
      rsc = 0;                    // today
      this->reset_active_point(); // today
    }
    this->run_phase(i, ends[current_word]);
    i++;
  }
  // std::cout<<"The rsc is "<<rsc<<std::endl;
  this->dfs_leaf_edge_label(0); // for the last word.
  for (auto x : ends)           // free allocated memory
    delete x;
}

template <typename T> void Node<T>::run_phase(int phase, int **end) {
  last_created_node = nullptr;
  END += 1;
  rsc += 1;
  while (rsc) {
    if (ap.length > 0) {
      if (ap.node->walk_down()) {
        continue;
      }
      int start_of_edge = ap.node->children[word[ap.edge]]->start();
      int next_index = start_of_edge + ap.length;
      if (handle_case_one(phase))
        break;
      this->insert_inner_node(start_of_edge, next_index - 1, phase, end);
    } else {
      // if ap.length == 0
      if (word[phase] == SEPERATOR &&
          ap.node->is_root()) { // ignore adding unique char in root
        rsc -= 1;
        break;
      }
      if (handle_case_zero(phase))
        break;
      // add new node
      this->add_node(phase, end);
    }
  }
}

template <typename T> void Node<T>::set_occurences_count() {
  bool first = true;
  int current = 0, size = word.size(), next = current + 1;
  Node *temp = this, *next_node = nullptr;
  while (current < size) {
    temp = temp->children[word[current]];
    current += temp->edge_length();
    temp->occurences_count += 1;
    if (!temp->is_leaf())
      continue;
    next = word[next] == SEPERATOR ? next + 2 : next + 1;
    first = true;
    current = next - 1;
    temp = this;
  }
}

template <typename T>
std::vector<T> Node<T>::extract_most_freq_occur_subs(int n, int *frequency) {
  std::set<std::pair<int, int>> subs;
  this->get_substrings(subs, 0, frequency, n);
  std::vector<T> temp;
  bool first = true;
  for (auto [start, len] : subs) {
    auto _it = first ? temp.begin() : temp.end();
    first = false;
    temp.insert(_it, word.begin() + start, word.begin() + start + len);
    temp.push_back(SEPERATOR);
  }
  temp.pop_back(); // remove last sepr.
  return temp;
}

template <typename T>
void Node<T>::get_substrings(std::set<std::pair<int, int>> &subs,
                             int string_dept, int *most_frequent, int minimum) {
  for (auto [_, node] : this->children) {
    node->get_substrings(subs, string_dept + node->edge_length(), most_frequent,
                         minimum);
  }
  if (this->is_root() || string_dept < minimum ||
      (word[this->end()] == SEPERATOR && string_dept == minimum))
    return;
  int len = this->is_leaf()
                ? string_dept - 1
                : string_dept; // inorder to remove the last seperator count.
  if (this->occurences_count == *most_frequent)
    subs.insert({this->end() - string_dept + 1, len});
  if (this->occurences_count > *most_frequent) {
    *most_frequent = this->occurences_count;
    subs = {{this->end() - string_dept + 1, len}};
  }
}
