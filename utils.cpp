//
//  utils.cpp
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/25/21.
//

#include "utils.h"

bool readFileIntoString(std::string fileName, std::string *dest) {
  std::ifstream in(fileName);
  if(!in) {
    std::cerr << "Failed to open file: " << fileName << "\n";
    return false;
  }
  in.seekg(0,std::ios_base::end);
  (*dest).reserve(in.tellg());
  in.seekg(0,std::ios_base::beg);
  (*dest).assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
  in.close();
  return true;
}
