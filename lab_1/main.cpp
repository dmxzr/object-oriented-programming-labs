#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <cstring>
#include "UI/UI.hpp"
#include "convert/convert.hpp"



vector<int> get_int_array(){
	vector<int> array;
	string line;
	getline(cin, line); 
	stringstream ss(line);
	int num;
	while (ss >> num) { 
		array.push_back(num);
	}
	return array;
}


char *get_str_array(){
	string line;
	getline(cin, line); 
	char *result = new char[line.length() + 1];
	strcpy(result, line.c_str());
	return result;
}

string get_string(){
	string line;
	getline(cin, line);
	return line;
}

int print_vector(vector<int> array){
	for (int val : array) {
		cout << val << " ";
	    }
	    cout << endl;
	return 0;
}

int main() {
	int choice;
	cout << MAIN_MENU;
	string array_name, result;
	vector<int> res;
	while(cin >> choice){
		switch(choice){
			case 1:
				cout << "\n -> Array to TOML \n";

				//cout << INPUT_MENU;
				
				//cout << "\n -> Input from console to file\n\n";

		
				cout << "Enter the name of the array: ";
				cin >> array_name;
				//getline(cin, array_name);
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				
				
				//cin >> array;
				
				cout << TYPE_OF_STRING;
				cin >> choice;
				switch(choice){
					case 1:
						cout << "\n -> default\n";
						cout << "Enter array elements (separate by space): ";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						result = convert_to_toml(get_int_array(), array_name.c_str());
						cout << result << endl;
						break;
					case 2:
						cout << "\n -> const char*\n";
						cout << "Enter array elements (separate by space): ";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						result = convert_to_toml(get_str_array(), array_name.c_str());
						cout << result << endl;
						break;
					case 3:
						cout << "\n -> const char* + size_t\n";
						cout << "Enter array elements (separate by space): ";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						char *input;
						input = get_str_array();
						result = convert_to_toml(input, strlen(input) ,array_name.c_str());
						cout << result << endl;
						delete[] input;
						break;
					case 4:
						cout << "\n -> std::string\n";
						cout << "Enter array elements (separate by space): ";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						result = convert_to_toml(get_string(), array_name.c_str());
						cout << result << endl;
						break;

					default:
						cout << "Invalid choice\n";
						continue;
				}
				break;

				
			case 2:
				cout << "\n -> TOML to array \n";


				cin.ignore(numeric_limits<streamsize>::max(), '\n');
								
								
				//cin >> array;
								
				cout << TYPE_OF_TOML;
				cin >> choice;
				switch(choice){
					case 1:
						cout << "\n -> const char*\n";
						cout << "Enter TOML: ";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						res = convert_to_array(get_str_array());
						print_vector(res);
						break;

					case 2:
						cout << "\n -> const char* + size_t\n";
						cout << "Enter TOML: ";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						char *input;
						input = get_str_array();
						res = convert_to_array(input, sizeof(input));
						print_vector(res);
						delete[] input;
						break;

					case 3:
						cout << "\n -> std::string\n";
						cout << "Enter TOML: ";
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
											
						res = convert_to_array(get_string());
						print_vector(res);
						
						break;
					}
				
				break;

			case 3:
				cout << "\n -> Exit \n";
				return 0;

				
			default:
				cout << choice;
				break;
			
		}
		cout << MAIN_MENU;
	}
	

	return 0;
}

