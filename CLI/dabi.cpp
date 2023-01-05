#include <iostream>
#include "dabi_help.h"
#include "dabi_fetch.h"
#include "strlib.h"
#include <windows.h>
#include "divefile.h"
#include "dabi_parser.h"

int main (int argc, char ** argv){

   std::string query;
    auto vector = strlib::stack_split(query);
    for (auto i : *vector){
        std::cout << i << std::endl;
    }

    /*
    {
        using namespace dive;
        auto reader = FileReader("path.testpg");
        auto writer = FileWriter("path.testpg", true);
        std::cout << std::endl;
        auto res = reader.readFile();

        for (int i = 0; i<=1 ; i++){
            writer.writeVector(*res.get());
        }
        for (auto i : *res){
            std::cout << i << std::endl;
        }

    } */
    // default console output
    if (argc==1){
        init_help();
        return 0;
    }

    // fetching commands by parsing command line arguments
    if(!fetch_command(argv[1])){
        fetch_command(argc, argv);
    }


}








#undef let
#undef func