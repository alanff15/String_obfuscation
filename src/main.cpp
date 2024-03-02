#include <iostream>
#include "StringObfuscator.h"

int main() {
  auto str1 = OBF_STR("you cannot find this text!");  // if you open the compiled executable with a text reader
  auto str2 = "but this one you can!";

  std::cout << DEOBF_STR(str1) << std::endl;
  std::cout << str2 << std::endl;

  return EXIT_SUCCESS;
}