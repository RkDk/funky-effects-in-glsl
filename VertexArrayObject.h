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
  
  void create(std::vector<Vertex>&, std::vector<unsigned>&);
  const GLuint& getVAO() const;
  ~VertexArrayObject();
};

void createQuadVAO(VertexArrayObject*);


#endif /* VertexArrayObject_h */
