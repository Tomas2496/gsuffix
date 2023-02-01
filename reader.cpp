#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include<stdexcept>
#include"reader.hpp"


Reader::Reader(){
    filename = "";
    next_numbr = 0U;
}


Reader::Reader(std::string name){
    filename = name;
    next_numbr = 1U;
    start();
}


void Reader::read(){
    int size = 0;
    std::string line, result;
    std::ifstream file (filename);
    if(!file.is_open())
        throw std::runtime_error("could not open file");
    
    std::getline(file, line);             //ignore first line
    while(!file.eof()){                  
        file >> result ; file >> result;  //ignores label & length
        std::getline(file, line);
        add_input(line);
    }
    file.close();
}


void Reader::add_input(std::string str){
    std::istringstream stream(str);
    std::string temp, result;
    int i = 0;
    while(stream >> temp ){
        if(i % 2 != 0){
            i++;
            continue;
        }
        input.push_back(temp);
        i++;   
    }
    input.push_back(SEPERATOR);
}


void Reader::make_dictionary_and_add_words(){
    dictionary[SEPERATOR] = 0U;
    ref[0U] = SEPERATOR;
    for(std::string temp : input){
        if(dictionary.find(temp) != dictionary.end()){
            words.push_back(dictionary[temp]);
            continue;
        }
        dictionary[temp] = next_numbr;
        ref[next_numbr] = temp;
        words.push_back(next_numbr);
        next_numbr += 1U;
    }
}


void Reader::start(){
    read();
    make_dictionary_and_add_words();
}


std::vector<std::string> Reader::map_to_original(std::vector<uint16_t> word){
    std::vector<std::string> result;
    for(uint16_t x : word)
        result.push_back(ref[x]);
    return result;
}