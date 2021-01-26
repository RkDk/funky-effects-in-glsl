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


