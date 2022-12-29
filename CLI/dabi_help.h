//
// Created by Rufelle on 28/12/2022.
//

#ifndef DIVEDB__DABI_HELP_H
#define DIVEDB__DABI_HELP_H
#include "dabi_macros.h"


auto init_help() -> void {
    std::cout << "Dive Database Management System (DABI)\n(c)2022, Dive Technologies\n" <<
            "Developed by Rufelle Emmanuel Pactol\n" <<
            "\nAbout the DABI CLI\n\tAs of the current phase, the DABI CLI is not built to work outside of the pre-provided DABI APIs.\n" <<
            "\tcurrently, there are plans to develop a developer-friendly interface.\n\n";
    return;
}

#endif //DIVEDB__DABI_HELP_H
