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
        std::string path = entry.path().c_str();
        _threadPoll.emplace_back(std::thread(&ManagerServer::runServer, this, path));
    }
    for (auto &thread : _threadPoll) {
        thread.join();
    }
}

void ManagerServer::runServer(std::string path)
{
    std::unique_lock<std::mutex> lk(_locker);
    _parser.parse(path);

    auto &item = _parser.getParams();
    auto it = item.find("port");
    auto modules = _parser.getModules();
    if (it != item.end() && !it->second.empty()) {
        ModulesManager modulesManager;

        std::cout << "\nA server on port: " << it->second << '\n';
        for (auto module : modules) {
            modulesManager.loadOneModule("./sharedModules/" + module + ".so");
        }
        boost::asio::io_service io_service;
        Server server(io_service, modulesManager, std::stoi(it->second));
        lk.unlock();
        io_service.run();
    } else {
        std::cout << "port is missing in file " << path << '\n';
    }
    lk.unlock();
}