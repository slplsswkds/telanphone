// import args;
#include <CLI/CLI.hpp>
#include <expected>
#include <regex>
#include <string>

class ArgsCLI {
private:
protected:
public:
    std::string ip; // target ip
    std::string mac; // target MAC
    std::string port; // target port
};

int main(int argc, char **argv) {
    ArgsCLI my_args;

    //------------------- Lambdas -----------
    auto check_mac = [](const std::string &mac_string) {
        const std::regex macRegex("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
        if (!std::regex_match(mac_string, macRegex)) {
            return std::string("Invalid MAC address format");
        }
        return std::string();
    };

    auto check_ipv4 = [](const std::string &ip_string) {
        const std::regex ipv4Regex(
            R"(^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$)"
        );
        if (!std::regex_match(ip_string, ipv4Regex)) {
            return std::string("Invalid IPv4 address format");
        }
        return std::string();
    };

    auto check_port = [](const std::string &port_string) {
        const std::regex portRegex(
            "^([0-9]{1,4}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5])$"
        );
        if (!std::regex_match(port_string, portRegex)) {
            return std::string("Invalid port");
        }
        return std::string();
    };

    //------------------- Parser setup ------
    CLI::App cli_parser{"Tool for client/server calls via (TCP|UDP)/IP like classic telephone"};
    // argv = cli_parser.ensure_utf8(argv);

    cli_parser.add_option("-m, --mac", my_args.mac, "target MAC")
            ->required()
            ->check(check_mac);

    cli_parser.add_option("-i, --ip", my_args.ip, "target ip")
            ->required()
            ->check(check_ipv4);

    cli_parser.add_option("-p, --port", my_args.port, "target port")
            ->required()
            ->check(check_port);

    try {
        cli_parser.parse(argc, argv);
    } catch (const CLI::ParseError &err) {
        return cli_parser.exit(err);
    }
    return 0;
}

//---------------------------------------------------------------------------------------------------------------------
// #include <CLI/CLI.hpp>
// #include <iostream>
// #include <sstream>
// #include <iomanip>
// #include <string>
// #include <regex>
//
// bool isValidMacAddress(const std::string &mac) {
//     // Регулярний вираз для перевірки MAC-адреси у форматі HEX
//     std::regex macRegex("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
//     return std::regex_match(mac, macRegex);
// }
//
// std::array<uint8_t, 6> parseMacAddress(const std::string &mac) {
//     std::array<uint8_t, 6> macBytes;
//     std::stringstream ss(mac);
//     std::string byte;
//     for (int i = 0; i < 6; ++i) {
//         if (std::getline(ss, byte, ':') || std::getline(ss, byte, '-')) {
//             macBytes[i] = static_cast<uint8_t>(std::stoul(byte, nullptr, 16));
//         } else {
//             throw CLI::ValidationError("Invalid MAC address format");
//         }
//     }
//     return macBytes;
// }
//
// int main(int argc, char **argv) {
//     CLI::App app{"MAC Address Parser"};
//
//     std::string mac;
//     app.add_option("-m,--mac", mac, "MAC address in HEX format")->required()
//         ->check([](const std::string &input) {
//             if (!isValidMacAddress(input)) {
//                 return std::string("Invalid MAC address format");
//             }
//             try {
//                 parseMacAddress(input);
//             } catch (...) {
//                 return std::string("Failed to parse MAC address");
//             }
//             return std::string();
//         });
//
//     CLI11_PARSE(app, argc, argv);
//
//     try {
//         auto macBytes = parseMacAddress(mac);
//         std::cout << "Parsed MAC address: ";
//         for (size_t i = 0; i < macBytes.size(); ++i) {
//             std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(macBytes[i]);
//             if (i < macBytes.size() - 1) {
//                 std::cout << ":";
//             }
//         }
//         std::cout << std::endl;
//     } catch (const CLI::ValidationError &e) {
//         std::cerr << e.what() << std::endl;
//         return 1;
//     }
//
//     return 0;
// }
//
