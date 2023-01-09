//
// Created by Rufelle on 04/01/2023.
//

#ifndef DIVEDB__DABI_ERRORHANDLING_H
#define DIVEDB__DABI_ERRORHANDLING_H
#include <iostream>
#include <vector>
#include <string>

namespace dabi_err{

    void unknownCLICommand(std::vector<std::string> args){
        std::cerr << "ERR 41 Args Error [UnknownCLIArgumentException]: unknown CLI command sequence: [ ";
        int ctr = 0;
        for (auto i: args){
            ctr++;
            if (ctr<3){
                continue;
            }
            std::cerr << i << " ";
        }
        std::cerr << "] \n";
        std::cerr << "\nknown commands:\n\n\tFOR ADMIN ACCESS: -h [host name] -p [host password]\n\t"
                     "FOR USER ACCESS: -h [host name] -p [host password] -u [username]\n\t";
        exit(41);
    }

    void reselectedTable(std::string table){
        std::cerr << "ERR 701 Selector Error [DuplicateSelectionException]: multiple instances of table [" << table << "] being selected\n";
        exit(701);
    }

    void aliasSelection(){
        std::cerr << "ERR 702 Selector Error [AliasSelectionException]: cannot select another table after invoking instance of [*].\n";
        exit(702);
    }

    void fromAlias(){
        std::cerr << "ERR 703 Selector Error [AliasedFromException]: cannot perform FROM operation on invoked instance of [*].\n";
        exit(703);
    }

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

    void danglingOperand(std::string op){
        std::cerr << "ERR 809 Parse Error [DanglingOperandException]: cannot end on operand [" << op << "]. This is an incomplete query.\n";
        exit(807);
    }

    void invalidMathOperand(const std::string &math, const std::string &operand){
        std::cerr << "ERR 901 Operand Mismatch [NotNumericOperandException]: the operand [" << operand << "] cannot operate on NUMERIC data [" << math << "]\n";
        exit(901);
    }

    void invalidStringOperand(const std::string &math, const std::string &operand){
        std::cerr << "ERR 902 Operand Mismatch [NotVARCHAROperandException]: the operand [" << operand << "] cannot operate on VARCHAR data [" << math << "]\n";
        exit(902);
    }

    void invalidVariableOperand(const std::string &math, const std::string &operand){
        std::cerr << "ERR 903 Operand Mismatch [NotSelectorOperandException]: the operand [" << operand << "] cannot operate on VARIABLE data [" << math << "]\n";
        exit(903);
    }

    void invalidModifierOperand(const std::string &math, const std::string &operand){
        std::cerr << "ERR 904 Operand Mismatch [NotModifierOperandException]: the operand [" << operand << "] cannot operate on MODIFIER data [" << math << "]\n";
        exit(904);
    }

}



#endif //DIVEDB__DABI_ERRORHANDLING_H
