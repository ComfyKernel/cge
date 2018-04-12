#include <cge/log.hpp>
#include <cge/reg.hpp>

#include <iostream>
#include <fstream>

#include <cstdarg>

using namespace cge;

std::ofstream _cge_log_file;
bool          _cge_log_open;

bool log::file(const std::string& s_fname) {
  if(_cge_log_file.is_open()) {
    close();
  }

  _cge_log_file.open(s_fname, std::ios::out);
  if(_cge_log_file.is_open()) {
    _cge_log_open = true;
    return true;
  }

  std::cerr<<"Failed to open log file '"<<s_fname<<"'\n";
  reg::put("cge-error-status" ,"true");
  reg::put("cge-error-message","Failed to open a log file");

  return false;
}

void log::log(const std::string& str) {
  std::cout<<str;

  if(!_cge_log_open) return;

  _cge_log_file<<str;
}

void log::logp(const std::string& str, unsigned int s, unsigned int e) {
  std::cout.write(&str[s], e - s);

  if(!_cge_log_open) return;

  _cge_log_file.write(&str[s], e - s);
}

unsigned int u_lf_c = 0;
bool         b_lf_r = false;

void log::logf(const std::string& s_base, ...) {
  u_lf_c = 0;
  b_lf_r = false;
  
  va_list vargs;
  va_start(vargs, s_base);
  
  for(unsigned int i=0; i<s_base.length(); ++i) {
    if(b_lf_r) {
      b_lf_r = false;
      switch(s_base[i]) {
      case '*':
	log(reg::get(va_arg(vargs, char*)));
	continue;
      case 's':
	log(va_arg(vargs, char*));
	continue;
      case 'd':
	log(std::to_string(va_arg(vargs, int)));
	continue;
      default:
	log(va_arg(vargs, char*));
	continue;
      }
      // If it somehow reaches here, continue
      continue;
    }
    
    if(s_base[i]=='%') {
      logp(s_base, u_lf_c, i);
      u_lf_c = i + 2;
      b_lf_r = true;
      continue;
    }
  }

  logp(s_base, u_lf_c, s_base.length());

  va_end(vargs);
}

void log::close() {
  if(!_cge_log_file.is_open()) return;

  log("Closing the log file\n");
  _cge_log_file.close();
  _cge_log_open = false;
}
