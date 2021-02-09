//
//  Framebuffer.h
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 2/8/21.
//

#ifndef Framebuffer_h
#define Framebuffer_h

#include <iostream>
#include <glad/glad.h>
#include "constants.h"

class Framebuffer {
private:
  GLuint frameBuffer, renderTexture;
  
public:
  
  const GLuint & getFrameBuffer() const {
    return frameBuffer;
  }
  
  const GLuint & getRenderTexture() const {
    return renderTexture;
  }
  
  bool initialize();
  void bind() const;
  ~Framebuffer();
};

#endif /* Framebuffer_h */
