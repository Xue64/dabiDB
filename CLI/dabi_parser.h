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
#include "strlib.h"


/*
 * Token list:
 *      - SELECT
 *      - *
 *      - WHERE
 *      - <
 *      - >
 *      - =
 *      - FROM
 *      - ALTER
 *      - DROP
 *      - DATABASE
 *      - TABLE
 *      - COLUMN
 */


#define make_op new operand
class Parser{
private:

    // pseudo-enums for tokens
    struct token;
    static let OPERAND = 0;
    static let NOT_OP = 1;
    static let COMPOUND = 2;
    static let MATH = 3;
    static let NUMERIC = 4;
    static let VARCHAR = 5;
    static let MATH_SINGULAR = 6;
    static let MODIFY = 7;
    static let MODIFY_OPERANDS = 9;
    std::vector<std::vector<token>> * token_plane; // represents all the tokens in a query
    std::vector<std::string> query; // single-line strings to represent a query
    struct operand{ // used as a token identifier for the operand
        int parity;
        int type;

        operand(int type, int parity){
            this->parity = parity;
            this->type = type;
        }

        operand(){
            parity = -99;
            type = -99;
        }
    };

    struct token{ // contains the operand, represents the token
        std::string token_name;
        operand * token_operand;

        token (const std::string& token_name, operand * token_operand){
            this->token_operand = token_operand;
            this->token_name = token_name;
        }

        token(){
            token_name = "DEFAULT_ERROR_MUST_NOT_APPEAR";
            token_operand = new operand();
            delete token_operand;
        }

    };
    std::map<std::string, operand* > * def_token; // represents a map containing all the predefined operands, uses flyweight


    auto init_tokens(){
        def_token->emplace("SELECT", make_op(OPERAND, COMPOUND));
        def_token->emplace("WHERE", make_op(OPERAND, COMPOUND));
        def_token->emplace("FROM", make_op(OPERAND, COMPOUND));
        def_token->emplace("*", make_op(OPERAND, COMPOUND));
        def_token->emplace("<", make_op(OPERAND, MATH));
        def_token->emplace("=", make_op(OPERAND, MATH_SINGULAR));
        def_token->emplace(">", make_op(OPERAND, MATH));
        def_token->emplace("DROP", make_op(OPERAND, MODIFY));
        def_token->emplace("ALTER", make_op(OPERAND, MODIFY));
        def_token->emplace("TABLE", make_op(OPERAND, MODIFY_OPERANDS));
        def_token->emplace("DATABASE", make_op(OPERAND, MODIFY_OPERANDS));
        def_token->emplace("COLUMNS", make_op(OPERAND, MODIFY_OPERANDS));
    }


    auto tokenize (){
        std::vector<token> temp_buff;
        token token_buffer;

        for (auto i : query){
            auto buff = strlib::split(i, " ");
            for (auto j : buff){
                operand * res = new operand(NOT_OP, NOT_OP);
                try {
                    res = def_token->at(j);
                } catch (std::out_of_range e){

                }
                token_buffer = token(j, res);
            }
            temp_buff.emplace_back(token_buffer);
        }
    }


public:
    Parser(const std::vector<std::string>& query){
        this->query = query;
        def_token = new std::map<std::string, operand*>();
        init_tokens();
        token_plane = new std::vector<std::vector<token>>;
        tokenize();
    }
};




#undef make_op
#undef func
#undef let
#endif //DIVEDB__DABI_PARSER_H
