//
//  Shader.cpp
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/25/21.
//

#include "Shader.h"

bool Shader::load(std::string fileName, GLuint shaderType) {
  std::string shader;
  if(!readFileIntoString(fileName, &shader)) {
    std::cerr << "Failed to load shader\n";
    return false;
  }
  
  const GLchar* shaderSource[1] = {shader.c_str()};
  const GLint shaderLength[1] = {static_cast<GLint>(shader.length())};
  
  this->shaderType = shaderType;
  this->glShader = glCreateShader(this->shaderType);
  glShaderSource(this->glShader, 1, shaderSource, shaderLength);
  glCompileShader(this->glShader);
  
  GLint compileStatus;
  glGetShaderiv(this->glShader, GL_COMPILE_STATUS, &compileStatus);
  if(compileStatus == GL_FALSE) {
    char errorLog[512];
    glGetShaderInfoLog(this->glShader, 512, NULL, errorLog);
    std::cerr << "Failed to load shader: " << errorLog << "\n";
    return false;
  }
  return true;
}

const GLuint& Shader::getShader() const {
  return this->glShader;
}

Shader::~Shader() {
  glDeleteShader(this->glShader);
}

