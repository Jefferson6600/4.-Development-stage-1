#include "CommandLineInterface.h"
#include "Server.h"

int main(int argc, char* argv[]) {
    CommandLineInterface cli;
    if (!cli.parseArgs(argc, argv)) {
        return 0;
    }

    Server server(cli.getDbFile(), cli.getLogFile(), cli.getPort());
    server.start();
    return 0;
}
