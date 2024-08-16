#include "ArgsCLI.h"

int main(const int argc, char **argv) {
    ArgsCLI my_args;
    my_args.parse(argc, argv);

    return 0;
}
