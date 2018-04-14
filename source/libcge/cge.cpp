#include <cge/cge.hpp>

#include <iostream>
#include <experimental/filesystem>

//               // ############################################################################ //
// CGE Functions // ############################################################################ //
//               // ############################################################################ //

bool cge::init() {
  // Add a status to the registry which tells the program we are running
  cge::reg::put("cge-active","true");

  // Set up error handling registry options
  cge::reg::put("cge-error-status","false");
  cge::reg::put("cge-error-message","NO-ERROR");

  // Get the current working path and check for missing '/'
  std::string path = std::experimental::filesystem::current_path();;

  if(path[path.size() - 1] != '/') {
    path += '/';
  }

  cge::reg::put("cge-path", path);

  // Get OS information

  std::string os_name="Non-Standard OS";
  #ifdef __linux__
    os_name = "Linux";
  #elif  __unix || __unix__
    os_name = "Unix";
  #elif  __FreeBSD__
    os_name = "FreeBSD";
  #elif __APPLE || __MACH__
    os_name = "Mac OSX";
  #elif _Win32
    os_name = "Windows 32-Bit";
  #elif _Win64
    os_name = "Windows 64-Bit";
  #endif

  cge::reg::put("os-name", os_name);

  std::string os_arch="x86_64";
  #if defined(_M_IX86) || defined(__i386__)
    os_arch = "x86";
  #endif
  
  cge::reg::put("os-arch", os_arch);
  
  return true;
}

//              // ############################################################################ //
// CGE Registry // ############################################################################ //
//              // ############################################################################ //

std::vector<std::string> _cge_reg_values={
  // Used for unknown names when calling *get* //
  "UNKNOWN",

  // Basic information about CGE //
  "cge-version-major", "0",
  "cge-version-minor", "1",
  "cge-version-flair", "alpha",
  "cge-author"       , "ComfyKernel"
};

const std::string& cge::reg::get(const std::string& name) {
  // This iterates through all the strings and it returns
  // if there is a match AND if it is also a name and not a value ((i+1)%2),
  // the -1 offset is for the "UNKNOWN" value at the start of the array.
  // It will also return "UNKNOWN" if the name isn't found
  
  for(unsigned int i=0;i<_cge_reg_values.size();++i) {
    if(_cge_reg_values[i] == name && (i+1)%2 == 0) {
      return _cge_reg_values[i+1];
    }
  }

  return _cge_reg_values[0];
}

unsigned int cge::reg::put(const std::string& name, const std::string& value) {
  // First loop through the values and find a matching name, if found,
  // replace the string in the registry, if not found, add a new string
  // into the registry

  if(name == "UNKNOWN") return CGE_REG_FAILED; // Special case, stub for reserved names
  
  for(unsigned int i=0;i<_cge_reg_values.size();++i) {
    if(_cge_reg_values[i] == name && (i+1)%2 == 0) {
      _cge_reg_values[i + 1] = value;
      
      return CGE_REG_REPLACED;
    }
  }

  _cge_reg_values.push_back(name);
  _cge_reg_values.push_back(value);
  
  return CGE_REG_ADDED;
}

std::string cge::reg::format(const std::string& str_in, const std::initializer_list<std::string>& vals) {
  // Check for '*' in a string and format registry variables in it as needed
  
  std::string out="";
  unsigned int off=0;
  
  for(auto i : str_in) {
    if(i == '*') {
      if(off>=vals.size()) {
	// Keep repeating the last value so we don't drop off the array
	off-=1;
      }
      
      out+=get(vals.begin()[off]);
      off+=1;
      
      continue;
    }

    out+=i;
  }

  return out;
}

const std::vector<std::string>& cge::reg::all() {
  return _cge_reg_values;
}
