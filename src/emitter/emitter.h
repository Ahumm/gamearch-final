#ifndef _EMITTER_H_
#define _EMITTER_H_

#include "controller_functions.h"
#include "particle.h"

#include <stdint.h>
#include <string>
#include <vector>
#include <iostream>
#include <GL/glew.h> //MUST come before GLFW!
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Image.hpp>
#include <glm/glm.hpp> //feel free to use your own math library!
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

class emitter;

// BASIC FUNCTION CONTROLLERS
enum base_emitter_control_types
{
    NO_CONTROLLER ,
    SIN_POS_X , SIN_POS_Y , SIN_POS_Z ,  
    SIN_VEL_X , SIN_VEL_Y , SIN_VEL_Z ,
    SIN_ACC_X , SIN_ACC_Y , SIN_ACC_Z ,
    
    COS_POS_X , COS_POS_Y , COS_POS_Z ,
    COS_VEL_X , COS_VEL_Y , COS_VEL_Z ,
    COS_ACC_X , COS_ACC_Y , COS_ACC_Z ,
    
    EXP_POS_X , EXP_POS_Y , EXP_POS_Z ,
    EXP_VEL_X , EXP_VEL_Y , EXP_VEL_Z ,
    EXP_ACC_X , EXP_ACC_Y , EXP_ACC_Z ,
    
    BUTTERFLY_CURVE_XY , BUTTERFLY_CURVE_XZ , 
    BUTTERFLY_CURVE_YZ , BUTTERFLY_CURVE_FLAT ,
    LOG_SPIRAL_XY , LOG_SPIRAL_XZ ,
    LOG_SPIRAL_YZ , LOG_SPIRAL_FLAT ,
    
    SINE_WAVE_Y_TO_X , COS_WAVE_Y_TO_X , TAN_GRAPH_Y_TO_X ,
    SINH_GRAPH_Y_TO_X , COSH_GRAPH_Y_TO_X , TANH_GRAPH_Y_TO_X ,
    SINE_WAVE_FLAT , COS_WAVE_FLAT , TAN_GRAPH_FLAT, 
    SINH_GRAPH_FLAT , COSH_GRAPH_FLAT , TANH_GRAPH_FLAT ,
    
    WHITE , BLACK , 
    RED , YELLOW , GREEN , CYAN , BLUE , MAGENTA ,
    WHITE_TO_BLACK , BLACK_TO_WHITE ,
    RED_TO_CYAN , YELLOW_TO_BLUE , GREEN_TO_MAGENTA ,
    CYAN_TO_RED , BLUE_TO_YELLOW , MAGENTA_TO_GREEN ,
    
    FADE , UN_FADE , FADE_IN_AND_OUT , FADE_IN_AND_OUT_EDGE ,
    
    COLORED_SINE , COLORED_TAN , COLORED_COSH ,
    
    CIRCLE_XY ,
    
    STEP , GRAVITY_Y , GRAVITY_B , ROTATE ,
    
    ENUM_END
};

typedef struct {
    float position[3];
    float color[4];
} pos_color;

typedef void (*fptr)(vector<particle>::iterator, const emitter*, const double&);
//typedef particle (*sptr)(const double&);

class emitter {
public:
    ///////////////
    // VARIABLES //
    ///////////////
    
    glm::mat4 model_matrix;
    glm::vec4 center;
    glm::mat4 frame_matrix;
    GLuint
        shader_program,
        frag_shader,
        vert_shader,
        u_thickness_loc,
        cam_pos_loc,
        mvp_matrix_loc,
        projection_matrix_loc,
        view_matrix_loc,
        model_matrix_loc,
        sampler_loc,
        vao,
        vbo_part,
        vbo_color,
        tex_id,
        part_size,
        vel_offset,
        accel_offset,
        color_offset,
        lifespan_offset,
        alive_time_offset;
    
    uint32_t
        particle_count,
        generation_speed, // Particles per second
        max_particles; // Maximum Particles to have out
    
    double particle_lifespan;
    float spawn_radius;
    float thickness;
    bool active;
    float base_color[4];
    const static int mass = 1000;
    bool fade;
    
    bool output_spam;
	
    base_emitter_control_types controller;
    
    string current_controller_name;
    
    string texture;
    
    vector<particle> parts;
    vector<fptr> active_controllers;
    uint32_t spawn_controller;
    
    
    //////////////////
    // CONSTRUCTORS //
    //////////////////
    
    emitter();
    emitter(const char* texture_file, const double& lifespan, const uint32_t& count_or_speed, const bool& is_count);
    emitter(const emitter& other);
    ~emitter();
    
    // CONSTRUCTION HELPER
    void init();
    
    
    ///////////////
    // ACCESSORS //
    ///////////////
    
    void set_base_color(const float& r, const float& g, const float& b, const float& a);
    void set_base_color(const float& r, const float& g, const float& b);
    
    void set_spawn_radius(const float& new_spawn_radius);
    
    void toggle_active();
    void active_off();
    void active_on();
    
    void next_spawn_controller();
    void prev_spawn_controller();
    
    void print_status(std::ostream& out, const int& id = -1);
    
    //////////////////////
    // UPDATE FUNCTIONS //
    //////////////////////
    
    void update(const double& delta_time);
    
    void spawn_particle();
    void spawn_quota(const double& delta_time);
    void remove_particle(vector<particle>::iterator& part_it);
    void clear_all_particles();
    
    void switch_controller(const base_emitter_control_types& new_controller);
    void clear_controller();
    void add_controller(const base_emitter_control_types& new_controller);
    
    pos_color* get_data();
    
    ////////////////////
    // DRAW FUNCTIONS //
    ////////////////////
    
    void draw(const glm::mat4& view_matrix, const glm::mat4& projection_matrix, const glm::vec3& cam_pos);
    
    
    ///////////////
    // OPERATORS //
    ///////////////
    
    emitter& operator=(const emitter& other);
};

#endif