#ifndef CPP_COMMONS_COMMON_LIST_H
#define CPP_COMMONS_COMMON_LIST_H

#include <list>
#include <string>
#include <exception>
#include <iostream>
#include <fstream>
#include <common_util.h>
#include <unsupported_data_type_exception.h>
#include <common_var.h>

namespace cpp_commons {

    namespace common_collection {

        namespace common_list {

            template<typename T>
            std::list<T> convertFromString(const std::string &str) {
                using namespace std;
                list<T> l{};
                auto start = 0U;
                auto end = str.find(COMMA);
                string token;
                T data;
                while (end != string::npos) {
                    token = str.substr(start, end - start);
                    data = data_util::convertData<T>(token);
                    l.push_back(data);
//                    cout << token << endl;
                    start = end + COMMA.length();
                    end = str.find(COMMA, start);
                }
                token = str.substr(start, end);
                data = data_util::convertData<T>(token);
                l.push_back(data);
//                cout << token << endl;
                return l;
            }

            template<typename T>
            std::list<T> importFromFile(const std::string &fileName) {
                using namespace std;
                ifstream is(fileName);
                if (is.is_open()) {   //checking whether the file is open
                    string tp;
                    while (getline(is, tp)) { //read data from file object and put it into string.
//                        cout << tp << endl; //print the data of the string
                        return convertFromString<T>(tp);
                    }
                    is.close(); //close the file object.
                }
                return list<T>{};
            }

            template<typename T>
            void print(std::list<T> l) {
                using namespace std;
                cout << "[";
                typename list<T>::iterator beforeEnd = prev(l.end(), 1);
                for (auto it = l.begin(); it != l.end(); ++it){
                    cout << it.operator*();
                    if (it != beforeEnd) {
                        cout << ", ";
                    }
                }
                cout << "]";
            }

        }
    }
}

#endif
