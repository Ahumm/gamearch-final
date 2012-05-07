#include "particle.h"

#include <stdio.h>

//////////////////
// CONSTRUCTORS //
//////////////////

particle::particle() : p_position({0.0f, 0.0f, 0.0f}) , p_velocity({0.0f, 0.0f, 0.0f}), p_acceleration({0.0f, 0.0f, 0.0f}), p_color({0.0f, 0.0f, 0.0f, 1.0f}), p_lifespan(1.0), p_alive_time(0.0)
{}

particle::particle(const double& lifespan) : p_position({0.0f, 0.0f, 0.0f}) , p_velocity({0.0f, 0.0f, 0.0f}), p_acceleration({0.0f, 0.0f, 0.0f}), p_color({0.0f, 0.0f, 0.0f, 1.0f}), p_lifespan(lifespan), p_alive_time(0.0)
{}

particle::particle(const float& p_x, const float& p_y, const float& p_z, const double& lifespan)
 : p_position({p_x, p_y, p_z}) , p_velocity({0.0f, 0.0f, 0.0f}), p_acceleration({0.0f, 0.0f, 0.0f}), p_color({0.0f, 0.0f, 0.0f, 1.0f}), p_lifespan(lifespan), p_alive_time(0.0)
{}

particle::particle(const float& p_x, const float& p_y, const float& p_z,
                const float& v_x, const float& v_y, const float& v_z, const double& lifespan)
 : p_position({p_x, p_y, p_z}) , p_velocity({v_x, v_y, v_z}), p_lifespan(lifespan), p_alive_time(0.0)
{}

particle::particle(const float& p_x, const float& p_y, const float& p_z, const float& v_x, const float& v_y, const float& v_z,
                const float& a_x, const float& a_y, const float& a_z, const double& lifespan)
 : p_position({p_x, p_y, p_z}) , p_velocity({v_x, v_y, v_z}), p_acceleration({a_x, a_y, a_z}), p_color({0.0f, 0.0f, 0.0f, 1.0f}), p_lifespan(lifespan), p_alive_time(0.0)
{}

particle::particle(const particle& other)
{
    p_position[0] = other.p_position[0];
    p_position[1] = other.p_position[1];
    p_position[2] = other.p_position[2];
    
    p_velocity[0] = other.p_velocity[0];
    p_velocity[1] = other.p_velocity[1];
    p_velocity[2] = other.p_velocity[2];
    
    p_acceleration[0] = other.p_acceleration[0];
    p_acceleration[1] = other.p_acceleration[1];
    p_acceleration[2] = other.p_acceleration[2];
    
    p_color[0] = other.p_color[0];
    p_color[1] = other.p_color[1];
    p_color[2] = other.p_color[2];
    p_color[3] = other.p_color[3];
    
    p_lifespan = other.p_lifespan;
    p_alive_time = other.p_alive_time;
}


///////////////
// ACCESSORS //
///////////////

void particle::set_color(const float& r, const float& g, const float& b, const float& a)
{
    p_color[0] = (r < 0.0f) ? 0.0f : ((r > 1.0f) ? 1.0f : r);
    p_color[1] = (g < 0.0f) ? 0.0f : ((g > 1.0f) ? 1.0f : g);
    p_color[2] = (b < 0.0f) ? 0.0f : ((b > 1.0f) ? 1.0f : b);
    p_color[3] = (a < 0.0f) ? 0.0f : ((a > 1.0f) ? 1.0f : a);
}

double particle::seconds_alive()
{
    return (p_alive_time / 1000.0);
}


///////////////
// FUNCTIONS //
///////////////

void particle::apply_acceleration(const double& delta_time)
{
    p_velocity[0] += p_acceleration[0] * delta_time / 1000.0f;
    p_velocity[1] += p_acceleration[1] * delta_time / 1000.0f;
    p_velocity[2] += p_acceleration[2] * delta_time / 1000.0f;
}

void particle::apply_velocity(const double& delta_time)
{
    double t = delta_time / 1000.0;
    p_position[0] += p_velocity[0] * t + 0.5 * p_acceleration[0] * t * t;
    p_position[1] += p_velocity[1] * t + 0.5 * p_acceleration[1] * t * t;
    p_position[2] += p_velocity[2] * t + 0.5 * p_acceleration[2] * t * t;
}


///////////////
// OPERATORS //
///////////////

particle& particle::operator=(const particle& other)
{
    if(this != &other)
    {
        p_position[0] = other.p_position[0];
        p_position[1] = other.p_position[1];
        p_position[2] = other.p_position[2];
        
        p_velocity[0] = other.p_velocity[0];
        p_velocity[1] = other.p_velocity[1];
        p_velocity[2] = other.p_velocity[2];
        
        p_acceleration[0] = other.p_acceleration[0];
        p_acceleration[1] = other.p_acceleration[1];
        p_acceleration[2] = other.p_acceleration[2];
        
        p_color[0] = other.p_color[0];
        p_color[1] = other.p_color[1];
        p_color[2] = other.p_color[2];
        p_color[3] = other.p_color[3];
        
        p_lifespan = other.p_lifespan;
        p_alive_time = other.p_alive_time;
    }
    
    return *this;
}