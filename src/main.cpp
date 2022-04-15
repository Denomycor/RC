#include <iostream>
#include <variant>

#include "parser.h"

#ifdef DEBUG
#define log(x) std::cout << "LOG: " << x << std::endl
#else 
#define log(x) 
#endif

int main(int argc, const char** argv){
    auto prog_args = eval_args(argc, argv);
    if(prog_args.index() == 0){
        std::cout << "usage:\nremotec open <port>\nremotec connect <port> <ip> <code>\nremotec offer <port> <ip>" << std::endl;
        return 0;
    }

    log("Arguments correct parsing");

    parsed_args& args = std::get<parsed_args>(prog_args);
    
    if(args.command == commands::OPEN){

    }else if(args.command == commands::CONNECT){

    }else if(args.command == commands::OFFER){

    }else{
        std::cout << "error - unexpected control reached" << std::endl;
        return 0;
    }
}
