//
// Created by Rufelle on 05/01/2023.
//

#ifndef DIVEDB__DABI_CLI_H
#define DIVEDB__DABI_CLI_H
#include "dabi_macros.h"
#include "iostream"
#include "strlib.h"
namespace CLI{

    void verify (std::string hash){
        return;
    }

    auto event_loop (std::string hash) -> std::string {
        std::string ret;
        verify(hash);
        while (true){
            std::string buffer;
            std::cout << "> ";
            std::getline(std::cin, buffer);
            if (buffer==";"){
                break;
            }
            ret += " " + buffer;
            if (buffer.length()>=1){
                if (buffer.at(buffer.length()-1)==';'){
                    ret = ret.substr(0, ret.length()-1);
                    break;
                }
            }
        }
        return ret;
    }

    auto event_loop () -> std::string {
        std::string ret, hash;
        std::cout << "enter database password: ";
        hash = strlib::get_pass();
        verify(hash);
        while (true){
            std::string buffer;
            std::cout << "> ";
            std::getline(std::cin, buffer);
            if (buffer==";"){
                break;
            }
            ret += " " + buffer;
        }
        return ret;
    }
}

#undef func
#undef let

#endif //DIVEDB__DABI_CLI_H
