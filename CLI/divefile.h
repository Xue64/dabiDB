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

    /**
     *
     *
     * @brief   This class is a proxy class for the CPP @c std::istream class.
     *
     * @author  Rufelle Emmanuel Pactol, Dive
     * @version 1.0
     * @since   30-12-22
     */
    class FileReader {
        std::string path;
        std::shared_ptr<std::ifstream> input_file;


    public:
        /**
         *
         *
         * @brief The @c dive::FileReder() default constructor.
         * @params path contains the file's path.
         */
        FileReader(std::string path) {
            this->path = path;
            input_file = std::make_shared<std::ifstream>(path);

        }

        /**
         *
         *
         * @brief Closes the file.
         * @warning Manually closing this file will call the object destructor.
         */
        void close() {
            delete this;
        }

        /**
         *
         *
         * @brief This methods retrieves the raw @c std::ifstream object.
         * @returns A reference to the @c std::ifstream object.
         */
        auto &get() {
            return input_file;
        }

        /**
         *
         * @brief Reads a single line of the given file.
         * @return Returns a @c std::string containing the line.
         */
        auto readLine() {
            std::string line = "";
            if (input_file->is_open()) {
                std::getline(*input_file, line);
            }
            return line;
        }

        /**
         *
         *
         * @brief Stores the remaining file lines in an @c std::vector<std::string> .
         * @return Returns a @c std::shared_ptr of @c std::vector of @c std::string containing the remaining lines inside the file.
         * @warning Using @c readLine() prior to this method will cause the returned vector to not return the whole file but instead return the lines not yet read by @c readLine() . If you are unsure if you have triggered @c readLine() prior to this method and would like to include the whole file in the vector, invoke the @c resetFile() method first.
         * @warning Using this method will exhaust the file lines. Use the @c resetFile() method to reset the file's lines.
         */
        auto readFile() {
            auto vector = std::make_shared<std::vector<std::string>>();
            while (this->input_file->good()) {
                vector->push_back(readLine());
            }
            return vector;
        }

        /**
         * @brief Resets the internal @c std::ifstream object to read the whole file again. This resets the exhausted lines that may be used up by the @c readLine() and @c readFile() methods.
         * @return A boolean which returns true if the file has been successfully reset.
         */
        auto resetFile(){
            input_file->close();
            input_file = std::make_shared<std::ifstream>(path);
            return true;
        }

        /**
         *
         * @return A boolean which returns true if the file is open.
         */
        auto isOpen(){
            return input_file->is_open();
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
