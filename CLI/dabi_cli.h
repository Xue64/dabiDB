//
// Created by Rufelle on 05/01/2023.
//

#ifndef DIVEDB__DABI_CLI_H
#define DIVEDB__DABI_CLI_H
#include "dabi_macros.h"
#include "iostream"
#include "strlib.h"
namespace CLI{

    void verify (std::string key, std::string hash){
        return;
    }

    auto event_loop (std::string key, std::string hash) -> std::string {
        std::string ret;
        verify(key, hash);
        while (true){
            std::string buffer;
            std::cout << "[" + key + "]>> ";
            std::getline(std::cin, buffer);
            if (buffer==";"){
                break;
            }
            ret += " " + buffer;
        }
        return ret;
    }

    auto event_loop () -> std::string {
        std::string ret;
        std::cout << "enter database key: ";
        std::string key, hash;
        std::getline(std::cin, key);
        std::cout << "enter database password: ";
        hash = strlib::get_pass();
        verify(key, hash);
        while (true){
            std::string buffer;
            std::cout << "[" + key + "]>> ";
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
