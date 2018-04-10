#include <iostream>

#include <cge/cge.hpp>

#include "testing.hpp"

// Helper functions //

const std::string& test_get(const std::string& name) {
  std::cout<<"Getting string '"<<name<<"'";
  return cge::reg::get(name);
}

// Testing functions //

void test_grabbed(const std::string& str) {
  if(str == "UNKNOWN") {
    std::cout<<" Failed\n";
    die(__LINE__, "Failed to grab string correctly");
  }
  std::cout<<" : '"<<str<<"' : Success\n";
}

void test_put(const std::string& name, const std::string& value) {
  std::cout<<"Putting string '"<<name<<"' as '"<<value<<"'\n";

  unsigned int val = cge::reg::put(name, value);
  
  if(test_get(name) != value || val == CGE_REG_FAILED) {
    std::cout<<" Failed\n";
    die(__LINE__, "Failed to put string correctly");
  }

  std::cout<<" Success\n";
}

void test_cge_base() {
  std::cout<<"Testing registry\n";
  test_grabbed(test_get("cge-version-major"));
  test_grabbed(test_get("cge-version-minor"));
  test_grabbed(test_get("cge-version-flair"));
  
  std::cout<<"\nTesting registry values\n";
  std::cout<<"Using CGE Version "
	   <<cge::reg::get("cge-version-major")<<"."
	   <<cge::reg::get("cge-version-minor")<<"-"
	   <<cge::reg::get("cge-version-flair")<<"\n";
  std::cout<<"Clearly Unknown : "<<cge::reg::get("this-value-shouldnt-exist-lol")<<"\n";

  std::cout<<"\nTesting string formater\n";
  std::cout<<cge::reg::format("Using CGE Version *.*-*\n",
			      {"cge-version-major",
			       "cge-version-minor",
			       "cge-version-flair"});
  std::cout<<cge::reg::format("Clearly Unknown : *\n",{"this-value-shouldnt-exist-lol"});

  std::cout<<"\nTesting registry addition\n";
  test_put("test-value-1","test-value-2");
  test_put("test-value-2","big word");
  test_put("test-value-3","other value");
  test_grabbed(test_get("test-value-2"));

  std::cout<<"\nTesting CGE Initialization\n";

  if(!cge::init()) {
    std::cout<<cge::reg::format("CGE Error : *\n",{"cge-error-message"});
    die(__LINE__,"Failed to initialize CGE");
  }

  std::cout<<cge::reg::format("Active? : *\nPath : *\nError? : *\nError Message : *\n",
			      {"cge-active",
			       "cge-path",
			       "cge-error-status",
			       "cge-error-message" });
}
