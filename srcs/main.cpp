#include "../incl/Server.hpp"

int main(int ac, char **av)
{
    std::string     configFilePath = "webservConfigFileExample.conf";

    if (ac > 1)
        configFilePath = av[1];
    Server(configFilePath);

    return (0);
}