#include <openssl/evp.h>
#include <openssl/rsa.h>

#include <iomanip>
#include <iostream>
#include <vector>

int main() {

  auto ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, nullptr);
  EVP_PKEY *pkey = NULL;
  EVP_PKEY_keygen_init(ctx);
  EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048);
  EVP_PKEY_keygen(ctx, &pkey);
  EVP_PKEY_CTX_free(ctx);
  ctx = nullptr;

  unsigned char cleartext[] = "abc";
  int cleartext_size = sizeof(cleartext) / sizeof(cleartext[0]);

  EVP_MD_CTX *md_ctx = EVP_MD_CTX_create();
  EVP_DigestInit_ex(md_ctx, EVP_sha256(), NULL);
  EVP_DigestUpdate(md_ctx, cleartext, cleartext_size);
  unsigned char digest[EVP_MAX_MD_SIZE];
  unsigned int digest_size;
  EVP_DigestFinal_ex(md_ctx, digest, &digest_size);
  EVP_MD_CTX_destroy(md_ctx);
  md_ctx = nullptr;
  std::cout << "SHA256 digest of 'abc' is: " << std::hex << std::setfill('0');
  for (unsigned int i = 0; i < digest_size; i++) {
    std::cout << std::setw(2) << (int)digest[i];
  }
  std::cout << std::endl;

  std::vector<unsigned char> sig;
  size_t sig_len;

  ctx = EVP_PKEY_CTX_new(pkey, nullptr);
  EVP_PKEY_sign_init(ctx);
  EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING);
  EVP_PKEY_sign(ctx, nullptr, &sig_len, digest, digest_size);
  sig.resize(sig_len);
  EVP_PKEY_sign(ctx, sig.data(), &sig_len, digest, digest_size);
  EVP_PKEY_CTX_free(ctx);

  std::cout << "Signature: " << std::hex << std::setfill('0');
  for (auto c : sig) {
    std::cout << std::setw(2) << static_cast<int>(c);
  }
  std::cout << std::endl;

  ctx = EVP_PKEY_CTX_new(pkey, nullptr);
  EVP_PKEY_verify_init(ctx);
  EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING);
  auto result = EVP_PKEY_verify(ctx, sig.data(), sig_len, digest, digest_size);
  if (result == 1) {
    std::cout << "Verification succeeded." << std::endl;
  } else if (result == 0) {
    std::cout << "Verification failed." << std::endl;
  } else {
    std::cerr << "Verification error." << std::endl;
  }

  return 0;
}