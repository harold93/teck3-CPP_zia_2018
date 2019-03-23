//
// Created by harold Armijo Leon on 2019-03-20.
//

#include <iostream>
#include "Stage.hpp"

static constexpr char MODULE_NAME[] = "Logger";

extern "C" {
    std::string registerHooks(dems::StageManager &manager) {
//        manager.request().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
//            std::cout << "I'm an example module" << std::endl;
//            return dems::CodeStatus::OK;
//        });
        std::cout << " test module log \n";
        return MODULE_NAME;
    }
};
