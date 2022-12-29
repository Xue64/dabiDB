#include <iostream>
#include "dabi_help.h"
#include "dabi_fetch.h"
#include "strlib.h"
#include <windows.h>
#include "divefile.h"


int main (int argc, char ** argv){

    using namespace dive;
    auto file = std::make_unique<FileReader>("mytoken.dabi");
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