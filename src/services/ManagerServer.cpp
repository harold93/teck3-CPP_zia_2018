//
// Created by harold Armijo Leon on 2019-03-13.
//

#include <boost/asio/io_service.hpp>
#include "../components/server/Server.h"
#include "ManagerServer.h++"

ManagerServer::ManagerServer(const std::string path)
    : _pathConfiguration(path)
{}

ManagerServer::~ManagerServer()
{}

void ManagerServer::init()
{
    for (auto &entry : boost::filesystem::directory_iterator(_pathConfiguration)) {
        _parser.parse(entry.path().c_str());

        auto &item = _parser.getParams();
        auto it = item.find("port");
        auto modules = _parser.getModules();
        if (it != item.end() && !it->second.empty()) {
            // run server on thread
            std::cout << "A server on port: " << it->second << '\n';
            for (auto module : modules) {
                _modulesManager.loadOneModule("./sharedModules/" + module + ".so");
            }

            boost::asio::io_service io_service;
            Server server(io_service, std::stoi(it->second));

            io_service.run();
        } else {
            std::cout << "port is missing in file " << entry.path() << '\n';
        }
    }
}
