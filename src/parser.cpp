#include <variant>
#include <string.h>

#include "parser.h"
#include "helper.h"

std::variant<bool, parsed_args> eval_args(int argc, const char** argv){
    if(argc < 3){
        return false;
    }else{
        commands command = parse_command(argv[1]);
        if(command == commands::OPEN && argc == 3){
            short port = atoi(argv[2]);
            if(port < 1){
                return false;
            } else{
                return parsed_args{.command = command, .myport = port};
            }
            
        }else if(command == commands::CONNECT && argc == 5){
            short myport = atoi(argv[2]);
            auto[ip, port] = parse_ip(argv[3]);
            if(myport < 1 || port < 1 || ip == ""){
                return false;
            }else{
                return parsed_args{command, myport, port, std::move(ip), std::string_view(argv[4])};
            }

        }else if(command == commands::OFFER && argc == 4){
            short myport = atoi(argv[2]);
            auto[ip, port] = parse_ip(argv[3]);
            if(myport < 1 || port < 1 || ip == ""){
                return false;
            }else{
                return parsed_args{command, myport, port, std::move(ip)};
            }
        }else{
            return false;
        }
    }
}

std::pair<std::string, short> parse_ip(const char* ip){
    bool point = true;
    for(size_t i=0; i<strlen(ip); i++){
        if(is_digit(ip[i])){
            point = false;
        }else if(ip[i] == '.' && !point){
            point = true;
        }else if(ip[i] == ':'){
            return {std::string(ip, i), atoi(ip+i+1)};
        }else{
            return {"", -1};
        }
    }
    return {"", -1};
}

commands parse_command(const char* command){
    if(!strcmp(command, "open")){
        return commands::OPEN;
    }else if(!strcmp(command, "connect")){
        return commands::CONNECT;
    }else if(!strcmp(command, "offer")){
        return commands::OFFER;
    }else{
        return commands::NONE;
    }
}