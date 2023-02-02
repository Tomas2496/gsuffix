#pragma once

#include <string>
#include <unordered_map>
#include <vector>

const std::string SEPERATOR = "$";

class Reader {
  std::string filename;
  uint16_t next_numbr;
  std::vector<std::string> input;
  void read();
  void add_input(std::string line);
  void make_dictionary_and_add_words();
  void start();

public:
  Reader();
  Reader(std::string name);
  std::vector<uint16_t> words;
  std::unordered_map<std::string, uint16_t> dictionary;
  std::unordered_map<uint16_t, std::string> ref;
  std::vector<std::string> map_to_original(const std::vector<uint16_t> word);
};