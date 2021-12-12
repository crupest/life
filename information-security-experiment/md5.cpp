#include <openssl/evp.h>

#include <iomanip>
#include <iostream>

int main() {
  EVP_MD_CTX *ctx = EVP_MD_CTX_create();
  EVP_DigestInit_ex(ctx, EVP_md5(), NULL);

  EVP_DigestUpdate(ctx, "abc", 3);

  unsigned char digest[EVP_MAX_MD_SIZE];
  unsigned int digest_size;
  EVP_DigestFinal_ex(ctx, digest, &digest_size);

  EVP_MD_CTX_destroy(ctx);

  std::cout << "MD5 digest of 'abc' is: " << std::hex << std::setfill('0');
  for (unsigned int i = 0; i < digest_size; i++) {
    std::cout << std::setw(2) << (int)digest[i];
  }
  std::cout << std::endl;

  return 0;
}
