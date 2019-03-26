//
// Created by harold Armijo Leon on 2019-03-25.
//

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "Stage.hpp"

static constexpr char MODULE_NAME[] = "php";

static void epurStr(std::string &s) {
    bool space = false;
    auto p = s.begin();
    for (auto ch : s)
        if (std::isspace(ch)) {
            space = p != s.begin();
        } else {
            if (space) *p++ = ' ';
            *p++ = ch;
            space = false;
        }
    s.erase(p, s.end());
}

static dems::CodeStatus runPHP(dems::Context &context)
{
    std::string cmd("echo \"" + context.response.body + "\" | php-cgi");
    int bytesRead = 0;
    char buff[4096];
#ifdef _WIN32
    FILE *fd = _popen(cmd.c_str(), "r");
#else
    FILE *fd = popen(cmd.c_str(), "r");
#endif
    if (fd != NULL) {
        // parse buffer
        std::stringstream ss;
        std::string to;

        while ((bytesRead = fread(buff, sizeof(*buff), 1, fd)))
            ss.write(buff, bytesRead);
        // to set headerq
        while (std::getline(ss, to, '\n')) {
            if (to.size() == 1) {
                break;
            } else {
                epurStr(to);
                std::stringstream parse(to);
                std::string key;
                std::string val;
                std::getline(parse, key, ':');
                std::getline(parse, val, ':');
                context.response.headers->setHeader(key, val);
            }
            to.clear();
        }
        std::getline(ss, to, '\0');
        context.response.body.clear();
        context.response.body = to;
        fclose(fd);
        return dems::CodeStatus::OK;
    }
    return dems::CodeStatus::HTTP_ERROR;
}

extern "C" {
    std::string registerHooks(dems::StageManager &manager) {
        manager.request().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
            return runPHP(ctx);
        });
        return MODULE_NAME;
    }
};