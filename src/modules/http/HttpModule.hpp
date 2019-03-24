#pragma once

#include <cstdio>
#include <vector>
#include <string>
#include "Stage.hpp"

class httpModule {

public:
  httpModule() {
    _reqTypes.insert(_reqTypes.end(),
      {"GET", "HEAD", "POST", "PUT", "DELETE", "CONNECT", "OPTIONS"}); 
  };
  ~httpModule() = default;

  dems::Context &getContextRequest(dems::Context &ctx);

private:
  void printRequest(std::string &req);
  void printRequest(std::vector<std::string> &req);
  std::vector<std::string> getRequestParts(std::string &req);
  bool checkRequestSyntax(std::vector<std::string> &reqParts);

  std::vector<std::string> _reqTypes;
};
