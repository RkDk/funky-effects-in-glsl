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
  bool buildFromShaders(std::string, std::string);
  const GLuint& getShaderProgram() const;
  ~ShaderProgram();
};


#endif /* ShaderProgram_h */
