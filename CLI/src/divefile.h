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
#include <memory>

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
         * @brief The @c dive::FileReader() default constructor.
         * @params path contains the file's path.
         */
        FileReader(const std::string& path) {
            this->path = path;
            input_file = std::make_shared<std::ifstream>(path);

        }

        /**
         *
         *
         * @brief Closes the file.
         * @warning Manually closing this file will call the object destructor.
         * @warning Unless absolutely necessary, do not close this file manually. Upon calling this object's destructor, the file will be closed automatically.
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


        /**
         * Deletes the class and closes the internal file.
         */
        ~FileReader() {
            input_file->close();
        }

    };

    class FileWriter {
        std::shared_ptr<std::ofstream> output_file;
        std::string path;
        bool append;


    public:
        /**
         * @brief FileWriter's default constructor.
         * @param path used for determining the path to the file.
         */
        FileWriter(const std::string& path) {
            this->path = path;
            output_file = std::make_shared<std::ofstream>(path);
            this->append = false;
        }

        /**
         *
         *
         * @param path the path to the file to write
         * @param append append mode; set true if you want to append
         */
        FileWriter(const std::string& path, const bool& append){
            this->append = append;
            this->path = path;
            if (!append){
                output_file = std::make_shared<std::ofstream>(path);
                return;
            }
            output_file = std::make_shared<std::ofstream>(path, std::ios::app);
        }


        /**
         *
         *
         * @brief Set the append status of the current file.
         * @param append set to true to turn on append mode.
         */
        void setAppend(const bool& append){
            this->append = append;
            if (append){
                output_file = std::make_shared<std::ofstream>(path, std::ios::app);
                return;
            } std::make_shared<std::ofstream>(path);
        }

        /**
         *
         * @param line The string to write to the file. Will append if append was set to true.
         * @return Returns a bool that returns true if process was successful.
         */
        bool writeLine(const std::string& line){
            *output_file << line;
            return true;
        }

        /**
         *
         *
         * @brief Takes a vector and writes it to the file. Each string will be appended with a newline.
         * @param std::vector<std::string>
         * @return Returns true if the operation is successful.
         */
        bool writeVector(const std::vector<std::string> &vector){
            int ctr = 1;
            for (auto i : vector){
                if (ctr==5){
                    output_file->flush();
                    ctr = 0;
                }
                ctr++;
                *output_file << i << std::endl;
            }
            output_file->flush();
            return true;
        }

        /**
         *
         *
         * @brief Takes a vector and writes it to the file. Each string will be appended with the specified delimiter.
         * @param std::vector<std::string>
         * @param std::string delimiter Specifies how to end each line in-between strings.
         * @return Returns true if the operation is successful.
         */
        bool writeVector(const std::vector<std::string> &vector, const std::string &delimiter){
            if (append){
                for (auto i : vector){
                    *output_file << i << delimiter;
                } return true;
            }
            setAppend(true);
            for (auto i: vector){
                *output_file << i << delimiter;
            }
            append = false;
            return true;
        }

        /**
         *
         *
         * @brief This methods retrieves the raw @c std::ofstream object.
         * @returns A reference to the @c std::ofstream object.
         */
        auto &get() {
            return output_file;
        }

        /**
         *
         * @return Returns true if file is open.
         */
        bool isOpen(){
            return output_file->is_open();
        }

        /**
         *
         * @return Returns true if file has append mode enabled.
         */
        bool isAppend(){
            return append;
        }

        /**
         *
         *
         * @brief Closes the file.
         * @warning Manually closing this file will call the object destructor.
         * @warning Unless absolutely necessary, do not close this file manually. Upon calling this object's destructor, the file will be closed automatically.
         */
        void close(){
            delete this;
        }

        /**
         * @brief Flushes the file buffer.
         */
        void flush(){
            output_file->flush();
        }

        ~FileWriter() {
            output_file->close();
        }


    };
}



#endif //DIVEDB__DIVEFILE_H
