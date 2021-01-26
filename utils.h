//
//  utils.h
//  funky-effects-in-glsl
//
//  Created by Rick Chou on 1/25/21.
//

#ifndef utils_h
#define utils_h

#define LODEPNG_COMPILE_CPP

#include <fstream>
#include <iostream>
#include <string>
#include <glad/glad.h>
#include <lodepng.h>
#include <SDL2/SDL.h>

bool readFileIntoString(std::string, std::string*);
bool loadImage(std::string, GLuint*);

#endif /* utils_h */
