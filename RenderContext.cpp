//
//  RenderContext.cpp
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/25/21.
//

#include "RenderContext.h"

std::string graphicsErrorString = "Unknown error";

std::string getGraphicsErr() {
  return graphicsErrorString;
}

bool initGraphics(RenderContext *context) {
 if(SDL_Init(SDL_INIT_VIDEO) < 0) {
   graphicsErrorString = SDL_GetError();
   return false;
 }
 SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
 SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
 SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
 SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
 SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
 
 context->window = SDL_CreateWindow("funky-effects-in-glsl", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
 
 if(!context->window) {
   graphicsErrorString = SDL_GetError();
   return false;
 }
 
 context->glContext = SDL_GL_CreateContext(context->window);
 
 if(!context->glContext) {
   graphicsErrorString = SDL_GetError();
   return false;
 }
 
 if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
   graphicsErrorString = "Glad failed to initialize";
   return false;
 }
 
 glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
 
 return true;
}

