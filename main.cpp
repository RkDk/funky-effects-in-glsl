//
//  main.cpp
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/20/21.
//

#define LODEPNG_COMPILE_CPP

#include <iostream>
#include <fstream>
#include <lodepng.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

bool readFileIntoString(std::string fileName, std::string *dest) {
  std::ifstream in(fileName);
  if(!in) {
    std::cerr << "Failed to open file: " << fileName << "\n";
    return false;
  }
  in.seekg(0,std::ios_base::end);
  (*dest).reserve(in.tellg());
  in.seekg(0,std::ios_base::beg);
  (*dest).assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
  in.close();
  return true;
}

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

struct Vertex {
  float x, y;
};

class VertexArrayObject {
private:
  GLuint glVAO, glVBO, glEBO;
  
public:
  
  void create(std::vector<Vertex>& vbo, std::vector<unsigned>& ebo) {
    glGenVertexArrays(1, &glVAO);
    glBindVertexArray(glVAO);
    
    glGenBuffers(1, &glVBO);
    glBindBuffer(GL_ARRAY_BUFFER, glVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vbo.size(), &vbo[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*)0);
    glEnableVertexAttribArray(0);
    
    glGenBuffers(1, &glEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * ebo.size(), &ebo[0], GL_STATIC_DRAW);
    
    glBindVertexArray(0);
  }
  
  const GLuint& getVAO() const {
    return glVAO;
  }
  
  ~VertexArrayObject() {
    glDeleteBuffers(1, &glVBO);
    glDeleteBuffers(1, &glEBO);
    glDeleteVertexArrays(1, &glVAO);
  }
};


struct RenderContext {
  SDL_Window *window = NULL;
  SDL_GLContext glContext = NULL;
  VertexArrayObject quadVAO;
  ShaderProgram shaderProgram;
  
  ~RenderContext() {
    SDL_GL_DeleteContext(this->glContext);
    SDL_DestroyWindow(this->window);
  }
};


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
  
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  
  return true;
}

void createQuadVAO(VertexArrayObject* vao) {
  std::vector<Vertex> vbo = {
    {
      .x = 0.0f,
      .y = 0.0f
    },
    {
      .x = 100.0f,
      .y = 0.0f
    },
    {
      .x = 100.0f,
      .y = 100.0f
    },
    {
      .x = 0.0f,
      .y = 100.0f
    }
  };
  std::vector<unsigned> ebo = {
    0, 1, 3,
    1, 2, 3
  };
  vao->create(vbo, ebo);
}

void setShaderUniforms(ShaderProgram* shaderProgram) {
  const GLuint& glShaderProgram = shaderProgram->getShaderProgram();
  
  GLint viewUniform = glGetUniformLocation(glShaderProgram, "view");
  GLint projUniform = glGetUniformLocation(glShaderProgram, "projection");
  
  glm::mat4 viewMatrix(1.0f);
  glm::mat4 projMatrix = glm::ortho<float>(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
  
  glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(viewMatrix));
  glUniformMatrix4fv(projUniform, 1, GL_FALSE, glm::value_ptr(projMatrix));
}

void render(RenderContext *renderContext) {
  glClear(GL_COLOR_BUFFER_BIT);
  glBindVertexArray(renderContext->quadVAO.getVAO());
  glUseProgram(renderContext->shaderProgram.getShaderProgram());
  setShaderUniforms(&renderContext->shaderProgram);
  glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, NULL);
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
  
  createQuadVAO(&renderContext.quadVAO);

  mainLoop(&renderContext);
  
  return 0;
}
