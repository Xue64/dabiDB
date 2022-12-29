//
// Created by Rufelle on 30/12/2022.
//

#ifndef DIVEDB__DIVEFILE_H
#define DIVEDB__DIVEFILE_H


#include <algorithm>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace dive {
    class FileReader {
        std::string path;
        std::shared_ptr<std::ifstream> input_file;


    public:
        FileReader(std::string path) {
            this->path = path;
            input_file = make_shared<std::ifstream>(path);

        }

        void close() {
            input_file->close();
        }

        auto &get() {
            return input_file;
        }

        auto readLine() {
            auto line = std::make_shared<std::string>("");
            if (input_file->is_open()) {
                std::getline(*input_file, *line);
            }
            return *line;
        }

        auto readFile() {
            auto vector = std::make_shared<std::vector<std::string>>();
            while (this->input_file->good()) {
                vector->push_back(readLine());
            }
            return vector;
        }

        ~FileReader() {
            input_file->close();
        }

    };

    class FileWriter {
        std::shared_ptr<std::ofstream> output_file;
        std::string path;


    public:
        FileWriter(std::string path) {
            this->path = path;
            output_file = std::make_shared<std::ofstream>(path);
        }

        auto &get() {
            return output_file;
        }

        ~FileWriter() {
            output_file->close();
        }


    };
}



#endif //DIVEDB__DIVEFILE_H
