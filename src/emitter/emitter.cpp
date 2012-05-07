#include "emitter.h"
#include "../utils/utils.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp> //feel free to use your own math library!
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>

using namespace std;


//////////////////
// CONSTRUCTORS //
//////////////////

emitter::emitter()
 : base_color({0.0f, 0.0f, 0.0f, 1.0f}), texture("particle.png"), particle_lifespan(1000.0), generation_speed(10), particle_count(0), spawn_radius(1.0f),
    thickness(10.0f), active(false)
{
    model_matrix = glm::mat4(1.0f);
    frame_matrix = model_matrix;
    
    max_particles = ((uint32_t)particle_lifespan) * generation_speed + 1;
    max_particles = (max_particles > MAX_PARTICLES_PER_EMITTER) ? MAX_PARTICLES_PER_EMITTER : max_particles;

    init();
    
    controller = NO_CONTROLLER;
    active_controllers.push_back(controller::fade_in_and_out_edge);
    current_controller_name = "NO_CONTROLLER";
    
    spawn_controller = 0;
	fade = true;
}

// TAKES LIFESPAN IN SECONDS
emitter::emitter(const char* texture_file, const double& lifespan, const uint32_t& spawn_speed)
 : base_color({0.0f, 0.0f, 0.0f, 1.0f}), texture(texture_file), particle_lifespan(1000.0 * lifespan),
    generation_speed(spawn_speed), particle_count(0), spawn_radius(1.0f), thickness(10.0f), active(true)
{
    model_matrix = glm::mat4(1.0f);
    frame_matrix = model_matrix;
    
    max_particles = ((uint32_t)particle_lifespan) * generation_speed + 1;
    max_particles = (max_particles > MAX_PARTICLES_PER_EMITTER) ? MAX_PARTICLES_PER_EMITTER : max_particles;
    
    init();
    
    controller = NO_CONTROLLER;
    active_controllers.push_back(controller::fade_in_and_out_edge);
    current_controller_name = "NO_CONTROLLER";
    
    spawn_controller = 0;
	fade = true;
}

emitter::emitter(const emitter& other)
 : texture(other.texture), particle_lifespan(other.particle_lifespan), generation_speed(other.generation_speed),
    max_particles(other.max_particles), particle_count(other.particle_count), spawn_radius(other.spawn_radius),
    thickness(other.thickness), active(other.active), parts(other.parts)
{
    model_matrix = other.model_matrix;
    frame_matrix = model_matrix;
    
    base_color[0] = other.base_color[0];
    base_color[1] = other.base_color[1];
    base_color[2] = other.base_color[2];
    base_color[3] = other.base_color[3];

    init();
    
    controller = other.controller;
    current_controller_name = other.current_controller_name;
    active_controllers = other.active_controllers;
    spawn_controller = other.spawn_controller;
	fade = other.fade;
}

emitter::~emitter() {}

void emitter::init()
{
    particle p;
    part_size           =                     (GLuint)sizeof(p               );
    vel_offset          =                     (GLuint)sizeof(p.p_position    );
    accel_offset        = vel_offset        + (GLuint)sizeof(p.p_velocity    );
    color_offset        = accel_offset      + (GLuint)sizeof(p.p_acceleration);
    lifespan_offset     = color_offset      + (GLuint)sizeof(p.p_color       );
    alive_time_offset   = lifespan_offset   + (GLuint)sizeof(p.p_lifespan    );
    
    shader_program = glCreateProgram();
    on_gl_error("ERROR: Could not create the shader program");
    
    frag_shader = load_shader("shaders/emitter.fs", GL_FRAGMENT_SHADER);
    check_shader(frag_shader);
    vert_shader = load_shader("shaders/emitter.vs", GL_VERTEX_SHADER);
    check_shader(vert_shader);
    
    glAttachShader(shader_program, frag_shader);
    glAttachShader(shader_program, vert_shader);
    
    glBindAttribLocation(shader_program, 0, "in_Position");
	glBindAttribLocation(shader_program, 1, "in_Color");
    
    glLinkProgram(shader_program);
    
    glUseProgram(shader_program);
    
    mvp_matrix_loc = glGetUniformLocation(shader_program, "MVPMatrix");
    cam_pos_loc = glGetUniformLocation(shader_program, "cam_pos");
    u_thickness_loc = glGetUniformLocation(shader_program, "uThickness");
    sampler_loc = glGetUniformLocation(shader_program, "s_tex");
    
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);
    
    glGenBuffers(1, &vbo_part);
    //glGenBuffers(1, &vbo_color);
    on_gl_error("ERROR: Could not generate the buffer objects");
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo_part);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos_color) * max_particles, NULL, GL_DYNAMIC_DRAW);
    
    //glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
    //glBufferData(GL_ARRAY_BUFFER, part_size * max_particles, &(parts[0]), GL_DYNAMIC_DRAW);
    
    //glBufferData(GL_ARRAY_BUFFER, part_size * max_particles, &(parts[0]), GL_STATIC_DRAW);
    // glBufferData with a null data just initializes that much memory (particle is 
    //glBufferData(GL_ARRAY_BUFFER, max_particles * sizeof(pos_color), (GLvoid*)0, GL_DYNAMIC_DRAW);
    on_gl_error("ERROR: Could not bind the VBO to the VAO");
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    on_gl_error("ERROR: Could not enable vertex attributes");
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(pos_color), (GLvoid*)0);             // Position
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(pos_color), (GLvoid*)(sizeof(float) * 3));  // Color
    on_gl_error("ERROR: Could not set VAO attributes");
    
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, poly_size * poly_count, &(polys[0]), GL_STATIC_DRAW);
    on_gl_error("ERROR: Could not bind the IBO to the VAO");
    
    //glDisableVertexAttribArray(0);
    //glDisableVertexAttribArray(1);
    
    // Generate texture objects
    glGenTextures( 1, &tex_id );

    // Make texture object active
    glBindTexture( GL_TEXTURE_2D, tex_id );
    on_gl_error("ERROR: Could not bind Texture");
    
    // Set texture parameters
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    //glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    on_gl_error("ERROR: Could not set Texture parameters");
    
    // Upload texture from file to texture memory, autouses glTexImage2D, needs TGA
    sf::Image img;
    //if(!img.loadFromFile("textures/" + texture))
    if(!img.loadFromFile(texture))
    {
        fprintf( stderr, "Failed to load texture" );
        fprintf( stdout, "Failed to load texture" );
        throw 1;
    }
    
    img.flipVertically();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr());
    on_gl_error("ERROR: Could not load Texture");

    // DISABLE POINT SPRITES
    //glDisable(GL_POINT_SPRITE);
    //glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
    //glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_FALSE);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}


///////////////
// ACCESSORS //
///////////////

void emitter::set_base_color(const float& r, const float& g, const float& b, const float& a)
{
    base_color[0] = (r < 0.0f) ? 0.0f : ((r > 1.0f) ? 1.0f : r);
    base_color[1] = (g < 0.0f) ? 0.0f : ((g > 1.0f) ? 1.0f : g);
    base_color[2] = (b < 0.0f) ? 0.0f : ((b > 1.0f) ? 1.0f : b);
    base_color[3] = (a < 0.0f) ? 0.0f : ((a > 1.0f) ? 1.0f : a);
}

void emitter::set_base_color(const float& r, const float& g, const float& b)
{
    set_base_color(r, g, b, base_color[3]);
}

void emitter::set_spawn_radius(const float& new_spawn_radius)
{
    spawn_radius = new_spawn_radius;
}

void emitter::toggle_active()
{
    active = !active;
}

void emitter::active_off()
{
    active = false;
}

void emitter::active_on()
{
    active = true;
}

void emitter::next_spawn_controller()
{
    ++spawn_controller;
    if(spawn_controller >= spawner::num_spawn_controllers) spawn_controller = 0;
}
void emitter::prev_spawn_controller()
{
    if(spawn_controller == 0) spawn_controller = spawner::num_spawn_controllers - 1;
    else --spawn_controller;
    
}


//////////////////////
// UPDATE FUNCTIONS //
//////////////////////

void emitter::update(const double& delta_time)
{
    // DON'T RUN UPDATE IF INACTIVE AND THERE ARE NO PARTICLES (DO RUN IF INACTIVE AND THERE ARE PARTICLES)
    if(!active)
    {
        clear_all_particles();
        return;
    }
    
    // IF ACTIVE, SPAWN MORE PARTICLES
    spawn_quota(delta_time);
    
    // PROCESS OVER ALL PARTICLES
    vector<particle>::iterator it = parts.begin();
    while(it != parts.end())
    {
        // ADD DECAY
        it->p_alive_time += delta_time;
        // PARTICLE EXPIRED, REMOVE
        if(it->p_alive_time > particle_lifespan)
        {
            //fprintf(stdout, "Removing Node\n");
            remove_particle(it);
        }
        else
        {
            // RUN FUNCTIONS, APPLY VELOCITY AND ACCELERATION
            for(size_t i = 0; i < active_controllers.size(); ++i)
            {
                active_controllers[i](it, this, delta_time);
            }
            
            it->apply_acceleration(delta_time);
            it->apply_velocity(delta_time);
            ++it;
        }
    }
    
    // UPDATE THE FRAME MATRIX (LEGACY)
    frame_matrix = model_matrix;
    // Update the center
    center = frame_matrix * glm::vec4(0.0f,0.0f,0.0f,1.0f);
    
    glBindVertexArray(vao);
    pos_color* temp_data = get_data();
    glBindBuffer(GL_ARRAY_BUFFER, vbo_part);
    glBufferSubData(GL_ARRAY_BUFFER, 0, parts.size() * sizeof(pos_color), temp_data);
    //glBufferData(GL_ARRAY_BUFFER, parts.size() * sizeof(pos_color), temp_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
    delete [] temp_data;
}

void emitter::spawn_particle()
{
    // CREATE A PARTICLE, ADD IT TO THE VECTOR, INCREMENT PARTICLE_COUNT
    particle p = spawner::spawn_controllers[spawn_controller](particle_lifespan, this);
    parts.push_back(p);
    ++particle_count;
}

void emitter::spawn_quota(const double& delta_time)
{
    // DON'T SPAWN IF WE HAVE NO ROOM
    if(!(particle_count < max_particles)) return;

    // CALCULATE NUMBER OF UNITS TO SPAWN
    uint32_t quota = ((generation_speed * delta_time) / 1000) + 1;
    
    // SPAWN AS MANY PARTICLES AS WE CAN UP TO QUOTA
    for(uint32_t i = 0; (particle_count < max_particles) && i < quota; ++i)
    {
        spawn_particle();
    }
}

void emitter::remove_particle(vector<particle>::iterator& part_it)
{
    // REMOVE THE PARTICLE FROM THE VECTOR, DECREMENT PARTICLE_COUNT
    part_it = parts.erase(part_it);
    --particle_count;
}

void emitter::clear_all_particles()
{
    parts.clear();
    particle_count = 0;
}

void emitter::switch_controller(const base_emitter_control_types& new_controller)
{
    if(controller == new_controller) return;
    clear_controller();
    add_controller(new_controller);
    controller = new_controller;
}

void emitter::clear_controller()
{
    // CLEAR VECTOR OF FUNCTION POINTERS
    controller = NO_CONTROLLER;
    current_controller_name = "NO_CONTROLLER";
    active_controllers.clear();
    // RESET (DESTROY ALL PARTICLES)
    clear_all_particles();
}


////////////////////
// DRAW FUNCTIONS //
////////////////////

void emitter::draw(const glm::mat4& view_matrix, const glm::mat4& projection_matrix, const glm::vec3& cam_pos)
{
    // DON'T DRAW IF INACTIVE OR NO PARTICLES TO DRAW
    if(!active || !(particle_count > 0)) return;
    glUseProgram(shader_program);
    
    glEnable(GL_TEXTURE_2D);
    
    glm::mat4 mvp_matrix = projection_matrix * view_matrix * frame_matrix;
    
    glUniformMatrix4fv(mvp_matrix_loc, 1, GL_FALSE, glm::value_ptr(mvp_matrix));
    glUniform3fv(cam_pos_loc, 1, glm::value_ptr(cam_pos));
    //glUniformMatrix4fv(model_matrix_loc, 1, GL_FALSE, glm::value_ptr(frame_matrix));
    //glUniformMatrix4fv(view_matrix_loc, 1, GL_FALSE, glm::value_ptr(view_matrix));
    //glUniformMatrix4fv(projection_matrix_loc, 1, GL_FALSE, glm::value_ptr(projection_matrix));
    glUniform1f(u_thickness_loc, thickness);
    glUniform1i(sampler_loc, 0);
    
    // SET THE VAO TO ACTIVE
    glBindVertexArray(vao);
    
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBindTexture(GL_TEXTURE_2D, tex_id);
    
    // ENABLE BLENDING OPTIONS
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glEnable(GL_POINT_SPRITE);
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glDrawArrays(GL_POINTS, 0, parts.size());
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
   
    on_gl_error("ERROR: Could not enable vertex attributes");
    
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_POINT_SPRITE);
    glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
    
    glBindVertexArray(0);
    
    glDisable(GL_TEXTURE_2D);
    
    glUseProgram(0);
}


///////////////
// OPERATORS //
///////////////


// SIMPLE ASSIGNMENT OPERATOR
emitter& emitter::operator=(const emitter& other)
{
    if(this != &other)
    {
        model_matrix = other.model_matrix;
        frame_matrix = model_matrix;
        texture = other.texture;
        particle_lifespan = other.particle_lifespan;
        generation_speed = other.generation_speed;
        
        max_particles = other.max_particles;
        
        particle_count = other.particle_count;
        spawn_radius = other.spawn_radius;
        thickness = other.thickness;
        
        base_color[0] = other.base_color[0];
        base_color[1] = other.base_color[1];
        base_color[2] = other.base_color[2];
        base_color[3] = other.base_color[3];
    
        active = other.active;

        parts = other.parts;
        
        init();
        
        controller = other.controller;
        current_controller_name = other.current_controller_name;
        active_controllers = other.active_controllers;
        spawn_controller = other.spawn_controller;
		fade = other.fade;
    }
    
    return *this;
}

pos_color* emitter::get_data()
{
    pos_color* temp_data = new pos_color[parts.size()];
    vector<particle>::iterator it = parts.begin();
    size_t i = 0;
    while(it != parts.end())
    {
        memcpy(temp_data[i].position, it->p_position, sizeof(float) * 3);
        memcpy(temp_data[i].color, it->p_color, sizeof(float) * 4);
        ++i;
        ++it;
    }
    
    return temp_data;
}


void emitter::add_controller(const base_emitter_control_types& new_controller)
{
    bool auto_fade = true;
    switch(new_controller)
    {
        // SIN //
        case SIN_POS_X:
            active_controllers.push_back(controller::sin_pos_x);
            current_controller_name = "SIN_POS_X";
            break;
        case SIN_POS_Y:
            active_controllers.push_back(controller::sin_pos_y);
            current_controller_name = "SIN_POS_Y";
            break;
        case SIN_POS_Z:
            active_controllers.push_back(controller::sin_pos_z);
            current_controller_name = "SIN_POS_Z";
            break;
        case SIN_VEL_X:
            active_controllers.push_back(controller::sin_vel_x);
            current_controller_name = "SIN_VEL_X";
            break;
        case SIN_VEL_Y:
            active_controllers.push_back(controller::sin_vel_y);
            current_controller_name = "SIN_VEL_Y";
            break;
        case SIN_VEL_Z:
            active_controllers.push_back(controller::sin_vel_z);
            current_controller_name = "SIN_VEL_Z";
            break;
        case SIN_ACC_X:
            active_controllers.push_back(controller::sin_acc_x);
            current_controller_name = "SIN_ACC_X";
            break;
        case SIN_ACC_Y:
            active_controllers.push_back(controller::sin_acc_y);
            current_controller_name = "SIN_ACC_Y";
            break;
        case SIN_ACC_Z:
            active_controllers.push_back(controller::sin_acc_z);
            current_controller_name = "SIN_ACC_Z";
            break;
        
        // COS //
        case COS_POS_X:
            active_controllers.push_back(controller::cos_pos_x);
            current_controller_name = "COS_POS_X";
            break;
        case COS_POS_Y:
            active_controllers.push_back(controller::cos_pos_y);
            current_controller_name = "COS_POS_Y";
            break;
        case COS_POS_Z:
            active_controllers.push_back(controller::cos_pos_z);
            current_controller_name = "COS_POS_Z";
            break;
        case COS_VEL_X:
            active_controllers.push_back(controller::cos_vel_x);
            current_controller_name = "COS_VEL_X";
            break;
        case COS_VEL_Y:
            active_controllers.push_back(controller::cos_vel_y);
            current_controller_name = "COS_VEL_Y";
            break;
        case COS_VEL_Z:
            active_controllers.push_back(controller::cos_vel_z);
            current_controller_name = "COS_VEL_Z";
            break;
        case COS_ACC_X:
            active_controllers.push_back(controller::cos_acc_x);
            current_controller_name = "COS_ACC_X";
            break;
        case COS_ACC_Y:
            active_controllers.push_back(controller::cos_acc_y);
            current_controller_name = "COS_ACC_Y";
            break;
        case COS_ACC_Z:
            active_controllers.push_back(controller::cos_acc_z);
            current_controller_name = "COS_ACC_Z";
            break;
            
        // EXP //    
        case EXP_POS_X:
            active_controllers.push_back(controller::exp_pos_x);
            current_controller_name = "EXP_POS_X";
            break;
        case EXP_POS_Y:
            active_controllers.push_back(controller::exp_pos_y);
            current_controller_name = "EXP_POS_Y";
            break;
        case EXP_POS_Z:
            active_controllers.push_back(controller::exp_pos_z);
            current_controller_name = "EXP_POS_Z";
            break;
        case EXP_VEL_X:
            active_controllers.push_back(controller::exp_vel_x);
            current_controller_name = "EXP_VEL_X";
            break;
        case EXP_VEL_Y:
            active_controllers.push_back(controller::exp_vel_y);
            current_controller_name = "EXP_VEL_Y";
            break;
        case EXP_VEL_Z:
            active_controllers.push_back(controller::exp_vel_z);
            current_controller_name = "EXP_VEL_Z";
            break;
        case EXP_ACC_X:
            active_controllers.push_back(controller::exp_acc_x);
            current_controller_name = "EXP_ACC_X";
            break;
        case EXP_ACC_Y:
            active_controllers.push_back(controller::exp_acc_y);
            current_controller_name = "EXP_ACC_Y";
            break;
        case EXP_ACC_Z:
            active_controllers.push_back(controller::exp_acc_z);
            current_controller_name = "EXP_ACC_Z";
            break;
            
        // BUTTERFLY_CURVE
        case BUTTERFLY_CURVE_XY:
            active_controllers.push_back(controller::butterfly_curve_xy);
            current_controller_name = "BUTTERFLY_CURVE_XY";
            break;
        case BUTTERFLY_CURVE_XZ:
            active_controllers.push_back(controller::butterfly_curve_xz);
            current_controller_name = "BUTTERFLY_CURVE_XZ";
            break;
        case BUTTERFLY_CURVE_YZ:
            active_controllers.push_back(controller::butterfly_curve_yz);
            current_controller_name = "BUTTERFLY_CURVE_YZ";
            break;
        case BUTTERFLY_CURVE_FLAT:
            active_controllers.push_back(controller::butterfly_curve_xy);
            active_controllers.push_back(controller::zero_all_z);
            current_controller_name = "BUTTERFLY_CURVE_FLAT";
            break;
        
        // LOG_SPIRAL
        case LOG_SPIRAL_XY:
            active_controllers.push_back(controller::log_spiral_xy);
            current_controller_name = "LOG_SPIRAL_XY";
            break;
        case LOG_SPIRAL_XZ:
            active_controllers.push_back(controller::log_spiral_xz);
            current_controller_name = "LOG_SPIRAL_XZ";
            break;
        case LOG_SPIRAL_YZ:
            active_controllers.push_back(controller::log_spiral_yz);
            current_controller_name = "LOG_SPIRAL_YZ";
            break;
        case LOG_SPIRAL_FLAT:
            active_controllers.push_back(controller::log_spiral_xy);
            active_controllers.push_back(controller::zero_all_z);
            current_controller_name = "LOG_SPIRAL_FLAT";
            break;
            
        // SINE
        case SINE_WAVE_Y_TO_X:
            active_controllers.push_back(controller::sine_wave_y_to_x);
            current_controller_name = "SINE_WAVE_Y_TO_X";
            break;
        // COS
        case COS_WAVE_Y_TO_X:
            active_controllers.push_back(controller::cos_wave_y_to_x);
            current_controller_name = "COS_WAVE_Y_TO_X";
            break;
        // TAN
        case TAN_GRAPH_Y_TO_X:
            active_controllers.push_back(controller::tan_graph_y_to_x);
            current_controller_name = "TAN_GRAPH_Y_TO_X";
            break;
        // SINH
        case SINH_GRAPH_Y_TO_X:
            active_controllers.push_back(controller::sinh_graph_y_to_x);
            current_controller_name = "SINH_GRAPH_Y_TO_X";
            break;
        // COSH
        case COSH_GRAPH_Y_TO_X:
            active_controllers.push_back(controller::cosh_graph_y_to_x);
            current_controller_name = "COSH_GRAPH_Y_TO_X";
            break;
        // TANH
        case TANH_GRAPH_Y_TO_X:
            active_controllers.push_back(controller::tanh_graph_y_to_x);
            current_controller_name = "TANH_GRAPH_Y_TO_X";
            break;
        // SINE_FLAT
        case SINE_WAVE_FLAT:
            active_controllers.push_back(controller::sine_wave_y_to_x);
            active_controllers.push_back(controller::zero_all_z);
            current_controller_name = "SINE_WAVE_FLAT";
            break;
        // COS_FLAT
        case COS_WAVE_FLAT:
            active_controllers.push_back(controller::cos_wave_y_to_x);
            active_controllers.push_back(controller::zero_all_z);
            current_controller_name = "COS_WAVE_FLAT";
            break;
        // TAN_FLAT
        case TAN_GRAPH_FLAT:
            active_controllers.push_back(controller::tan_graph_y_to_x);
            active_controllers.push_back(controller::zero_all_z);
            current_controller_name = "TAN_GRAPH_FLAT";
            break;
        // SINH_FLAT
        case SINH_GRAPH_FLAT:
            active_controllers.push_back(controller::sinh_graph_y_to_x);
            active_controllers.push_back(controller::zero_all_z);
            current_controller_name = "SINH_GRAPH_FLAT";
            break;
        // COSH_FLAT
        case COSH_GRAPH_FLAT:
            active_controllers.push_back(controller::cosh_graph_y_to_x);
            active_controllers.push_back(controller::zero_all_z);
            current_controller_name = "COSH_GRAPH_FLAT";
            break;
        // TANH_FLAT
        case TANH_GRAPH_FLAT:
            active_controllers.push_back(controller::tanh_graph_y_to_x);
            active_controllers.push_back(controller::zero_all_z);
            current_controller_name = "TANH_GRAPH_FLAT";
            break;
            
        // BASE_COLORS
        case WHITE:
            active_controllers.push_back(controller::white);
            current_controller_name = "WHITE";
            break;
        case BLACK:
            active_controllers.push_back(controller::black);
            current_controller_name = "BLACK";
            break;
        case RED:
            active_controllers.push_back(controller::red);
            current_controller_name = "RED";
            break;
        case YELLOW:
            active_controllers.push_back(controller::yellow);
            current_controller_name = "YELLOW";
            break;
        case GREEN:
            active_controllers.push_back(controller::green);
            current_controller_name = "GREEN";
            break;
        case CYAN:
            active_controllers.push_back(controller::cyan);
            current_controller_name = "CYAN";
            break;
        case BLUE:
            active_controllers.push_back(controller::blue);
            current_controller_name = "BLUE";
            break;
        case MAGENTA:
            active_controllers.push_back(controller::magenta);
            current_controller_name = "MAGENTA";
            break;
            
        // COLOR_TRANSITIONS
        case WHITE_TO_BLACK:
            active_controllers.push_back(controller::white_to_black);
            current_controller_name = "WHITE_TO_BLACK";
            break;
        case BLACK_TO_WHITE:
            active_controllers.push_back(controller::black_to_white);
            current_controller_name = "BLACK_TO_WHITE";
            break;
        case RED_TO_CYAN:
            active_controllers.push_back(controller::red_to_cyan);
            current_controller_name = "RED_TO_CYAN";
            break;
        case YELLOW_TO_BLUE:
            active_controllers.push_back(controller::yellow_to_blue);
            current_controller_name = "YELLOW_TO_BLUE";
            break;
        case GREEN_TO_MAGENTA:
            active_controllers.push_back(controller::green_to_magenta);
            current_controller_name = "GREEN_TO_MAGENTA";
            break;
        case CYAN_TO_RED:
            active_controllers.push_back(controller::cyan_to_red);
            current_controller_name = "CYAN_TO_RED";
            break;
        case BLUE_TO_YELLOW:
            active_controllers.push_back(controller::blue_to_yellow);
            current_controller_name = "BLUE_TO_YELLOW";
            break;
        case MAGENTA_TO_GREEN:
            active_controllers.push_back(controller::magenta_to_green);
            current_controller_name = "MAGENTA_TO_GREEN";
            break;
        
        // ALPHA_CHANGES
        case FADE:
            active_controllers.push_back(controller::fade);
            current_controller_name = "FADE";
            auto_fade = false;
            break;
        case UN_FADE:
            active_controllers.push_back(controller::un_fade);
            current_controller_name = "UN_FADE";
            auto_fade = false;
            break;
        case FADE_IN_AND_OUT:
            active_controllers.push_back(controller::fade_in_and_out);
            current_controller_name = "FADE_IN_AND_OUT";
            auto_fade = false;
            break;
        case FADE_IN_AND_OUT_EDGE:
            active_controllers.push_back(controller::fade_in_and_out_edge);
            current_controller_name = "FADE_IN_AND_OUT_EDGE";
            auto_fade = false;
            break;
            
        // COLORED TRIG
        case COLORED_SINE:
            active_controllers.push_back(controller::sine_wave_y_to_x);
            active_controllers.push_back(controller::red_to_cyan);
            current_controller_name = "COLORED_SINE";
            break;
        // TAN
        case COLORED_TAN:
            active_controllers.push_back(controller::tan_graph_y_to_x);
            active_controllers.push_back(controller::yellow_to_blue);
            current_controller_name = "COLORED_TAN";
            break;
        // COSH
        case COLORED_COSH:
            active_controllers.push_back(controller::cosh_graph_y_to_x);
            active_controllers.push_back(controller::green_to_magenta);
            current_controller_name = "COLORED_COSH";
            break;
        case CIRCLE_XY:
            active_controllers.push_back(controller::circle_xy);
            current_controller_name = "CIRCLE_XY";
            break;
        case STEP:
            active_controllers.push_back(controller::step);
            current_controller_name = "STEP";
            break;
        case GRAVITY_Y:
            active_controllers.push_back(controller::gravity_y);
            current_controller_name = "GRAVITY_Y";
            break;
        case GRAVITY_B:
            active_controllers.push_back(controller::gravity_b);
            current_controller_name = "GRAVITY_B";
            break;
        case ROTATE:
            active_controllers.push_back(controller::rotate);
            current_controller_name = "ROTATE";
            break;
        default:
            break;
    }
    if(auto_fade && fade)
        active_controllers.push_back(controller::fade_in_and_out_edge);
    
}


