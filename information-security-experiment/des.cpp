#include <openssl/des.h>
#include <openssl/evp.h>

#include <cstdlib>
#include <iomanip>
#include <iostream>

void PrintCblock(const DES_cblock &b, bool end_line = true) {
  std::cout << std::hex << std::right << std::setfill('0');

  for (auto c : b) {
    std::cout << std::setw(2) << static_cast<int>(c);
  }

  if (end_line) {
    std::cout << std::endl;
  }
}

int main() {
  auto cipher = EVP_des_cfb();

  std::cout << "Selected cipher: des_cfb" << std::endl;

  auto key_length = EVP_CIPHER_key_length(cipher);
  std::cout << "Key length: " << key_length << std::endl;

  auto iv_length = EVP_CIPHER_iv_length(cipher);
  std::cout << "IV length: " << iv_length << std::endl;

  auto block_length = EVP_CIPHER_block_size(cipher);
  std::cout << "Block length: " << block_length << std::endl;

  DES_cblock key;

  std::srand(std::time(nullptr));

  std::cout << std::hex << std::setfill('0');

  if (DES_random_key(&key) == 0) {
    std::cerr << "Failed to generate key." << std::endl;
    return 1;
  } else {
    std::cout << "Succeeded to generate key." << std::endl;
    std::cout << "Key: ";
    PrintCblock(key);
  }

  DES_key_schedule key_schedule;

  {
    auto result = DES_set_key_checked(&key, &key_schedule);

    if (result == -1) {
      std::cerr << "Parity is wrong." << std::endl;
      return 1;
    } else if (result == -2) {
      std::cerr << "Key is too weak." << std::endl;
    }
  }

  DES_cblock clear_text = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

  std::cout << "Clear text: " << std::hex;
  PrintCblock(clear_text);

  DES_cblock cipher_text;

  DES_ecb_encrypt(&clear_text, &cipher_text, &key_schedule, 1);

  std::cout << "Cipher text after encrypted: " << std::hex;
  PrintCblock(cipher_text);

  DES_ecb_encrypt(&cipher_text, &clear_text, &key_schedule, 0);

  std::cout << "Clear text after decrypted: " << std::hex;
  PrintCblock(clear_text);

  return 0;
}
