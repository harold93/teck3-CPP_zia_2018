#pragma once

#include "Stage.hpp"

class RespModule
{
    public:
  RespModule() {
    _reqTypes.insert(_reqTypes.end(),
      {"GET", "HEAD", "POST", "PUT", "DELETE", "CONNECT", "OPTIONS"}); 
  };
  ~RespModule() = default;

  dems::Context &getContextRequest(dems::Context &ctx);

private:
  void printRequest(std::string &req);
  void printRequest(std::vector<std::string> &req);
  std::vector<std::string> getRequestParts(std::string &req);
  bool checkRequestSyntax(std::vector<std::string> &reqParts);

  std::vector<std::string> _reqTypes;
};