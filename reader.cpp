#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include"reader.hpp"



Reader::Reader(std::string name){
    filename = name;
    next_numbr = 1U;
    input_size = 0;
    start();
}


std::string Reader::read(){
    int size = 0;
    std::string line, result;
    std::ifstream file (filename + ".traces");
    if(!file.is_open()){
        std::cout<<"The file is not open"<<std::endl;
        return " ";
    }
    while(!file.eof()){
        file.get();                       //ignore label        
        file >> size;                     // get input length
        input_size += size/2;             // accumulate input length
        file.get();                       //ignore space
        std::getline(file, line);
        result+= remove_outputs(line);
    }
    file.close();
    return result;
}


std::string Reader::remove_outputs(std::string str){
    std::istringstream stream(str);
    std::string temp, result;
    int i = 0;
    while(stream >> temp ){
        if(i % 2 != 0){
            i++;
            continue;
        }
        result+= temp + " ";
        i++;   
    }
    return result + "$ ";
}


void Reader::make_dictionary(){
    std::string temp;
    std::ifstream file (filename + ".inputs");
    dictionary["$"] = 0U;
    ref[0U] = "$";
    if(!file.is_open()){
        std::cout<<"File not opened"<<std::endl;
        return;
    }
    while(!file.eof()){
        std::getline(file, temp);
        dictionary[temp] = next_numbr;
        ref[next_numbr] = temp;
        next_numbr += 1U;
    }
    file.close();
}


void Reader::add_words(std::string result, int size){
    std::istringstream stream(result);
    std::string temp;
    while(stream >> temp){
        words.push_back(dictionary[temp]);     // because in the all.inputs every char is terminated with \r. 
    }
}


void Reader::start(){
    std::string traces = read();
    make_dictionary();
    add_words(traces, 0);
}


std::vector<std::string> Reader::map_to_original(std::vector<uint16_t> word){
    std::vector<std::string> result;
    for(uint16_t x : word)
        result.push_back(ref[x]);
    return result;
}