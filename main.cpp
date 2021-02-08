//
//  main.cpp
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/20/21.
//


#include <iostream>
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "RenderContext.h"

int wavyFactor = 0;

void setShaderUniforms(RenderContext *renderContext) {
  const GLuint& glShaderProgram = renderContext->shaderProgram.getShaderProgram();
  
  GLint wavyFactorUniform = glGetUniformLocation(glShaderProgram, "wavyFactor");
  GLint textureUniform = glGetUniformLocation(glShaderProgram, "textureId");
  GLint viewUniform = glGetUniformLocation(glShaderProgram, "view");
  GLint projUniform = glGetUniformLocation(glShaderProgram, "projection");
  GLint modelUniform = glGetUniformLocation(glShaderProgram, "model");
  
  glUniform1i(textureUniform, 0);
  
  glm::mat4 viewMatrix(1.0f);
  glm::mat4 projMatrix = glm::ortho<float>(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
  glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(renderContext->imageWidth, renderContext->imageHeight, 1.0f));

  switch(renderContext->renderMode) {
    case RenderMode::WAVY:
      if(++wavyFactor > 359) {
        wavyFactor = 0;
      }
      break;
    default: break;
  }
  
  glUniform1i(wavyFactorUniform, wavyFactor);
  glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
  glUniformMatrix4fv(projUniform, 1, GL_FALSE, glm::value_ptr(projMatrix));
  glUniformMatrix4fv(modelUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
}

void render(RenderContext *renderContext) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBindVertexArray(renderContext->quadVAO.getVAO());
  glUseProgram(renderContext->shaderProgram.getShaderProgram());
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, renderContext->imageTexture);
  setShaderUniforms(renderContext);
  glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);
  glBindVertexArray(0);
  glUseProgram(0);
  SDL_GL_SwapWindow(renderContext->window);
}

void mainLoop(RenderContext *renderContext) {
  while(true) {
    SDL_Event event;
    SDL_PollEvent(&event);
    
    if(event.type == SDL_QUIT) {
      return;
    }

    switch(event.key.keysym.sym) {
      case SDLK_0:
        renderContext->renderMode = RenderMode::DEFAULT;
        wavyFactor = 0;
        break;
      case SDLK_1:
        renderContext->renderMode = RenderMode::WAVY;
      default: break;
    }
    
    render(renderContext);
  }
}

int main(int argc, const char * argv[]) {
  
  RenderContext renderContext;
  if(!initGraphics(&renderContext)) {
    std::cout << getGraphicsErr() << "\n";
    return -1;
  }
  
  if(!renderContext.shaderProgram.buildFromShaders("vertex.vs", "fragment.fs")) {
    return -1;
  }
  
  loadImage("image.png", renderContext.imageWidth, renderContext.imageHeight, renderContext.imageTexture);
  
  createQuadVAO(&renderContext.quadVAO);
  mainLoop(&renderContext);
  
  return 0;
}
