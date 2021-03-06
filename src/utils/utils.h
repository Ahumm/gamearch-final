#ifndef _UTILS_H_
#define _UTILS_H_

#include <GL/glew.h>
#include <sstream>
#include <string>

#define DEBUG_OUTPUT 0

#define PI 3.14159265358979323846
#define MAX_PARTICLES_PER_EMITTER 100000
#define GRAVITY -10000
#define TERM_VEL 100
#define GRAV_CONST 0.0000000000667384
#define GRAV_MAX 100

#define lerp(f1, f2, a) ((f1 * a) + f2 * (1.0 - a) )

GLuint load_shader(const char* filename, const GLenum& shader_type);
void check_shader(const GLuint& shader);
void on_gl_error(const char* error_message);

float clamp(const float& f, const float& min, const float& max);

std::string int_to_string(const int& num);
std::string float_to_string(const float& num);

#endif