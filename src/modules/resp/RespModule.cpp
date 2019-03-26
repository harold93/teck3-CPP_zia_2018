
#include <iostream>
#include "RespModule.hpp"
#include "HeaderManager.hpp"

static constexpr char MODULE_NAME[] = "resp";

void RespMain(dems::Context &ctx) {
  dems::header::Response res;

  res.httpVersion = "HTTP/1.1";
  res.message = "OK";
  res.statusCode = "200";
  ctx.response.firstLine = res;
  auto head = std::make_unique<HeaderManager>();
  head->setHeader("Content-type", "text/html");
  ctx.response.body = "Zia Project <?php echo 'lol'?>";
  ctx.response.headers = std::move(head);
}


extern "C" {

std::string registerHooks(dems::StageManager &manager)
{
  manager.request().hookToFirst(1, MODULE_NAME, [](dems::Context &ctx) {
    RespMain(ctx);
    return dems::CodeStatus::OK;
  });

//  manager.request().hookToMiddle(0, MODULE_NAME, [](dems::Context &ctx) {
//    std::cout << "Stage: Request MIDDLE" << std::endl;
//    std::cout << ctx.response.body << std::endl;
//    return dems::CodeStatus::OK;
//  });
//
//  manager.request().hookToEnd(0, MODULE_NAME, [](dems::Context &ctx) {
//    std::cout << "Stage: Request END" << std::endl;
//    std::cout << ctx.response.body << std::endl;
//    return dems::CodeStatus::OK;
//  });
//  std::cout << "Resp OK" << '\n';
  return MODULE_NAME;
}
};