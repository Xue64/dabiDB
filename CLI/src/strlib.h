//
// Created by Rufelle on 29/12/2022.
//

#ifndef DIVEDB__STRLIB_H
#define DIVEDB__STRLIB_H
#include <algorithm>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>
#include "dabi_errorhandling.h"
#include <conio.h>





namespace strlib {

    // The dive library for easy string and file handling

    using namespace std;


    bool allSpace (const std::string& str){
        for (auto i : str){
            if (i!=' '){
                return false;
            }
        }
        return true;
    }

    auto stack_split (const string& s){
        size_t stack_counter = 0;
        std::string stack;
        auto res = make_shared<std::vector<std::string>>();
        for (int i = 0; i < s.length(); i++){
            stack.reserve(s.size());
            if (s[i]=='\"'){
                stack_counter++;
                for (i = i+1; i < s.length(); i++){
                    if (s[i]=='\"'){
                        if (s[i-1]!='\\'){
                            stack_counter++;
                            res->push_back(stack);
                            stack.clear();
                            stack.reserve(s.size());
                            i++;
                            break;
                        } else {
                            stack.pop_back();
                            stack.push_back('"');
                            continue;
                        }
                    }
                    stack.push_back(s[i]);
                }
            }
            if (s[i]==' '){
                if (!allSpace(stack)){
                    res->push_back(stack);
                }
                stack.clear();
                stack.reserve(s.size());
                continue;
            }
            stack.push_back(s[i]);
        }
        if (stack_counter%2){
            dabi_err::no_terminating_quote();
        }
        if (!allSpace(stack)){
            res->push_back(stack);
        }
        return res;
    }


    vector <string> split(string s) {
        /*
         * Special use case for the diveDB project
         */
        string token;
        vector<string> res;
        while (s.length()!=0){
            if (s[0]=='\"'){
                s = s.substr(0, s.length()-1);
                auto index = s.find_first_of('\"');
                std::cout << "INDEX IS " << index << std::endl;
                if (index==string::npos){
                    exit(802);
                }
                if (index!=0){
                    if (s[index-1]!='\\'){
                        token = s.substr(0, index-1);
                        if (s.size()!=index){
                            s = s.substr(index+1, s.length() - (index+1));
                        }
                        res.push_back(token);
                    }
                    else {
                        auto temp = s.substr(0, index - 1);
                        temp += '\"';
                        try {
                            s = s.substr(index + 1, s.length() - (index + 1));
                        } catch (std::exception e) {
                            exit(802);
                        }
                        index = s.find('\"');
                        token = s.substr(0, index - 1);
                        if (index >= s.size()) {
                            s = "";
                        } else {
                            s = s.substr(index + 1, s.length() - (index + 1));
                        }
                        token = temp + token;
                        res.push_back(token);
                    }
                }
            } else {
                auto index = s.find_first_of(" ");
                token = s.substr(0, index-1);
                if (index==s.length()-1){
                    if (!token.empty()){
                        res.push_back(token);
                    }
                    return res;
                }
                if (token.empty()){
                    continue;
                }
                s = s.substr(index+1, s.length()-(index+1));
                res.push_back(token);
            }
        }

        return res;
    }

    vector <string> split(string s, string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        vector <string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    }

    auto get_pass (){
        string res;
        char c;
        do{
            c = getch();
            switch(c){
                case 0://special keys. like: arrows, f1-12 etc.
                    getch();//just ignore also the next character.
                    break;
                case 13://enter
                    cout<<endl;
                    break;
                case 8://backspace
                    if(res.length()>0){
                        res.erase(res.end()-1); //remove last character from string
                        cout<<c<<' '<<c;//go back, write space over the character and back again.
                    }
                    break;
                default://regular ascii
                    res += c;//add to string
                    cout<<'*';//print `*`
                    break;
            }
        }while(c!=13);
        return res;
    }


    auto strToUp(std::string str){
        for (int i = 0; i<str.length(); i++){
            str[i] = toupper(str[i]);
        }
        return str;
    }


}


#endif //DIVEDB__STRLIB_H
