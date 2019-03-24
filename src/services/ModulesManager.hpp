//
// Created by harold Armijo Leon on 2019-03-18.
//

#ifndef ZIA_MODULESMANAGER_HPP
#define ZIA_MODULESMANAGER_HPP

#include "AModulesManager.hpp"

class ModulesManager : public dems::AModulesManager {
public:
    using TypeRegisterHooks = std::string (*)(dems::StageManager &);

    void loadModules(const std::string &directoryPath) override;
    void loadOneModule(const std::string &filePath) override;
    void unloadModule(const std::string &moduleName) override;
    void callHooksConnection(int);
//    void callHooksRequest(std::array<char, 8000>);
    void callHooksRequest(const char *);
    void callHooksDisconnection();
    const std::string getData() noexcept;
private:
    dems::Context _context;
};

#endif //ZIA_MODULESMANAGER_HPP
