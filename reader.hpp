#pragma once

#include<string>

class Reader {
public:
    static std::string filename;
    static int input_size;

    static std::string read();
    static std::string remove_outputs(std::string);
};