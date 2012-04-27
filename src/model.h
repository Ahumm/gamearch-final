#include <string>
#include <vector>

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
    GLunit
        shader_program,
        frag_shader,
        vert_shader,
        projection_matrix_loc,
        view_matrix_loc,
        model_matrix_loc,
        vao,
        vbo_vert,
        vbo_poly,
        poly_count,
        vert_count,
        vert_size,
        rgba_offset,
        uv_offset,
        normal_offset,
        poly_rgba_offset;
        
    bool expires;
    bool is_dead;
    double lifespan;
    
    float scale;
    
    vector<vertex> verts;
    vector<int> polys;
    
    string texture;
    
    model();
    model(char* file);
    
    void load_model(char* file);
    
    void init();
    
    GLuint load_shader(const char* filename, GLenum shader_type);
    
    void update(double delta_time);
    
    void draw(glm::mat4& view_matrix, glm::mat4& projection_matrix);
    
    model& operator=(const model& other);
    
    void scale(float & factor);
    
    void undo_scale();
}