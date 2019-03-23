//
// Created by harold Armijo Leon on 2019-03-13.
//

#ifndef ZIA_MANAGERSERVER_H
#define ZIA_MANAGERSERVER_H

#include <map>
#include <boost/filesystem.hpp>
#include "parseXml.hpp"
#include "ModulesManager.hpp"

class ManagerServer {

public:
    ManagerServer(const std::string);
    ~ManagerServer();
    void init();
private:
    parseXml _parser;
    std::string _pathConfiguration;
    ModulesManager _modulesManager;
};


#endif //ZIA_MANAGERSERVER_H
