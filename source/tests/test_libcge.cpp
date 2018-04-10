#include <iostream>

#include <cge/cge.hpp>

#include "testing.hpp"

void test_grabbed(const std::string& str) {
  if(str == "UNKNOWN") {
    std::cout<<" Failed\n";
    die(__LINE__, "Failed to grab string correctly");
  }
  std::cout<<" Success\n";
}

const std::string& test_get(const std::string& name) {
  std::cout<<"Getting string '"<<name<<"'";
  return cge::registry::get(name);
}

void test_cge_base() {
  std::cout<<"Testing registry\n";
  test_grabbed(test_get("cge-version-major"));
  test_grabbed(test_get("cge-version-minor"));
  test_grabbed(test_get("cge-version-flair"));
  
  std::cout<<"Testing registry values\n";
  std::cout<<"Using CGE Version "
	   <<cge::registry::get("cge-version-major")<<"."
	   <<cge::registry::get("cge-version-minor")<<"-"
	   <<cge::registry::get("cge-version-flair")<<"\n";
}
