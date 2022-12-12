#pragma once

#include<string>
#include<unordered_map>


class Reader {
    std::string filename;
    int input_size;
    uint16_t next_numbr;
    std::string read();
    std::string remove_outputs(std::string);
    void make_dictionary();
    void add_words(std::string, int size);
    void start();

public:
    Reader(std::string name);
    std::vector<uint16_t> words;
    std::unordered_map<std::string, uint16_t> dictionary;
    std::unordered_map<uint16_t, std::string> ref;
    std::vector<std::string>map_to_original(const std::vector<uint16_t> word); 
};