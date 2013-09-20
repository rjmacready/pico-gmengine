#include <ecl/ecl.h>
#include "scripts.h"



int load_and_exec(const char *filename) {
  cl_object cl_load = ecl_make_symbol("load", "CL");
  cl_object cl_filename = c_string_to_object(filename);

  cl_object result = cl_funcall(1, cl_load, cl_filename);  
  
  return 0;
}
