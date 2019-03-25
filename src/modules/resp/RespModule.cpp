
#include <iostream>
#include "RespModule.hpp"
#include "HeaderManager.hpp"

static constexpr char MODULE_NAME[] = "Logger";

void RespMain(dems::Context &ctx) {
  dems::header::Response res;

  //ctx.rawData.push_back("HTTP/1.1");
  //ctx.rawData.clear();  
  res.httpVersion = "HTTP/1.1";
  res.message = "OK";
  res.statusCode = "200";
  ctx.response.body="Zia Project";
  ctx.response.firstLine = res;
  auto head = std::make_unique<HeaderManager>();
  std::cout << head.get() << '\n';
  head->setHeader("accept", "application/json");
  ctx.response.headers = std::move(head);
  std::cout << "head -> " + ctx.response.headers->getHeader("accept") + "\n";
}


extern "C" {

std::string registerHooks(dems::StageManager &manager)
{
  manager.connection().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
    std::cout << "Stage: Request FIRST" << std::endl;
    RespMain(ctx);
    std::cout << ctx.response.body << std::endl;
    return dems::CodeStatus::OK;
  });

  manager.request().hookToMiddle(0, MODULE_NAME, [](dems::Context &ctx) {
    std::cout << "Stage: Request MIDDLE" << std::endl;
    std::cout << ctx.response.body << std::endl;
    return dems::CodeStatus::OK;
  });

  manager.request().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
    std::cout << "Stage: Request END" << std::endl;
    std::cout << ctx.response.body << std::endl;
    return dems::CodeStatus::OK;
  });
  std::cout << "Resp OK" << '\n';
  return MODULE_NAME;
}
};