#include "convert.hpp"
#include <sstream>
#include <stdexcept>
#include <iostream>

bool is_number(const std::string& s) {
    if (s.empty()) return false;

    size_t start = (s[0] == '-') ? 1 : 0;

    if (start == 1 && s.length() == 1) return false;

    return s.find_first_not_of("0123456789", start) == std::string::npos;
}
std::string convert_to_toml(const std::vector<int>& array, const char* name) {
    std::ostringstream out;
    out << "[" << name << "]\n";
    for (size_t i = 0; i < array.size(); ++i) {
        out << (i + 1) << "=" << array[i] << "\n";
    }
    return out.str();
}

std::string convert_to_toml(const char* array, const char* name) {
    std::ostringstream out;
    out << "[" << name << "]\n";

    std::istringstream iss(array);
    std::string token;
    int index = 1;

    while (iss >> token) {
        if (is_number(token)) {
            out << index++ << "=" << token << "\n";
        } else {
            out << index++ << "=\"" << token << "\"\n";
        }
    }
    return out.str();
}

std::string convert_to_toml(const char* array, size_t size, const char* name) {
    return convert_to_toml(std::string(array, size).c_str(), name);
}

std::string convert_to_toml(const std::string& array, const char* name) {
    return convert_to_toml(array.c_str(), name);
}


std::vector<int> convert_to_array(const std::string &toml_string) {
    std::istringstream iss(toml_string);
    std::string line;
    std::vector<int> array;
    //getline(iss, line); 
   
    while (getline(iss, line)) {
    	size_t start_pos = 0;
    	while(true){
    	//std::cout << "зашел!" << std::endl;
        size_t equal_pos = line.find('=', start_pos);
        //std::cout << equal_pos << " " << start_pos << std::endl; 
        if(equal_pos == std::string::npos) break;
        if (equal_pos != std::string::npos) {
            int value = stoi(line.substr(equal_pos + 1));
            array.push_back(value);
            start_pos = equal_pos + 1;
        }
	
        }
    }
    return array;
}

std::vector<int> convert_to_array(const char* toml_string) {
    return convert_to_array(std::string(toml_string));
}

std::vector<int> convert_to_array(const char* toml_string, size_t size) {
    return convert_to_array(std::string(toml_string));
}
