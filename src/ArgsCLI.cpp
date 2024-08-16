#include "ArgsCLI.h"

void ArgsCLI::setup_checkers() {
    check_mac = [](const std::string &mac_string) {
        const std::regex macRegex("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
        if (!std::regex_match(mac_string, macRegex)) {
            return std::string("Invalid MAC address format");
        }
        return std::string();
    };

    check_ipv4 = [](const std::string &ip_string) {
        const std::regex ipv4Regex(
            R"(^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)"
        );
        if (!std::regex_match(ip_string, ipv4Regex)) {
            return std::string("Invalid IPv4 address format");
        }
        return std::string();
    };

    check_port = [](const std::string &port_string) {
        const std::regex portRegex(
            "^([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$"
        );
        if (!std::regex_match(port_string, portRegex)) {
            return std::string("Invalid port");
        }
        return std::string();
    };
}

void ArgsCLI::setup_parser() {
    cli_parser
            .add_option("-m, --mac", mac, "target MAC")
            ->check(check_mac);

    cli_parser
            .add_option("-i, --ip", ip, "target ip")
            ->required()
            ->check(check_ipv4);

    cli_parser
            .add_option("-p, --port", port, "target port")
            ->required()
            ->check(check_port);

    // parser configuration for app_mode
    const auto server_mode = cli_parser
            .add_flag("-s,--server", [&](int) { app_mode = AppMode::Server; });

    cli_parser
            .add_flag("-c,--client", [&](int) { app_mode = AppMode::Client; })
            ->excludes(server_mode)
            ->description("Run in client mode");
}

ArgsCLI::ArgsCLI() {
    setup_checkers();
    setup_parser();
}

int ArgsCLI::parse(const int argc, char **argv) {
    try {
        cli_parser.parse(argc, argv);
    } catch (const CLI::ParseError &err) {
        return cli_parser.exit(err);
    }
    return 0;
}
