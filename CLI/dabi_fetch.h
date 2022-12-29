//
// Created by Rufelle on 28/12/2022.
//

#ifndef DIVEDB__DABI_FETCH_H
#define DIVEDB__DABI_FETCH_H
#include "dabi_macros.h"
#include <iostream>
#include <vector>
#include <memory>



auto consolidate (const int &argc, char ** argv) {
    auto vector = std::make_unique<std::vector<std::string>>();
    for (int i=0; i<argc; i++){
        vector->push_back(argv[i]);
    }
    return vector;
}


auto fetch_command(std::string cmd) -> bool {
    if (cmd=="--ver" || cmd == "-v"){
        std::cout << "v.0.0.1\nbuild 28.12.22\n\n";
        return true;
    }
    return false;
}

auto fetch_command (int argc, char ** argv) -> void {
    auto vector = consolidate(argc, argv);
    if (vector->at(1)=="-c"){
        if (vector->size()<=2){
            std::cout << "WARNING!\n"
                         "\t\tCommand path not detected. Please use only with DABI's pre-built APIs."
                         "\n\t\tUsing the CLI without the APIs may result in undefined behavior.\n\n";
        }
    }
}


#endif //DIVEDB__DABI_FETCH_H
