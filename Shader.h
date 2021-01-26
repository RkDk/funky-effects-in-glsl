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
  bool load(std::string, GLuint);
  const GLuint& getShader() const;
  ~Shader();
};


#endif /* Shader_h */
