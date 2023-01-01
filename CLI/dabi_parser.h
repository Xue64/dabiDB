//
// Created by Rufelle on 01/01/2023.
//

#ifndef DIVEDB__DABI_PARSER_H
#define DIVEDB__DABI_PARSER_H
#include <iostream>
#include <memory>
#include <string>
#include "dabi_macros.h"
#include <map>
#include <hash_map>


/*
 * Token list:
 *      - SELECT
 *      - *
 *      - WHERE
 *      - <
 *      - >
 *      - =
 *      - FROM
 *
 */
#define make_op operand
class Parser{
private:
    static let OPERAND = 0;
    static let NOT_OP = 1;
    static let COMPOUND = 2;
    static let MATH = 3;
    static let NUMERIC = 4;
    static let VARCHAR = 5;
    static let MATH_SINGULAR = 6;
    std::vector<std::vector<std::string>> * token_plane;
    std::vector<std::string> query;
    struct operand{
        int parity;
        int type;

        operand(int type, int parity){
            this->parity = parity;
            this->type = type;
        }
    };
    std::map<std::string, operand> * def_token;


    auto init_tokens(){
        def_token->emplace("SELECT", make_op(OPERAND, COMPOUND));
        def_token->emplace("WHERE", make_op(OPERAND, COMPOUND));
        def_token->emplace("FROM", make_op(OPERAND, COMPOUND));
        def_token->emplace("*", make_op(OPERAND, COMPOUND));
        def_token->emplace("<", make_op(OPERAND, MATH));
        def_token->emplace("=", make_op(OPERAND, MATH_SINGULAR));
        def_token->emplace(">", make_op(OPERAND, MATH));
    }


    auto tokenize (){
        std::vector<std::string> temp_buff;

        for (auto i : query){
            auto buff = strlib::split(i, " ");
            for (auto j : buff){
                operand res = operand(0, 0);
                try {
                    res = def_token->at(j);
                } catch (std::out_of_range e){
                    res = operand(NOT_OP, NOT_OP);
                }
            }
        }
    }


public:
    Parser(const std::vector<std::string>& query){
        this->query = query;
        def_token = new std::map<std::string, operand>();
        init_tokens();
        token_plane = new std::vector<std::vector<std::string>>;
        tokenize();
    }
};




#undef make_op
#undef func
#undef let
#endif //DIVEDB__DABI_PARSER_H
