#include "model.h"
#include "../utils/utils.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp> //feel free to use your own math library!
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

model::model()
{
    model_matrix = glm::mat4(1.0f);
    frame_matrix = model_matrix;
    m_scale = 1.0f;
    total_rotation = 0.0f;
    active = false;
    rotate = false;
}

model::model(const char* file)
{
    model_matrix = glm::mat4(1.0f);
    frame_matrix = model_matrix;
    m_scale = 1.0f;
    total_rotation = 1.0f;
    
    active = true;
    rotate = true;
    
    load_model(file);
    init();
}
    
void model::load_model(const char* path)
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
    normal_offset = uv_offset + (GLuint)sizeof(verts[0].uv);
    poly_size = (GLuint)sizeof(polys[0]);
    
    shader_program = glCreateProgram();
    on_gl_error("ERROR: Could not create the shader program");
    
    frag_shader = load_shader("shaders/panda.fs", GL_FRAGMENT_SHADER);
    check_shader(frag_shader);
    vert_shader = load_shader("shaders/panda.vs", GL_VERTEX_SHADER);
    check_shader(vert_shader);
    
    glAttachShader(shader_program, frag_shader);
    glAttachShader(shader_program, vert_shader);
    
    glBindAttribLocation(shader_program, 0, "in_Position");
	glBindAttribLocation(shader_program, 1, "in_Tex");
    
    glLinkProgram(shader_program);
    
    glUseProgram(shader_program);
    
    model_matrix_loc = glGetUniformLocation(shader_program, "ModelMatrix");
    view_matrix_loc = glGetUniformLocation(shader_program, "ViewMatrix");
    projection_matrix_loc = glGetUniformLocation(shader_program, "ProjectionMatrix");
    sampler_loc = glGetUniformLocation(shader_program, "s_tex");
    
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    on_gl_error("ERROR: Could not enable vertex attributes");
    
    glGenBuffers(1, &vbo_vert);
    glGenBuffers(1, &vbo_poly);
    on_gl_error("ERROR: Could not generate the buffer objects");
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vert);
    glBufferData(GL_ARRAY_BUFFER, vert_size * vert_count, &(verts[0]), GL_STATIC_DRAW);
    on_gl_error("ERROR: Could not bind the VBO to the VAO");
    
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vert_size, (GLvoid*)0);             // Position
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vert_size, (GLvoid*)uv_offset);     // UV
    on_gl_error("ERROR: Could not set VAO attributes");
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_poly);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, poly_size * poly_count, &(polys[0]), GL_STATIC_DRAW);
    on_gl_error("ERROR: Could not bind the IBO to the VAO");
    
    // Generate texture objects
    glGenTextures( 1, &tex_id );

    // Make texture object active
    glBindTexture( GL_TEXTURE_2D, tex_id );
    on_gl_error("ERROR: Could not bind Texture");
    
    // Set texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    on_gl_error("ERROR: Could not set Texture parameters");
    
    // Upload texture from file to texture memory, autouses glTexImage2D, needs TGA
    sf::Image img;
    if(!img.loadFromFile("textures/" + texture))
    {
        fprintf( stderr, "Failed to load texture" );
        fprintf( stdout, "Failed to load texture" );
        throw 1;
    }
    
    img.flipVertically();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
    on_gl_error("ERROR: Could not load Texture");
    
    glBindVertexArray(0);
    glUseProgram(0);
}

void model::update(const double& delta_time)
{
    if(!active) return;
    if(!rotate) return;
    
    float model_angle;

	total_rotation += 5.0f * ((float)delta_time);
    model_angle = total_rotation * (float)(PI / 180); //radians

    //frame_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.01f));
    frame_matrix = glm::scale(model_matrix, glm::vec3(m_scale));
    frame_matrix = glm::rotate(frame_matrix, model_angle, glm::vec3(0, 1, 0)); //rotateH
    frame_matrix = glm::rotate(frame_matrix, model_angle, glm::vec3(1, 0, 0)); //rotateP
    frame_matrix = glm::rotate(frame_matrix, model_angle, glm::vec3(0, 0, 1)); //rotateR
}
    
void model::draw(const glm::mat4& view_matrix, const glm::mat4& projection_matrix)
{
    if(!active) return;
    glUseProgram(shader_program);
    
    glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, glm::value_ptr(frame_matrix));
    glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, glm::value_ptr(view_matrix));
    glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, glm::value_ptr(projection_matrix));
    glUniform1i(sampler_loc, 0);
    
    glBindVertexArray(vao);
    
    // SET THE TEXTURE TO ACTIVE AND SET THE TEX PARAMETERS
    // Make texture object active
    glBindTexture( GL_TEXTURE_2D, tex_id );
    on_gl_error("ERROR: Could not bind Texture");
    
    // Set texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    
    // DRAW THE MODEL
    glDrawElements(GL_TRIANGLES, poly_count, GL_UNSIGNED_INT, (GLvoid*)0);
    
    glBindVertexArray(0);
    
    glUseProgram(0);
}

model& model::operator=(const model& other)
{
    if(this != &other)
    {
        model_matrix = other.model_matrix;
        m_scale = other.m_scale;
        frame_matrix = model_matrix;
        verts = other.verts;
        polys = other.polys;
        
        active = other.active;
        
        init();
    }
    
    return *this;
}

void model::scale(const float& factor)
{
    if(factor == 0) return;
    m_scale = factor;
    //frame_matrix = glm::scale(model_matrix, glm::vec3(m_scale));
    //model_matrix = glm::scale(model_matrix, glm::vec3(m_scale));
}

void model::undo_scale()
{
    //model_matrix = glm::scale(model_matrix, glm::vec3(1.0f / m_scale));
    m_scale = 1.0f;
    //frame_matrix = glm::scale(model_matrix, glm::vec3(m_scale));
}

void model::toggle_active()
{
    active = !active;
}

void model::active_off()
{
    active = false;
}

void model::active_on()
{
    active = true;
}
