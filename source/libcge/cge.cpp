#include <cge/cge.hpp>

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
