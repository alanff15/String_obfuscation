#include <iostream>
#include <array>

template <typename I>
struct encrypted_string;

template <size_t... I>
class encrypted_string<std::index_sequence<I...>> {
public:
  constexpr static char encrypt(char c) { return c ^ 0xA5; }
  constexpr static char decrypt(char c) { return encrypt(c); }
  constexpr explicit __forceinline encrypted_string(const char* str) : decrypted{false}, buf{encrypt(str[I])...} {}
  inline const char* read() {
    if (!decrypted) {
      for (size_t i = 0; i < sizeof...(I); ++i) buf[i] = decrypt(buf[i]);
      buf[sizeof...(I)] = 0;
      decrypted = true;
    }
    return buf.data();
  }

private:
  std::array<char, sizeof...(I) + 1> buf;
  bool decrypted;
};
#define OBF_STR(str) encrypted_string<std::make_index_sequence<sizeof(str)>>(str)

int main() {
  auto str1 = OBF_STR("you cannot find this text!");  // if you open the compiled executable with a text reader
  std::string str2 = "but this one you can!";

  std::cout << str1.read() << std::endl;
  std::cout << str1.read() << std::endl;
  std::cout << str2 << std::endl;

  return EXIT_SUCCESS;
}