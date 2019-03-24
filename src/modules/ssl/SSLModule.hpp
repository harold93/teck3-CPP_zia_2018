
#ifndef SSL_MODULE
# define SSL_MODULE
#include "Stage.hpp"

#include <openssl/ssl.h>
#include <openssl/err.h>

/* 
**  SSLModule 
*/

class SSLModule {
public:
  SSLModule() {
    // Open error
    SSL_load_error_strings();
    // initialize ssl algo
    OpenSSL_add_ssl_algorithms();
    createCtx();
    configSSL();
  };
  ~SSLModule() {
    EVP_cleanup();
  };
  void createCtx();
  void configSSL();
  void initClient(dems::Context &ctx);
  void launchSSL(SSL *ssl, dems::Context &ctx);

private:
  SSL_CTX *_ctx;
};

#endif //f SSL_MODULE