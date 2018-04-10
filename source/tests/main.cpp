#include <iostream>
#include "testing.hpp"

void die(unsigned int line, const std::string& message) {
  std::cout<<"[Line: "<<line<<"] "<<message<<"\n";
  exit(1);
}

int main(int argc, char *argv[]) {
  std::cout<<"Starting CGE tests\n";

  std::cout<<"CGE base\n";
  test_cge_base();
  
  return 0;
}
