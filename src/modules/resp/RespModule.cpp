
#include <iostream>
#include <fstream>
#include "RespModule.hpp"
#include "HeaderManager.hpp"


static constexpr char MODULE_NAME[] = "resp";

std::vector<std::string> RespModule::getRequestParts(std::string &req)
{
  std::vector<std::string> reqParts;
  std::string delim = "\n";
  size_t pos = 0;

  while ((pos = req.find(delim)) != std::string::npos) {
    reqParts.push_back(req.substr(0, pos));
    req.erase(0, pos + delim.length());
  }
  reqParts.push_back(req);
  /* for(auto i : reqP)
  {
    /* code */
  return reqParts;
}

bool RespModule::checkRequestSyntax(std::vector<std::string> &reqParts)
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


dems::Context &RespModule::getContextRequest(dems::Context &ctx)
{
  dems::header::Request req;
  std::vector<std::string> head;
  std::string reqStr(ctx.rawData.begin(), ctx.rawData.end());
  ctx.rawData.clear();
  std::vector<std::string> reqParts = getRequestParts(reqStr);
  std::string delim = " ";
  size_t pos = 0;

  while ((pos = reqParts[0].find(delim)) != std::string::npos) {
    head.push_back(reqParts[0].substr(0, pos));
    reqParts[0].erase(0, pos + delim.length());
  }
  req.method = head[0];
  if (head.size() == 1) {
    req.httpVersion = reqParts[0];
    req.path = "/index.html";
  }
  else {
    if ((req.path = head[1]) == "/")
      req.path = "/index.html";
    req.httpVersion = reqParts[0];
  }

  ctx.request.firstLine = req;
  return ctx;
}

void RespModule::printRequest(std::vector<std::string> &req)
{
  auto i = req.begin();
  while (i != req.end()) {
    i++;
  }
}


void RespMain(dems::Context &ctx) {
  dems::header::Response res;
  RespModule http;

  http.getContextRequest(ctx);

  //ctx.rawData.push_back("HTTP/1.1");
  //ctx.rawData.clear();
  res.statusCode = "200";
  std::string body;
  std::ifstream myfile("./www" + std::get<0>(ctx.request.firstLine).path);
  if (myfile.is_open())
  {
    body = std::string((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());
    std::cout << body << '\n';
    myfile.close();
  }
  else {    
    std::ifstream err("./www/404.html");
   if (err.is_open())
    {
      body = std::string((std::istreambuf_iterator<char>(err)), std::istreambuf_iterator<char>());
      std::cout << body << '\n';
      res.statusCode = "404";
      myfile.close();
    }
    
  }
  res.httpVersion = "HTTP/1.1";
  res.message = "Zia server";
  ctx.response.body = body;
  ctx.response.firstLine = res;
  auto head = std::make_unique<HeaderManager>();
  head->setHeader("Content-type", "text/html");
  ctx.response.headers = std::move(head);
}


extern "C" {

std::string registerHooks(dems::StageManager &manager)
{
  manager.request().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
    std::cout << "Stage: Request MIDDLE" << std::endl;
      RespMain(ctx);
    std::cout << ctx.response.body << std::endl;
    return dems::CodeStatus::OK;
  });
  std::cout << "Resp OK" << '\n';
  return MODULE_NAME;
}
};