
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "./SSLModule.hpp"

static constexpr char MODULE_NAME[] = "ssl";

void SSLModule::createCtx()
{
  std::cout << "Create cont" << '\n';
  const SSL_METHOD *method;
  SSL_CTX *ctx;

  method = SSLv23_server_method();

  if (!(ctx = SSL_CTX_new(method))) {
    ERR_print_errors_fp(stderr);
    exit(84);
  }
  _ctx = ctx;
}

void SSLModule::configSSL()
{
  SSL_CTX_set_ecdh_auto(_ctx, 1);

  if (SSL_CTX_use_certificate_file(_ctx, "ssl/cert.pem", SSL_FILETYPE_PEM) <= 0) {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }

  if (SSL_CTX_use_PrivateKey_file(_ctx, "ssl/key.pem", SSL_FILETYPE_PEM) <= 0) {
    ERR_print_errors_fp(stderr);
    exit(EXIT_FAILURE);
  }
}

void SSLModule::launchSSL(SSL *ssl, dems::Context &ctx) {
    const int rdSize = 4096;
    int total = 0;
    int rd = 0;

    std::cout << "reading rawDATA" << std::endl;
    ctx.rawData.resize(ctx.rawData.size() + rdSize);
    rd = SSL_read(ssl, ctx.rawData.data() + total, rdSize);
    if (rd < 0)
        if (rd < rdSize && rd > 0)
            ctx.rawData.resize(ctx.rawData.size() - (rdSize - rd));
    total += rd;
    while (rd == rdSize) {
        std::cout << "reading rawDATA" << std::endl;
        ctx.rawData.resize(ctx.rawData.size() + rdSize);
        rd = SSL_read(ssl, ctx.rawData.data() + total, rdSize);
        if (rd < 0)
            if (rd < rdSize && rd > 0)
              ctx.rawData.resize(ctx.rawData.size() - (rdSize - rd));
        total += rd;
    }
    for (auto r : ctx.rawData)
        std::cout << "print raw data: " << r << std::endl;
    std::cout << "done reading data\n";
    SSL_free(ssl);
}

void SSLModule::initClient(dems::Context &ctx)
{
    int ret = 0;
    SSL *ssl = SSL_new(_ctx);
    SSL_set_fd(ssl, ctx.socketFd);
    
  if ((ret = SSL_accept(ssl)) <= 0) {
    int err = SSL_get_error(ssl, ret);
    std::cerr << "SSL_accept return: " << ret << std::endl;
    std::cerr << "ERROR: " << err << std::endl;
    if (err == SSL_ERROR_WANT_READ) {
      std::cout << "wait for data to read" << std::endl;
    }
    else if (err == SSL_ERROR_WANT_WRITE) {
      std::cout << "wait for data to write" << std::endl;
    }
    else if (err == SSL_ERROR_SYSCALL) {
      std::cout << "syscall error" << std::endl;
      //exit(84);
    }
    else if (err == SSL_ERROR_SSL) {
      ERR_print_errors_fp(stderr);
      std::cout << "SSL ERROR" << std::endl;
    }
    else if (err == SSL_ERROR_ZERO_RETURN) {
      std::cout << "zero return" << std::endl;
      exit(84);
    }
  }
  else {
      launchSSL(ssl, ctx);
  }
   
}


void SSLMain(dems::Context &ctx)
{
  SSLModule module;

  module.initClient(ctx);
}

extern "C" {

std::string registerHooks(dems::StageManager &manager)
{
  manager.connection().hookToFirst(0, MODULE_NAME, [](dems::Context &ctx) {
    std::cout << "Stage: Request FIRST" << std::endl;
    SSLMain(ctx);
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
  std::cout << "SSL OK" << '\n';
  return MODULE_NAME;
}
};