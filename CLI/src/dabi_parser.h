//
// Created by Rufelle on 01/01/2023.
//

#ifndef DIVEDB__DABI_PARSER_H
#define DIVEDB__DABI_PARSER_H
#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <hash_map>
#include "strlib.h"
#include "token_execute.h"
#include "token.h"
#include "dabi_macros.h"

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
namespace dabi {
    class Parser {
    private:

        // pseudo-enums for tokens
        static let OPERAND = 0;
        static let NOT_OP = 1;
        static let SELECTOR = 2;
        static let MATH = 3;
        static let NUMERIC = 4;
        static let VARCHAR = 5;
        // CHANGE!! static let MATH_SINGULAR = 6;
        static let MODIFY = 7;
        static let MODIFY_OPERANDS = 9;
        static let STRING_OPERATOR = 10;
        static let VARNAME = 11;
        std::vector<token *> *token_plane; // represents all the tokens in a query
        std::string query; // single-line strings to represent a query
        std::map<std::string, operand *> *def_token; // represents a map containing all the predefined operands, uses flyweight


        auto init_tokens() {
            def_token->emplace("SELECT", make_op(OPERAND, SELECTOR));
            def_token->emplace("WHERE", make_op(OPERAND, SELECTOR));
            def_token->emplace("FROM", make_op(OPERAND, SELECTOR));
            def_token->emplace("<", make_op(OPERAND, MATH));
            def_token->emplace(">=", make_op(OPERAND, MATH));
            def_token->emplace("=", make_op(OPERAND, MATH));
            def_token->emplace("<=", make_op(OPERAND, MATH));
            def_token->emplace(">", make_op(OPERAND, MATH));
            def_token->emplace("DROP", make_op(OPERAND, MODIFY));
            def_token->emplace("ALTER", make_op(OPERAND, MODIFY));
            def_token->emplace("TABLE", make_op(OPERAND, MODIFY_OPERANDS));
            def_token->emplace("DATABASE", make_op(OPERAND, MODIFY_OPERANDS));
            def_token->emplace("COLUMNS", make_op(OPERAND, MODIFY_OPERANDS));
            def_token->emplace("LIKE", make_op(OPERAND, STRING_OPERATOR));
        }

        auto parse() {
            bool isTurn = false;
            std::string prev;
            token *prev_token;
            for (auto i: *token_plane) {
                // operand checking
                if (i->token_operand->type == OPERAND) {
                    if (isTurn) {
                        dabi_err::double_operand(i->token_name, prev);
                    }
                    isTurn = true;
                } else {
                    // non-operand variable type checking
                    if (!isTurn) { // checks if operand - not_operand order is maintained
                        dabi_err::invalidKey(i->token_name);
                    }

                    // checking for NUMERIC tokens
                    if (i->token_operand->data_type == NUMERIC) {
                        if (prev_token->token_operand->data_type != MATH) {
                            dabi_err::invalidMathOperand(i->token_name, prev_token->token_name);
                        }
                    } else if (i->token_operand->data_type == VARNAME) {
                        if (prev_token->token_operand->data_type != SELECTOR) {
                            dabi_err::invalidVariableOperand(i->token_name, prev_token->token_name);
                        }
                    } else if (i->token_operand->data_type == VARCHAR) {
                        if (prev_token->token_operand->data_type != STRING_OPERATOR) {
                            dabi_err::invalidStringOperand(i->token_name, prev_token->token_name);
                        }
                    }
                    isTurn = false;
                }
                prev = i->token_name;
                prev_token = i;
            }

            if (isTurn) {
                dabi_err::danglingOperand((token_plane->at(token_plane->size() - 1))->token_name);
            }

            if (token_plane->size() == 0) {
                dabi_err::noSelect();
            } else if (token_plane->at(0)->token_name != "SELECT") {
                dabi_err::noSelect();
            } else if (token_plane->size() <= 3) {
                dabi_err::noFrom();
            } else if (token_plane->at(2)->token_name != "FROM") {
                dabi_err::noFrom();
            }
        }


        auto tokenize() {
            std::vector<token *> temp_buff;
            token *token_buffer;
            bool isNumeric;
            auto string_buffer = strlib::stack_split(query);
            for (auto i: *string_buffer) {
                isNumeric = false;
                auto no_op = i;
                try {
                    i = strlib::strToUp(i);
                    auto op = def_token->at(i);
                    token_buffer = new token(i, op);
                } catch (std::exception e) {
                    if (no_op.at(0) >= '0' && no_op.at(0) <= '9') {
                        isNumeric = true;
                    }
                    auto varchar = no_op.find(" $$VARCHAR$$");
                    if (varchar != std::string::npos) {
                        no_op = no_op.substr(0, varchar);
                        token_buffer = new token(no_op, new operand(NOT_OP, VARCHAR));
                    } else if (isNumeric) {
                        token_buffer = new token(no_op, new operand(NOT_OP, NUMERIC));
                    } else {
                        token_buffer = new token(no_op, new operand(NOT_OP, VARNAME));
                    }

                }
                token_plane->push_back(token_buffer);
            }
            parse();
        }


    public:
        Parser(const std::string &query) {
            this->query = query;
            def_token = new std::map<std::string, operand *>();
            init_tokens();
            token_plane = new std::vector<token *>;
            tokenize();
        }
    };


    class Atom {
    public:
        static auto query(const std::string &&rval) -> std::string {
            return rval;
        }
    };
}

#undef make_op
#undef func
#undef let
#endif //DIVEDB__DABI_PARSER_H
