#include <iostream>

#include <cge/cge.hpp>

#include "testing.hpp"

using namespace cge;

// Helper functions //

const std::string& test_get(const std::string& name) {
  std::cout<<"Getting string '"<<name<<"'";
  return reg::get(name);
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

  unsigned int val = reg::put(name, value);
  
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
	   <<reg::get("cge-version-major")<<"."
	   <<reg::get("cge-version-minor")<<"-"
	   <<reg::get("cge-version-flair")<<"\n";
  std::cout<<"Clearly Unknown : "<<reg::get("this-value-shouldnt-exist-lol")<<"\n";

  std::cout<<"\nTesting string formater\n";
  std::cout<<reg::format("Using CGE Version *.*-*\n",
			 {"cge-version-major",
			  "cge-version-minor",
			  "cge-version-flair"});
  std::cout<<reg::format("Clearly Unknown : *\n",{"this-value-shouldnt-exist-lol"});

  std::cout<<"\nTesting registry addition\n";
  test_put("test-value-1","test-value-2");
  test_put("test-value-2","big word");
  test_put("test-value-3","other value");
  test_grabbed(test_get("test-value-2"));

  std::cout<<"\nTesting CGE Initialization\n";

  if(!cge::init()) {
    std::cout<<reg::format("CGE Error : *\n",{"cge-error-message"});
    die(__LINE__,"Failed to initialize CGE");
  }

  std::cout<<reg::format("Active? : *\nPath : *\nError? : *\nError Message : *\n",
			 {"cge-active",
			  "cge-path",
			  "cge-error-status",
			  "cge-error-message" });

  std::cout<<reg::format("OS Name : *\nOS Architecture : *\n",
			 {"os-name",
			  "os-arch"});

  std::cout<<"\nTesting Logging\n";
  log::log ("Test out from log\n");
  log::log ("The next string should be cut off\n");
  log::logp("You shouldn't see this whole message", 0, 8);
  log::log ("\n");
  log::logf("Using CGE Version %*.%*-%*\n", "cge-version-major","cge-version-minor","cge-version-flair");

  std::cout<<"\nTesting Logging, But with a file\n";
  log::file(reg::get("cge-path")+"cgetest.log");
  log::log ("The next string should be cut off\n");
  log::logp("You shouldn't see this whole message", 0, 8);
  log::log ("\n");
  log::logf("Using CGE Version %*.%*-%*\n", "cge-version-major","cge-version-minor","cge-version-flair");

  if(reg::get("cge-error-status")=="true") {
    log::logf("CGE Error : %*\n", "cge-error-message");
    die(__LINE__, "Failed to open log file");
  }

  log::log("Using file logging for the rest of the tests");
}
