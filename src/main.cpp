/*
** EPITECH PROJECT, 2019
** zia
** File description:
** main
*/

#include <boost/asio/io_service.hpp>
#include "components/server/Server.h"

int main(int argc, char const *argv[])
{
    boost::asio::io_service io_service;
    Server server(io_service, 1212);

    io_service.run();
    return 0;
}
