//
//  utils.cpp
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/25/21.
//

#include "utils.h"

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

bool loadImage(std::string fileName, GLuint* texture) {
  std::vector<unsigned char> imageBuffer;
  unsigned int width, height;

  const int error = lodepng::decode(imageBuffer, width, height, fileName.c_str());
  if(error != 0) {
    std::cerr << "Failed to load/decode image: " << lodepng_error_text(error) << "\n";
    return false;
  }
  
  GLuint* pixelData = new GLuint[width*height];
  
  for(int y = 0; y < height; y++) {
    for(int x = 0; x < width; x++) {
      const int index = y * width + x;
      const int byteIndex = 4 * index;
      unsigned char r = imageBuffer[byteIndex];
      unsigned char g = imageBuffer[byteIndex + 1];
      unsigned char b = imageBuffer[byteIndex + 2];
      unsigned char a = imageBuffer[byteIndex + 3];
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
      pixelData[index] = (r << 24) + (g << 16) + (b << 8) + a;
#else
      pixelData[index] = (a << 24) + (b << 16) + (g << 8) + r;
#endif
    }
  }
  
  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelData);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  
  glBindTexture(GL_TEXTURE_2D, 0);
  
  delete [] pixelData;
  
  return true;
}
