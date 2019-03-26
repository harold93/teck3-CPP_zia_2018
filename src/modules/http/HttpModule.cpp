#include <iostream>
#include "HttpModule.hpp"

static constexpr char MODULE_NAME[] = "http";

std::vector<std::string> httpModule::getRequestParts(std::string &req)
{
  std::vector<std::string> reqParts;
  std::string delim = " ";
  size_t pos = 0;
  std::string token;

  while ((pos = req.find(delim)) != std::string::npos) {
    reqParts.push_back(req.substr(0, pos));
    req.erase(0, pos + delim.length());
  }
  reqParts.push_back(req);
  printRequest(reqParts);
  if (checkRequestSyntax(reqParts) == false)
    reqParts.clear();
  return reqParts;
}

bool httpModule::checkRequestSyntax(std::vector<std::string> &reqParts)
{
  auto i = _reqTypes.begin();

  if (reqParts.size() != 3) {
    return false;
  }
  while (i != _reqTypes.end() && reqParts[0] != *i)
    i++;
  if (i == _reqTypes.end()) {
    return false;
  }
  return true;
}

dems::Context &httpModule::getContextRequest(dems::Context &ctx)
{
  std::string reqStr(ctx.rawData.begin(), ctx.rawData.end());
  std::vector<std::string> reqParts = getRequestParts(reqStr);
  if (reqParts.size() != 3)
    return ctx;
  dems::header::Request req;
  req.method = reqParts[0];
  req.path = reqParts[1];
  req.httpVersion = reqParts[2];
  ctx.request.firstLine = req;
  return ctx;
}

void httpModule::printRequest(std::vector<std::string> &req)
{
  auto i = req.begin();
  while (i != req.end()) {
    i++;
  }
}

void HttpMain(dems::Context &ctx){
    httpModule http;

    http.getContextRequest(ctx);
}

extern "C" {

std::string registerHooks(dems::StageManager &manager)
{
  manager.request().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
    HttpMain(ctx);
//    std::cout << ctx.response.body << std::endl;
    return dems::CodeStatus::OK;
  });
//
//  manager.request().hookToMiddle(0, MODULE_NAME, [](dems::Context &ctx) {
//    std::cout << ctx.response.body << std::endl;
//    return dems::CodeStatus::OK;
//  });
//
//  manager.request().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
//    std::cout << ctx.response.body << std::endl;
//    return dems::CodeStatus::OK;
//  });
//  std::cout << "Http OK" << '\n';
  return MODULE_NAME;
}
};