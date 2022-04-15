#pragma once

#include <string>
#include <string_view>
#include <variant>

enum class commands : unsigned int {
    NONE, OPEN, CONNECT, OFFER
};

struct parsed_args{
    commands command;
    short myport, otherport;
    std::string ip;
    std::string_view code;
};

std::variant<bool, parsed_args> eval_args(int argc, const char** argv);

std::pair<std::string, short> parse_ip(const char* ip);

commands parse_command(const char* command);
