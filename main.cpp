#include "gsuffix.hpp"
#include "reader.hpp"

template <typename T> int Node<T>::END = -1;
template <typename T> T Node<T>::SEPERATOR = 0U;
template <typename T> int Node<T>::rsc = 0;
template <typename T>
Node<T>::ActivePoint Node<T>::ap = Node<uint16_t>::ActivePoint();
template <typename T> Node<T> *Node<T>::last_created_node = nullptr;
template <typename T> std::vector<T> Node<T>::word = {};
Node<uint16_t> tree = Node<uint16_t>();
Reader reader;

void build_tree() {
  std::string input;
  std::cin >> input;
  reader = Reader(input);
  Node<uint16_t>::word = reader.words;
  tree.add_to_tree();
  // tree.print_tree({});      //uncomment to print tree
  tree.set_occurences_count();
}

void print_substrings() {
  std::string input;
  std::cin >> input;
  int frequency = 0;
  std::vector<uint16_t> result =
      tree.extract_most_freq_occur_subs(stoi(input), &frequency);
  std::vector<std::string> orig = reader.map_to_original(result);
  std::cout << frequency << " ";
  for (auto x : orig) {
    if (x == "$") {
      std::cout << std::endl << frequency << " ";
      continue;
    }
    std::cout << x << " ";
  }
  std::cout << std::endl;
}

int main() {
  // TEST EXAMPLES
  // nonsense$sense$
  //"xabxa$bx$"
  //"xabxa$babxba$c$deef$deg$"
  //"abbc$";
  // abaaba$
  // abcabxabcd //cdddcdc //aabaacaad banana$//

  std::string commands = "The following commands are available\n"
                         "f <path to trace>       build tree\n"
                         "n <minimum length for substrings>      prints "
                         "frequency-substring on console\n"
                         "q    quit\n";

  while (1) {
    std::string command, input;
    std::cin >> command;
    if (command == "f") {
      build_tree();
    } else if (command == "n") {
      print_substrings();
    } else if (command == "q")
      break;
    else
      std::cout << commands;
  }
  return 0;
}