#ifndef ARGSCLI_H
#define ARGSCLI_H

#include <CLI/CLI.hpp>
#include <regex>
#include <string>

enum AppMode {
    Server,
    Client
};

class ArgsCLI {
private:
    CLI::App cli_parser{"Tool for client/server calls via (TCP|UDP)/IP like classic telephone"};

    void setup_checkers(); ///< configure lambdas that use to validate arguments
    void setup_parser();

    std::function<std::string(const std::string &)> check_mac;
    std::function<std::string(const std::string &)> check_ipv4;
    std::function<std::string(const std::string &)> check_port;

public:
    AppMode app_mode;
    std::string ip; // target ip. Required
    std::string mac; // target MAC. Optional (For WOL)
    std::string port; // target port. Temporarily required.

    ArgsCLI();

    int parse(int argc, char **argv);
};

#endif //ARGSCLI_H
