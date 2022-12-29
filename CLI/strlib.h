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





namespace strlib {

    // The dive library for easy string and file handling

    using namespace std;
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



}


#endif //DIVEDB__STRLIB_H
