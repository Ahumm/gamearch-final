#include "controller_functions.h"

#include <math.h>
#include <time.h>

namespace controller {
    // SIN
    void sin_pos_x(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_position[0] = sin(part_it->seconds_alive()); }
    void sin_pos_y(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_position[1] = sin(part_it->seconds_alive()); }
    void sin_pos_z(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_position[2] = sin(part_it->seconds_alive()); }
        
    void sin_vel_x(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_velocity[0] = sin(part_it->seconds_alive()); }
    void sin_vel_y(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_velocity[1] = sin(part_it->seconds_alive()); }
    void sin_vel_z(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_velocity[2] = sin(part_it->seconds_alive()); }
        
    void sin_acc_x(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_acceleration[0] = sin(part_it->seconds_alive()); }
    void sin_acc_y(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_acceleration[1] = sin(part_it->seconds_alive()); }
    void sin_acc_z(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_acceleration[2] = sin(part_it->seconds_alive()); }
    
    // COS
    void cos_pos_x(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_position[0] = cos(part_it->seconds_alive()); }
    void cos_pos_y(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_position[1] = cos(part_it->seconds_alive()); }
    void cos_pos_z(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_position[2] = cos(part_it->seconds_alive()); }
        
    void cos_vel_x(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_velocity[0] = cos(part_it->seconds_alive()); }
    void cos_vel_y(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_velocity[1] = cos(part_it->seconds_alive()); }
    void cos_vel_z(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_velocity[2] = cos(part_it->seconds_alive()); }

    void cos_acc_x(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_acceleration[0] = cos(part_it->seconds_alive()); }
    void cos_acc_y(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_acceleration[1] = cos(part_it->seconds_alive()); }
    void cos_acc_z(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_acceleration[2] = cos(part_it->seconds_alive()); }
        
    // EXP
    void exp_pos_x(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_position[0] = exp(part_it->seconds_alive()); }
    void exp_pos_y(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_position[1] = exp(part_it->seconds_alive()); }
    void exp_pos_z(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_position[2] = exp(part_it->seconds_alive()); }
    
    void exp_vel_x(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_velocity[0] = exp(part_it->seconds_alive()); }
    void exp_vel_y(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_velocity[1] = exp(part_it->seconds_alive()); }
    void exp_vel_z(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_velocity[2] = exp(part_it->seconds_alive()); }
    
    void exp_acc_x(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_acceleration[0] = exp(part_it->seconds_alive()); }
    void exp_acc_y(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_acceleration[1] = exp(part_it->seconds_alive()); }
    void exp_acc_z(vector<particle>::iterator part_it, const double& delta_time)
        { part_it->p_acceleration[2] = exp(part_it->seconds_alive()); }
        
    // BUTTERFLY CURVE
    void butterfly_curve_xy(vector<particle>::iterator part_it, const double& delta_time)
    {
        float t = (float)part_it->seconds_alive();
        t = fmodf(abs(t), 2 * PI);
        float co = cos(t);
        float si = sin(t);
        float si_12 = sin(t / 12.0f);
        float final = (exp(co) - (2.0f * cos(4.0f * t)) - pow(si_12, 5.0f));
        
        part_it->p_position[0] = si * final;
        part_it->p_position[1] = co * final;
    }
    void butterfly_curve_xz(vector<particle>::iterator part_it, const double& delta_time)
    {
        float t = (float)part_it->seconds_alive();
        t = fmodf(abs(t), 2 * PI);
        float co = cos(t);
        float si = sin(t);
        float si_12 = sin(t / 12.0f);
        float final = (exp(co) - (2.0f * cos(4.0f * t)) - pow(si_12, 5.0f));
        
        part_it->p_position[0] = si * final;
        part_it->p_position[2] = co * final;
    }
    void butterfly_curve_yz(vector<particle>::iterator part_it, const double& delta_time)
    {
        float t = (float)part_it->seconds_alive();
        t = fmodf(abs(t), 2 * PI);
        float co = cos(t);
        float si = sin(t);
        float si_12 = sin(t / 12.0f);
        float final = (exp(co) - (2.0f * cos(4.0f * t)) - pow(si_12, 5.0f));
        
        part_it->p_position[1] = si * final;
        part_it->p_position[2] = co * final;
    }
    void butterfly_curve_flat(vector<particle>::iterator part_it, const double& delta_time)
    {
        float t = (float)part_it->seconds_alive();
        t = fmodf(abs(t), 2 * PI);
        float co = cos(t);
        float si = sin(t);
        float si_12 = sin(t / 12.0f);
        float final = (exp(co) - (2.0f * cos(4.0f * t)) - pow(si_12, 5.0f));
        
        part_it->p_position[0] = si * final;
        part_it->p_position[1] = co * final;
        part_it->p_position[2] = 0.0f;
    }
    
    // Log Spiral
    void log_spiral_xy(vector<particle>::iterator part_it, const double& delta_time)
    {
        float a = 0.2, b = 0.5, t = (float)part_it->seconds_alive();
        t = fmodf(abs(t), 2 * PI);
        part_it->p_position[0] = a * cos(t) * exp(b * t);
        part_it->p_position[1] = a * sin(t) * exp(b * t);
    }
    
    void log_spiral_xz(vector<particle>::iterator part_it, const double& delta_time)
    {
        float a = 0.2, b = 0.5, t = (float)part_it->seconds_alive();
        part_it->p_position[0] = a * cos(t) * exp(b * t);
        part_it->p_position[2] = a * sin(t) * exp(b * t);
    }
    
    void log_spiral_yz(vector<particle>::iterator part_it, const double& delta_time)
    {
        float a = 0.2, b = 0.5, t = (float)part_it->seconds_alive();
        part_it->p_position[1] = a * cos(t) * exp(b * t);
        part_it->p_position[2] = a * sin(t) * exp(b * t);
    }
	
	// SINE_WAVE
	void sine_wave_y_to_x(vector<particle>::iterator part_it, const double& delta_time)
	{
		part_it->p_position[0] = sin(part_it->p_position[1]);
		part_it->p_velocity[0] = part_it->p_velocity[2];
		part_it->p_acceleration[0] = part_it->p_acceleration[1] = part_it->p_acceleration[2] = 0.0f;
		
		part_it->p_velocity[1] = 1.0f;
	}
    // TAN_GRAPH
	void tan_graph_y_to_x(vector<particle>::iterator part_it, const double& delta_time)
	{
		part_it->p_position[0] = tan(part_it->p_position[1]);
		part_it->p_velocity[0] = part_it->p_velocity[2];
		part_it->p_acceleration[0] = part_it->p_acceleration[1] = part_it->p_acceleration[2] = 0.0f;
		
		part_it->p_velocity[1] = 1.0f;
	}
    // COSH_GRAPH
	void cosh_graph_y_to_x(vector<particle>::iterator part_it, const double& delta_time)
	{
		part_it->p_position[0] = cosh(part_it->p_position[1]);
		part_it->p_velocity[0] = part_it->p_velocity[2];
		part_it->p_acceleration[0] = part_it->p_acceleration[1] = part_it->p_acceleration[2] = 0.0f;
		
		part_it->p_velocity[1] = 1.0f;
	}
    
    // COLOR_TRANSITIONS
    void red_to_yellow(vector<particle>::iterator part_it, const double& delta_time)
    {
        float k = (float)(part_it->p_alive_time) / (float)(part_it->p_lifespan);
        part_it->p_color[0] = 1.0f;
        part_it->p_color[1] = lerp(0.0f, 1.0f, k);
        part_it->p_color[2] = 0.0f;
        part_it->p_color[3] = 1.0f;
    }
    void yellow_to_blue(vector<particle>::iterator part_it, const double& delta_time)
    {
        float k = (float)(part_it->p_alive_time) / (float)(part_it->p_lifespan);
        part_it->p_color[0] = lerp(1.0f, 0.0f, k);
        part_it->p_color[1] = lerp(1.0f, 0.0f, k);
        part_it->p_color[2] = lerp(0.0f, 1.0f, k);
        part_it->p_color[3] = 1.0f;
    }
    void blue_to_red(vector<particle>::iterator part_it, const double& delta_time)
    {
        float k = (float)(part_it->p_alive_time) / (float)(part_it->p_lifespan);
        fprintf(stdout, "%f / %f = %f\n", (float)(part_it->p_alive_time), (float)(part_it->p_lifespan), k);
        part_it->p_color[0] = lerp(0.0f, 1.0f, k);
        part_it->p_color[1] = 0.0f;
        part_it->p_color[2] = lerp(1.0f, 0.0f, k);
        part_it->p_color[3] = 1.0f;
    }
    
    //CIRCLE
    void circle(vector<particle>::iterator part_it, const double& delta_time)
    {
        float t = (float)part_it->seconds_alive();
        t = fmodf(abs(t), 2 * PI);
        part_it->p_position[0] = sin(t);
        part_it->p_position[1] = cos(t);
    }
}


////////////////////////
// SPAWNING FUNCTIONS //
////////////////////////
namespace spawner
{
    particle random_pos(const double& lifespan)
    {
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float p_x = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float p_y = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float p_z = base + fine / scale;
        
        return particle(p_x, p_y, p_z, lifespan);
    }
    
    particle random_vel(const double& lifespan)
    {
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float v_x = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_y = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_z = base + fine / scale;
        
        return particle(0.0f,0.0f,0.0f,v_x, v_y, v_z, lifespan);
    }
    
    particle random_acc(const double& lifespan)
    {
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float a_x = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_y = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_z = base + fine / scale;
        
        return particle(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,a_x, a_y, a_z, lifespan);
    }
    
    particle random_full(const double& lifespan)
    {
        // POS
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float p_x = base + fine / scale;

        base = rand() / scale;
        fine = rand() / scale;
        float p_y = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float p_z = base + fine / scale;
        // VEL
        base = rand() / scale;
        fine = rand() / scale;
        float v_x = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_y = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_z = base + fine / scale;
        // ACC
        base = rand() / scale;
        fine = rand() / scale;
        float a_x = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_y = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_z = base + fine / scale;
        
        return particle(p_x,p_y,p_z,v_x,v_y,v_z,a_x, a_y, a_z, lifespan);
    }
	
	
	// CONE SPAWNER
	particle cone_vel(const double& lifespan)
    {
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float v_x = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_y = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_z = base + fine / scale;
        
        return particle(0.0f,0.0f,0.0f,v_x, v_y, v_z, lifespan);
    }
    
    particle cone_acc(const double& lifespan)
    {
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float a_x = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_y = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_z = base + fine / scale;
        
        return particle(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,a_x, a_y, a_z, lifespan);
    }
    
    particle cone_full(const double& lifespan)
    {
        // POS
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float p_x = base + fine / scale;

        base = rand() / scale;
        fine = rand() / scale;
        float p_y = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float p_z = base + fine / scale;
        // VEL
        base = rand() / scale;
        fine = rand() / scale;
        float v_x = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_y = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_z = base + fine / scale;
        // ACC
        base = rand() / scale;
        fine = rand() / scale;
        float a_x = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_y = base + fine / scale;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_z = base + fine / scale;
        
        return particle(p_x,p_y,p_z,v_x,v_y,v_z,a_x, a_y, a_z, lifespan);
    }
}