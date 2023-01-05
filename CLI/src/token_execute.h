//
// Created by Rufelle on 06/01/2023.
//

#ifndef DIVEDB__TOKEN_EXECUTE_H
#define DIVEDB__TOKEN_EXECUTE_H
#include"token.h"
#include "dabi_macros.h"
namespace dabi{
    class stream_execute{
        std::vector<token*> * token_stream;

        func run (){
            return;
        }

        stream_execute(std::vector<token*> * token_stream){
            this->token_stream = token_stream;
            run();
        }


    };
}


#endif //DIVEDB__TOKEN_EXECUTE_H
