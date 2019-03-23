//
// Created by harold Armijo Leon on 2019-03-18.
//

#include <iostream>
#include <dlfcn.h>
#include "ModulesManager.hpp"

void ModulesManager::loadModules(const std::string &directoryPath)
{}

void ModulesManager::loadOneModule(const std::string &filePath)
{
    std::cout << "load: " << filePath.c_str() << '\n';
    void* handle = dlopen(filePath.c_str(), RTLD_LAZY);
    auto registerHooks = (TypeRegisterHooks)dlsym(handle, "registerHooks");
    registerHooks(stageManager_);
}

void ModulesManager::unloadModule(const std::string &moduleName)
{}

