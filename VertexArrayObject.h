//
//  VertexArrayObject.h
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/25/21.
//

#ifndef VertexArrayObject_h
#define VertexArrayObject_h

#include <vector>
#include <glad/glad.h>
#include "types.h"

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

void createQuadVAO(VertexArrayObject*);


#endif /* VertexArrayObject_h */
