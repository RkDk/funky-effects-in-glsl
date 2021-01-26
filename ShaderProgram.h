//
//  ShaderProgram.h
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/25/21.
//

#ifndef ShaderProgram_h
#define ShaderProgram_h

#include <string>
#include <glad/glad.h>
#include "Shader.h"

class ShaderProgram {
private:
  GLuint glShaderProgram;
  
public:
  bool buildFromShaders(std::string vertexFilePath, std::string fragmentFilePath) {
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
  const GLuint& getShaderProgram() const {
    return this->glShaderProgram;
  }
  ~ShaderProgram() {
    glDeleteProgram(this->glShaderProgram);
  }
};


#endif /* ShaderProgram_h */
