#ifndef _MODEL_H_
#define _MODEL_H_

#include <string>
#include <vector>
#include <GL/glew.h> //MUST come before GLFW!
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <glm/glm.hpp> //feel free to use your own math library!
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

typedef struct {
    float position[4];
    float rgba[4];
    float uv[2];
    float normal[4];
} vertex;

const vertex base_vertex = {0.0f,0.0f,0.0f,1.0f,
                     0.0f,0.0f,0.0f,1.0f,
                     0.0f,0.0f,
                     0.0f,0.0f,0.0f,0.0f};

class model {
public:
    glm::mat4 model_matrix;
    glm::mat4 frame_matrix;
    GLuint
        shader_program,
        frag_shader,
        vert_shader,
        projection_matrix_loc,
        view_matrix_loc,
        model_matrix_loc,
        sampler_loc,
        vao,
        vbo_vert,
        vbo_poly,
        tex_id,
        poly_count,
        vert_count,
        vert_size,
        poly_size,
        rgba_offset,
        uv_offset,
        normal_offset,
        poly_rgba_offset;
    
    float total_rotation;
    
    float m_scale;
    
    bool active;
    bool rotate;
    
    vector<vertex> verts;
    vector<int> polys;
    
    string texture;
    
    model();
    model(const char* file);
    
    void load_model(const char* path);
    
    void init();
    
    void update(const double& delta_time);
    
    void draw(const glm::mat4& view_matrix, const glm::mat4& projection_matrix);
    
    model& operator=(const model& other);
    
    void scale(const float& factor);
    
    void undo_scale();
    
    void toggle_active();
    void active_off();
    void active_on();
};

#endif