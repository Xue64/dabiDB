//
// Created by Rufelle on 06/01/2023.
//

#ifndef DIVEDB__TOKEN_H
#define DIVEDB__TOKEN_H


namespace dabi {
    struct operand { // used as a token identifier for the operand
        int data_type;
        int type;
    public:

        operand(int type, int data_type) {
            this->data_type = data_type;
            this->type = type;
        }


        operand() {
            data_type = -99;
            type = -99;
        }
    };

    struct token { // contains the operand, represents the token
        std::string token_name;
        operand *token_operand;

        token(const std::string &token_name, operand *token_operand) {
            this->token_operand = token_operand;
            this->token_name = token_name;
        }

        token() {
            token_name = "DEFAULT_ERROR_MUST_NOT_APPEAR";
            token_operand = new operand();
            delete token_operand;
        }

    };
}

#endif //DIVEDB__TOKEN_H
