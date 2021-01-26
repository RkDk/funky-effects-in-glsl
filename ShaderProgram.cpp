//
//  ShaderProgram.cpp
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/25/21.
//

#include "ShaderProgram.h"

bool ShaderProgram::buildFromShaders(std::string vertexFilePath, std::string fragmentFilePath) {
  Shader vertexShader, fragmentShader;
  
  if(!vertexShader.load(vertexFilePath, GL_VERTEX_SHADER) ||
     !fragmentShader.load(fragmentFilePath, GL_FRAGMENT_SHADER)) {
    std::cerr << "Failed to load shaders for program\n";
    return false;
  }
  
  this->glShaderProgram = glCreateProgram();
  glAttachShader(this->glShaderProgram, vertexShader.getShader());
  glAttachShader(this->glShaderProgram, fragmentShader.getShader());
  glLinkProgram(this->glShaderProgram);
  
  GLint linkStatus;
  glGetProgramiv(this->glShaderProgram, GL_LINK_STATUS, &linkStatus);
  if(linkStatus == GL_FALSE) {
    char errorLog[512];
    glGetProgramInfoLog(this->glShaderProgram, 512, NULL, errorLog);
    std::cerr << errorLog << "\n";
    return false;
  }
  
  return true;
}

const GLuint& ShaderProgram::getShaderProgram() const {
  return this->glShaderProgram;
}

ShaderProgram::~ShaderProgram() {
  glDeleteProgram(this->glShaderProgram);
}
