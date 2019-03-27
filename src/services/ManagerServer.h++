//
// Created by harold Armijo Leon on 2019-03-13.
//

#ifndef ZIA_MANAGERSERVER_H
#define ZIA_MANAGERSERVER_H

#include <mutex>
#include <map>
#include <boost/filesystem.hpp>
#include <thread>
#include "parseXml.hpp"
#include "ModulesManager.hpp"

class ManagerServer {

public:
    ManagerServer(const std::string);
    ~ManagerServer();
    void init();
private:
    void runServer(std::string);
    parseXml _parser;
    std::string _pathConfiguration;
    std::vector<std::thread> _threadPoll;
    std::mutex _locker;
//    ModulesManager _modulesManager;
};


#endif //ZIA_MANAGERSERVER_H
