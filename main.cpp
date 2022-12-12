#include"gsuffix.hpp"
#include"reader.hpp"


Reader read = Reader("example");

template<typename T>
int Node<T>::END = -1;

template<typename T>
T Node<T>::SEPERATOR = 0U;

template<typename T>
int Node<T>::rsc = 0;

template<typename T>
Node<T>::ActivePoint Node<T>::ap = ActivePoint();

template<typename T>
Node<T>* Node<T>::last_created_node = nullptr;

template<typename T>
std::vector<T> Node<T>::word = read.words;



int main(){
    //TEST EXAMPLES
    //nonsense$sense$
    //"xabxa$bx$"
    //"xabxa$babxba$c$deef$deg$"
    //"abbc$";
    //abaaba$
    //abcabxabcd //cdddcdc //aabaacaad banana$//
    Node<uint16_t> tree = Node<uint16_t>();
    tree.add_to_tree();
    tree.print_tree({});
    tree.set_occurences_count();
    std::vector<uint16_t> result = tree.extract_most_freq_occur_subs(2);
    std::vector<std::string> orig = read.map_to_original(result); // uncomment to map to original
    for(auto x : orig)
        std::cout<<x;
    /*for(int i = 100; i <= 14'000 ; i+=100)
        tree.extract_most_freq_occur_subs(i);*/
    return 0;
}