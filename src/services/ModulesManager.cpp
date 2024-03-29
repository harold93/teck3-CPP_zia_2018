//
// Created by harold Armijo Leon on 2019-03-18.
//

#include <iostream>
#include <dlfcn.h>
#include "ModulesManager.hpp"

void ModulesManager::loadModules(const std::string &/*directoryPath*/)
{}

void ModulesManager::loadOneModule(const std::string &filePath)
{
    void* handle = dlopen(filePath.c_str(), RTLD_LAZY);
    if (handle == NULL) {
        std::cout << "error when loading: " << filePath.c_str() << '\n';
        return;
    }
    auto registerHooks = (TypeRegisterHooks)dlsym(handle, "registerHooks");
    if (registerHooks == NULL) {
        std::cout << "error when loading: registerHooks from " << filePath.c_str() << '\n';
        return;
    } else {
        std::cout << "loading: " << filePath.c_str() << '\n';
        registerHooks(stageManager_);

        dems::config::ConfigValue config;
        config.v = "none";
        _context.config[filePath] = config;
    }
}

void ModulesManager::unloadModule(const std::string &/*moduleName*/)
{}

void ModulesManager::callHooksConnection(int socket)
{
    _context.socketFd = socket;
    for (auto &[idx, hook] : stageManager_.connection().firstHooks()) {
        hook.callback(_context);
    }
    for (auto &[idx, hook] : stageManager_.connection().middleHooks()) {
        hook.callback(_context);
    }
    for (auto &[idx, hook] : stageManager_.connection().endHooks()) {
        hook.callback(_context);
    }
}

//void ModulesManager::callHooksRequest(std::array<char, 8000> buffer)
//{
//}

void ModulesManager::callHooksRequest(const char *buffer)
{
    for (int i = 0; buffer[i]; ++i) {
        _context.rawData.push_back((uint8_t)buffer[i]);
    }

    for (auto &[idx, hook] : stageManager_.request().firstHooks()) {
        hook.callback(_context);
    }
    for (auto &[idx, hook] : stageManager_.request().middleHooks()) {
        hook.callback(_context);
    }
    for (auto &[idx, hook] : stageManager_.request().endHooks()) {
        hook.callback(_context);
    }
}

void ModulesManager::callHooksDisconnection()
{
    for (auto &[idx, hook] : stageManager_.disconnect().firstHooks()) {
        hook.callback(_context);
    }
    for (auto &[idx, hook] : stageManager_.disconnect().middleHooks()) {
        hook.callback(_context);
    }
    for (auto &[idx, hook] : stageManager_.disconnect().endHooks()) {
        hook.callback(_context);
    }
}

const std::string ModulesManager::getData() noexcept
{
    std::string data;

//    // test response
//    _context.rawData.clear();
//    std::string test = "HTTP/1.1 200 OK\nServer: Zia\n\nhello world from rawData";
//    for (auto &&c : test) {
//        _context.rawData.push_back((u_int8_t)c);
//    }

////  send data from rawData
//    for (auto &&c : _context.rawData) {
//        data.push_back(c);
//    }

    //send data from header::HTTPMessage response
    auto entry = _context.config.find("./sharedModules/resp.so");
    if (entry == _context.config.end()) {
        data = "HTTP/1.1 200 OK\nServer: Zia\n\nyou must enable module resp ";
        data += "if you want to see our website ! (In the file of configuration placed in folder ./conf";
    } else {
        dems::header::Response  firstLine = std::get<dems::header::Response>(_context.response.firstLine);
        data += firstLine.httpVersion + ' ' + firstLine.statusCode + ' ' + firstLine.message + '\n';
        data += _context.response.headers->getWholeHeaders() + '\n';
        data += _context.response.body;
    }
    return data;
}