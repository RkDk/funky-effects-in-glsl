//
//  Framebuffer.cpp
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 2/8/21.
//

#include "Framebuffer.h"

Framebuffer::~Framebuffer() {
  glDeleteFramebuffers(1, &frameBuffer);
  glDeleteTextures(1, &renderTexture);
}

bool Framebuffer::initialize() {
  glGenFramebuffers(1, &frameBuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  
  glGenTextures(1, &renderTexture);
  glBindTexture(GL_TEXTURE_2D, renderTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, renderTexture, 0);
  
  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    return false;
  }
  
  glBindFramebuffer(GL_TEXTURE_2D, 0);
  
  return true;
}

void Framebuffer::bind() const {
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  
}
