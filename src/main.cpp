/*
** EPITECH PROJECT, 2019
** zia
** File description:
** main
*/

#include "parseXml.hpp"
#include "services/ManagerServer.h++"

int main(int ac, const char **av)
{
    (void)av;
    if (ac != 1)
        return 84;
    try {
        ManagerServer manager("conf");

        manager.init();
    } catch (const std::exception& e) {
         std::cout << e.what() << '\n';
         return 78;
    }
    return 0;
}

//#include <boost/asio/io_service.hpp>
//#include "components/server/Server.h"
//
//int main(int argc, char const *argv[])
//{
//    boost::asio::io_service io_service;
//    Server server(io_service, 1212);
//
//    io_service.run();
//    return 0;
//}
