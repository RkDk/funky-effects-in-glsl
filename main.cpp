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

void setShaderUniforms(ShaderProgram* shaderProgram) {
  const GLuint& glShaderProgram = shaderProgram->getShaderProgram();
  
  GLint textureUniform = glGetUniformLocation(glShaderProgram, "textureId");
  GLint viewUniform = glGetUniformLocation(glShaderProgram, "view");
  GLint projUniform = glGetUniformLocation(glShaderProgram, "projection");
  
  glUniform1i(textureUniform, 0);
  
  glm::mat4 viewMatrix(1.0f);
  glm::mat4 projMatrix = glm::ortho<float>(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
  
  glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
  glUniformMatrix4fv(projUniform, 1, GL_FALSE, glm::value_ptr(projMatrix));
}

void render(RenderContext *renderContext) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBindVertexArray(renderContext->quadVAO.getVAO());
  glUseProgram(renderContext->shaderProgram.getShaderProgram());
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, renderContext->imageTexture);
  setShaderUniforms(&renderContext->shaderProgram);
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
