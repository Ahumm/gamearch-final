#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// LOAD A SHADER BY FILE NAME AND SHADER TYPE
GLuint load_shader(const char* filename, const GLenum& shader_type)
{
	GLuint shader_id = 0;
	FILE* file;
	long file_size = -1;
	GLchar* glsl_source;
#if DEBUG_OUTPUT
    fprintf(stderr, "name: %s\n",filename);
    fprintf(stdout, "name: %s\n",filename);
#endif
	if (NULL != (file = fopen(filename, "rb")) &&
		0 == fseek(file, 0, SEEK_END) &&
		-1 != (file_size = ftell(file)))
	{
		rewind(file);
		
		if (NULL != (glsl_source = (GLchar*)malloc(file_size + 1)))
		{
			if (file_size == (long)fread(glsl_source, sizeof(GLchar), file_size, file))
			{
				glsl_source[file_size] = '\0';
                const GLchar* glsl_source_c = glsl_source;
				fprintf(stderr, "Source: %s\n", glsl_source_c);
                //fprintf(stdout, "Source: %s\n", glsl_source_c);

				if (0 != (shader_id = glCreateShader(shader_type)))
				{
					glShaderSource(shader_id, 1, &glsl_source_c, NULL);
					glCompileShader(shader_id);
					on_gl_error("Could not compile a shader");
				}
				else
                {
                #if DEBUG_OUTPUT
					fprintf(stderr, "ERROR: Could not create a shader.\n");
                    fprintf(stdout, "ERROR: Could not create a shader.\n");
                #endif
                }
			}
			else
            {
            #if DEBUG_OUTPUT
				fprintf(stderr, "ERROR: Could not read file %s\n", filename);
				fprintf(stdout, "ERROR: Could not read file %s\n", filename);
            #endif
            }
			free(glsl_source);
		}
		else
        {
        #if DEBUG_OUTPUT
			fprintf(stderr, "ERROR: Could not allocate %li bytes.\n", file_size);
			fprintf(stdout, "ERROR: Could not allocate %li bytes.\n", file_size);
        #endif
        }
		fclose(file);
	}
	else
    {
    #if DEBUG_OUTPUT
		fprintf(stderr, "ERROR: Could not open file %s\n", filename);
		fprintf(stdout, "ERROR: Could not open file %s\n", filename);
    #endif
    }

	return shader_id;
}

// CHECK THAT A SHADER WAS COMPILED CORRECTLY
void check_shader(const GLuint& shader)
{
	GLint status;
	//lGetShaderiv gets a particular parameter of the shader
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		int loglen;
		char logbuffer[1000];
		//there's also a corresponding glGetProgramInfoLog function for the linked program object
		glGetShaderInfoLog(shader, sizeof(logbuffer), &loglen, logbuffer);
    #if DEBUG_OUTPUT
		fprintf(stderr, "OpenGL Shader Compile Error:\n%.*s", loglen, logbuffer);
		fprintf(stdout, "OpenGL Shader Compile Error:\n%.*s", loglen, logbuffer);
    #endif
	} else {
		int loglen;
		char logbuffer[1000];
		glGetShaderInfoLog(shader, sizeof(logbuffer), &loglen, logbuffer);
    #if DEBUG_OUTPUT
		fprintf(stderr, "OpenGL Shader Compile OK:\n%.*s", loglen, logbuffer);
		fprintf(stdout, "OpenGL Shader Compile OK:\n%.*s", loglen, logbuffer);
    #endif
	}
}

// CHECK IF THERE WAS AN OPENGL ERROR
void on_gl_error(const char* error_message)
{
	const GLenum ErrorValue = glGetError();

	if (ErrorValue != GL_NO_ERROR)
	{
		const char* APPEND_DETAIL_STRING = ": %s\n";
		const size_t APPEND_LENGTH = strlen(APPEND_DETAIL_STRING) + 1;
		const size_t message_length = strlen(error_message);
		char* display_message = (char*)malloc(message_length + APPEND_LENGTH);

		memcpy(display_message, error_message, message_length);
		memcpy(&display_message[message_length], APPEND_DETAIL_STRING, APPEND_LENGTH);
    #if DEBUG_OUTPUT
		fprintf(stderr, display_message, "");//gluErrorString(ErrorValue));
		fprintf(stdout, display_message, "");//gluErrorString(ErrorValue));
    #endif

		free(display_message);
	}
}

float clamp(const float& f, const float& min, const float& max)
{
    return (f < min) ? min : ((f > max) ? max : f);
}

std::string int_to_string(const int& num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}

std::string float_to_string(const float& num)
{
    std::stringstream ss;
    ss << num;
    return ss.str();
}

