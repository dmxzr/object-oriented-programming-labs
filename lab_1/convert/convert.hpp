#ifndef _CONVERT_HPP_
#define _CONVERT_HPP_

#include <string>
#include <vector>

std::string convert_to_toml(const std::vector<int>& array, const char* name);
std::string convert_to_toml(const char* array, const char* name);
std::string convert_to_toml(const char* array, size_t size, const char* name);
std::string convert_to_toml(const std::string& array, const char* name);

std::vector<int> convert_to_array(const std::string& toml_string);
std::vector<int> convert_to_array(const char* toml_string);
std::vector<int> convert_to_array(const char* toml_string, size_t size);

#endif //_CONVERT_HPP_
