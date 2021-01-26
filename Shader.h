//
//  Shader.h
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/25/21.
//

#ifndef Shader_h
#define Shader_h

#include <string>
#include <iostream>
#include <glad/glad.h>
#include "utils.h"

class Shader {
private:
  GLuint glShader;
  GLuint shaderType;
  
public:
  bool load(std::string fileName, GLuint shaderType) {
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
  
  const GLuint& getShader() const {
    return this->glShader;
  }
  
  ~Shader() {
    glDeleteShader(this->glShader);
  }
};


#endif /* Shader_h */
