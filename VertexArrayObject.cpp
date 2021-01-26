//
//  VertexArrayObject.cpp
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/25/21.
//

#include "VertexArrayObject.h"

void createQuadVAO(VertexArrayObject* vao) {
  std::vector<Vertex> vbo = {
    {
      .x = 0.0f,
      .y = 0.0f,
      .s = 0.0f,
      .t = 0.0f
    },
    {
      .x = 1.0f,
      .y = 0.0f,
      .s = 1.0f,
      .t = 0.0f
    },
    {
      .x = 1.0f,
      .y = 1.0f,
      .s = 1.0f,
      .t = 1.0f
    },
    {
      .x = 0.0f,
      .y = 1.0f,
      .s = 0.0f,
      .t = 1.0f
    }
  };
  std::vector<unsigned> ebo = {
    0, 1, 3,
    1, 2, 3
  };
  vao->create(vbo, ebo);
}


void VertexArrayObject::create(std::vector<Vertex>& vbo, std::vector<unsigned>& ebo) {
  glGenVertexArrays(1, &glVAO);
  glBindVertexArray(glVAO);
  
  glGenBuffers(1, &glVBO);
  glBindBuffer(GL_ARRAY_BUFFER, glVBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vbo.size(), &vbo[0], GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
  glEnableVertexAttribArray(0);
  
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));
  glEnableVertexAttribArray(1);
  
  glGenBuffers(1, &glEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * ebo.size(), &ebo[0], GL_STATIC_DRAW);
  
  glBindVertexArray(0);
}

const GLuint& VertexArrayObject::getVAO() const {
  return glVAO;
}

VertexArrayObject::~VertexArrayObject() {
  glDeleteBuffers(1, &glVBO);
  glDeleteBuffers(1, &glEBO);
  glDeleteVertexArrays(1, &glVAO);
}

