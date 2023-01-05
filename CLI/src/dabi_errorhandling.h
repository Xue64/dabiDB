//
// Created by Rufelle on 04/01/2023.
//

#ifndef DIVEDB__DABI_ERRORHANDLING_H
#define DIVEDB__DABI_ERRORHANDLING_H
#include <iostream>
namespace dabi_err{
    void no_terminating_quote(){
        std::cerr << "ERR 802 Parse Error [NoTerminatingQuoteException]: no terminating double quote character (\") detected. Remove all double quotes or fix formatting to avoid error.\n";
        exit(802);
    }

    void double_operand(const std::string &operand_name, const  std::string& prev){
        std::cerr << "ERR 803 Parse Error [DoubleOperandException]: cannot use [" << operand_name << "] after invoking instance of [" << prev << "]\n";
        exit(803);
    }

    void invalidKey(const std::string& key){
        std::cerr << "ERR 804 Parse Error [InvalidKeyException]: unknown use of keyword [" << key << "]\n";
        exit(804);
    }

    void noSelect(){
        std::cerr << "ERR 805 Null Pointer / Parse Error [NoTableSelectedException]: the SELECT statement was not found at the beginning of the query.\n";
        exit(805);
    }

    void noFrom(){
        std::cerr << "ERR 806 Null Pointer / Parse Error [NoDatabaseSelectedException]: the FROM statement was not found after the SELECT clause.\n";
        exit(806);
    }
}



#endif //DIVEDB__DABI_ERRORHANDLING_H
