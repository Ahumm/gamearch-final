#include "model.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include <GL/glew.h>
#include <glm/glm.hpp> //feel free to use your own math library!
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

model::model()
{
    model_matrix = glm::mat4(1.0f);
    frame_matrix = model_matrix;
    dead = false;
    expires = false;
    lifespan = 0.0;
    scale = 1.0f
}

model::model(char* file)
{
    model_matrix = glm::mat4(1.0f);
    frame_matrix = model_matrix;
    dead = false;
    expires = false;
    lifespan = 0.0;
    scale = 1.0f
    
    load_model(file);
    
    gl_gunk();
}
    
void model::load_model(char* file)
{
    ifstream file;
    file.open(path);
    if(!file.is_open()){
        cout << "File " << path << " could not be opened" << endl;
        return;
    }
    while(!file.eof())
    {
        string line;
        string tmp;
        string cmd;
                
        getline(file,line);
        size_t s = line.find("<"), e = line.find(">");
        if(s == string::npos || e == string::npos) continue;
        
        cmd = line.substr(s,e-s+1);
        
        if(cmd == "<Texture>")
        {
            getline(file,line);
            size_t s = line.find("\""), e = line.rfind("\"");
            texture = line.substr(s+1,e-s-1);
            //cout << cmd << ": " << line.substr(s+1,e-s-1) << endl;
        }
        if(cmd == "<Vertex>")
        {
            float posx,posy,posz, normx,normy,normz, u,v;
            
            file >> posx >> posy >> posz >> tmp >> tmp >> normx >> normy >> normz >> tmp >> tmp >> tmp >> u >> v;
            //cout << cmd << ": " << posx << " , " << posy << " , " << posz << endl;
            vertex tmp_vertex = { posx, posy, posz, 1.0f,
                                  1.0f, 1.0f, 1.0f, 1.0f,
                                     u,    v,
                                 normx,normy,normz, 0.0f};
            //tmp_vertex.position = vec4(posx,posy,posz,1.0f);
            //tmp_vertex.uv = vec2(u,v);
            //tmp_vertex.normal = vec4(normx,normy,normz,0.0f);
            verts.push_back(tmp_vertex);
            //verticies.push_back(vec3(posx,posy,posz));
            //normals.push_back(vec3(normx,normy,normz));
            //uvs.push_back(vec2(u,v));
        }
        if(cmd == "<Polygon>")
        {
            int a,b,c;
            getline(file,line);
            getline(file,line);
            file >> tmp >> tmp >> a >> b >> c;
            polys.push_back(a-1);
            polys.push_back(b-1);
            polys.push_back(c-1);
            //cout << cmd << ": " << a << " , " << b << " , " << c << endl;
        }
    }
    file.close();
    //assign_RGBA();
}

void model::init()
{
    vert_count = (GLuint)verts.size();
    poly_count = (GLuint)polys.size();
    
    vert_size = (GLuint)sizeof(verts[0]);
    rgba_offset = (GLuint)sizeof(verts[0].position);
    uv_offset = rgba_offset + (GLuint)sizeof(verts[0].rgba);
    norm_offset = uv_offset + (GLuint)sizeof(verts[0].uv);
    poly_size = (GLuint)sizeof(polys[0]);
    
    shader_program = glCreateProgram();
    
    frag_shader = load_shader("shaders/base.fs", GL_FRAGMENT_SHADER);
    vert_shader = load_shader("shaders/base.vs", GL_VERTEX_SHADER);
    
    glAttachShader(shader_program, frag_shader);
    glAttachShader(shader_program, vert_shader);
    
    glBindAttribLocation(shader_program, 0, "in_Position");
	glBindAttribLocation(shader_program, 1, "in_Color");
    
    glLinkProgram(shader_program);
    
    glUseProgram(shader_program);
    
    model_matrix_loc = glGetUniformLocation(shader_program, "ModelMatrix");
    view_matrix_loc = glGetUniformLocation(shader_program, "ViewMatrix");
    projection_matrix_loc = glGetUniformLocation(shader_program, "ProjectionMatrix");
    
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glGenBuffers(1, &vbo_vert);
    glGenBuffers(1, &vbo_poly);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vert);
    glBufferData(GL_ARRAY_BUFFER, vert_size * vert_count, &(verts[0]), GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vert_size, (GLvoid*)0);             // Position
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vert_size, (GLvoid*)rgba_offset);   // RGBA
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_poly);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, poly_size * poly_count, &(polys[0]), GL_STATIC_DRAW);
    
    glBindVertex_array(0);
    
    glUseProgram(0);
}

GLuint model::load_shader(const char* filename, GLenum shader_type)
{
	GLuint shader_id = 0;
	FILE* file;
	long file_size = -1;
	GLchar* glsl_source;
    fprintf(stderr, "name: %s\n",filename);

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

				if (0 != (shader_id = glCreateShader(shader_type)))
				{
					glShaderSource(shader_id, 1, &glsl_source_c, NULL);
					glCompileShader(shader_id);
					OnGLError("Could not compile a shader");
				}
				else
					fprintf(stderr, "ERROR: Could not create a shader.\n");
			}
			else
				fprintf(stderr, "ERROR: Could not read file %s\n", filename);

			free(glsl_source);
		}
		else
			fprintf(stderr, "ERROR: Could not allocate %li bytes.\n", file_size);

		fclose(file);
	}
	else
		fprintf(stderr, "ERROR: Could not open file %s\n", filename);

	return shader_id;
}

void model::update(double delta_time)
{
    frame_matrix = model_matrix;
    
    if(expires && !dead)
    {
        lifespan -= delta_time;
        dead = !(lifespan > 0);
    }
}
    
void model::draw(glm::mat4& view_matrix, glm::mat4& projection_matrix)
{
    glUseProgram(shader_program);
    
    glUniformMatrix4fv(frame_matrix_loc, 1, GL_FALSE, glm::value_ptr(model_matrix));
    glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, glm::value_ptr(view_matrix));
    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, glm::value_ptr(projectio_matrix));
    
    glBindVertexArray(vao);
    
    glDrawElements(GL_TRIANGLES, 3 * poly_count, GL_UNSIGNED_INT, (GLvoid*)0);
    
    glBindVertexArray(0);
    
    glUseProgram(0);
}

model& operator=(const model& other)
{
    if(this != &other)
    {
        model_matrix = other.model_matrix;
        scale = other.scale;
        frame_matrix = model_matrix;
        dead = other.dead;
        expires = other.expires;
        lifespan = other.lifespan;
        verts = other.verts;
        polys = other.polys;
        
        init();
    }
    
    return *this
}

void model::scale(float & factor)
{
    if(scale == 0) return;
    scale = factor;
    model_matrix = glm::scale(model_matrix, glm::vec3(scale));
}

void model::undo_scale()
{
    model_matrix = glm::scale(model_matrix, glm::vec3(1.0f / scale));
    scale = 1.0f;
}
