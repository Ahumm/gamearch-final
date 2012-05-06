#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "../utils/utils.h"

class particle {
public:
    ///////////////
    // VARIABLES //
    ///////////////
    
    float p_position[3];
    float p_velocity[3];
    float p_acceleration[3];
    float p_color[4];
    double p_lifespan;
    double p_alive_time;
    
    
    //////////////////
    // CONSTRUCTORS //
    //////////////////
    
    particle();
    particle(const double& lifespan);
    particle(const float& p_x, const float& p_y, const float& p_z, const double& lifespan);
    particle(const float& p_x, const float& p_y, const float& p_z,
             const float& v_x, const float& v_y, const float& v_z, const double& lifespan);
    particle(const float& p_x, const float& p_y, const float& p_z,
             const float& v_x, const float& v_y, const float& v_z,
             const float& a_x, const float& a_y, const float& a_z, const double& lifespan);
    particle(const particle& other);

    
    ///////////////
    // ACCESSORS //
    ///////////////
    
    void set_color(const float& r, const float& g, const float& b, const float& a = 1.0f);
    double seconds_alive();
    
    ///////////////
    // FUNCTIONS //
    ///////////////
    
    void apply_acceleration(const double& delta_time);
    void apply_velocity(const double& delta_time);
    
    
    ///////////////
    // OPERATORS //
    ///////////////
    
    particle& operator=(const particle& other);
    
    
};

#endif