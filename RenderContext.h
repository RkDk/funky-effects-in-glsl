//
//  RenderContext.h
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/25/21.
//

#ifndef RenderContext_h
#define RenderContext_h

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "VertexArrayObject.h"
#include "Framebuffer.h"
#include "ShaderProgram.h"
#include "constants.h"

enum class RenderMode {
  DEFAULT,
  WAVY
};

struct RenderContext {
  SDL_Window *window = NULL;
  SDL_GLContext glContext = NULL;
  VertexArrayObject quadVAO;
  unsigned int imageWidth, imageHeight;
  GLuint imageTexture;
  ShaderProgram shaderProgram;
  ShaderProgram fbShaderProgram;
  Framebuffer renderTarget;
  RenderMode renderMode = RenderMode::DEFAULT;
  
  ~RenderContext() {
    glDeleteTextures(1, &imageTexture);
    SDL_GL_DeleteContext(this->glContext);
    SDL_DestroyWindow(this->window);
  }
};

std::string getGraphicsErr();
bool initGraphics(RenderContext*);

#endif /* RenderContext_h */
