#include <iostream>
#include "dabi_help.h"
#include "dabi_fetch.h"
#include "strlib.h"
#include <windows.h>
#include "divefile.h"
#include "dabi_parser.h"

int main (int argc, char ** argv){


   // auto l = "ALTER TABLE (a, \"VARCHAR ALERT\", c)";
   auto l = "SELECT a,z,c,d,r, FROM z ";
    using namespace dabi;
    Parser parse = Parser(l);
    auto a = strlib::stack_split(l);

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
        return 0;
    }

    // fetching commands by parsing command line arguments
    if(!fetch_command(argv[1])){
        fetch_command(argc, argv);
    }


}








#undef let
#undef func