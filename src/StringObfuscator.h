#pragma once
#include <array>

/// @brief Used to obfuscate a string
/// @param str receives a const char* string
/// @return returns a StringObfuscator object
#define OBF_STR(str) StringObfuscator<std::make_index_sequence<sizeof(str)>>(str)

/// @brief Used to deobfuscate a string
/// @param str receives a StringObfuscator object
/// @return returns a const char* string
#define DEOBF_STR(str) static_cast<const char*>(str.read())

// StringObfuscator class definition
template <typename I>
struct StringObfuscator;

template <size_t... I>
class StringObfuscator<std::index_sequence<I...>> {
public:
  constexpr static char encrypt(char c) { return (c + 0x7F) ^ 0xA5; }
  constexpr static char decrypt(char c) { return (c ^ 0xA5) - 0x7F; }
  constexpr explicit __forceinline StringObfuscator(const char* str) : decrypted{false}, buf{encrypt(str[I])...} {}
  inline const char* read() {
    if (!decrypted) {
      for (size_t i = 0; i < sizeof...(I); ++i) buf[i] = decrypt(buf[i]);
      buf[sizeof...(I)] = '\0';
      decrypted = true;
    }
    return buf.data();
  }

private:
  std::array<char, sizeof...(I) + 1> buf;
  bool decrypted;
};