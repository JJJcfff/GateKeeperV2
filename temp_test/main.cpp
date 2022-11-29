#include <iostream>
#include <ctime>
#include <chrono>
#include <cmath>



int main() {
  struct std::tm a = {0,0,0,5,0,70}; // Monday, January 5th 1970 at 00:00:00
  std::time_t x = std::mktime(&a);
  std::time_t y = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
  double difference = std::difftime(y, x) / (60 * 60 * 24 * 7);
  std::string weeks = std::to_string(std::round(difference));
  std::string salt = "09e1cda686f8a1b1";

  std::cout << "Weeks since 1970: " << weeks << std::endl;

  return 0;
}
