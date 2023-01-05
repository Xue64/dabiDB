//
// Created by Rufelle on 04/01/2023.
//

#ifndef DIVEDB__DABI_ERRORHANDLING_H
#define DIVEDB__DABI_ERRORHANDLING_H
#include <iostream>
namespace dabi_err{
    void no_terminating_quote(){
        std::cerr << "ERR 802 [Formatting Error]: no terminating double quote character (\") detected. Remove all double quotes or fix formatting to avoid error.\n";
        exit(802);
    }
}



#endif //DIVEDB__DABI_ERRORHANDLING_H
