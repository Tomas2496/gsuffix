#include<iostream>
#include<fstream>
#include<bits/stdc++.h>
#include"reader.hpp"


std::string Reader::read(){
    int size = 0;
    std::string line, result;
    std::ifstream file (filename);
    if(file.is_open()){
        std::getline(file, line);             //ignore first line
        while(!file.eof()){
            file.get();                       //ignore label        
            file >> size;                     // get input length
            input_size += size/2;             // accumulate input length
            file.get();                       //ignore space
            std::getline(file, line);
            result+= remove_outputs(line);
        }
        file.close();
    } 
    else
        std::cout<<"File failed to open\n";

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
    return result;
}