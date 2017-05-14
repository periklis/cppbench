#define _LIBCPP_DEBUG 1
#include <string>

int main() {
  std::__libcpp_debug_function = std::__libcpp_throw_debug_function;
  try {
    std::string::iterator bad_it;
    std::string str("hello world");
    str.insert(bad_it, '!'); // causes debug assertion
  } catch (std::__libcpp_debug_exception const&) {
    return EXIT_SUCCESS;
  }
  return EXIT_FAILURE;
}
