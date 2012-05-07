#include "controller_functions.h"

#include <math.h>
#include <time.h>

namespace controller {
    // ZERO THINGS
    void zero_pos_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[0] = 0; }
    void zero_pos_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[1] = 0; }
    void zero_pos_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[2] = 0; }
        
    void zero_vel_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[0] = 0; }
    void zero_vel_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[1] = 0; }
    void zero_vel_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[2] = 0; }
        
    void zero_acc_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_acceleration[0] = 0; }
    void zero_acc_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_acceleration[1] = 0; }
    void zero_acc_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_acceleration[2] = 0; }
        
    void zero_all_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[0] = 0; 
          part_it->p_velocity[0] = 0; 
          part_it->p_acceleration[0] = 0; }
    void zero_all_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[1] = 0; 
          part_it->p_velocity[1] = 0; 
          part_it->p_acceleration[1] = 0; }
    void zero_all_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[2] = 0; 
          part_it->p_velocity[2] = 0; 
          part_it->p_acceleration[2] = 0; }
          
    // SIN
    void sin_pos_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[0] = sin(part_it->seconds_alive()); }
    void sin_pos_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[1] = sin(part_it->seconds_alive()); }
    void sin_pos_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[2] = sin(part_it->seconds_alive()); }
        
    void sin_vel_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[0] = sin(part_it->seconds_alive()); }
    void sin_vel_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[1] = sin(part_it->seconds_alive()); }
    void sin_vel_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[2] = sin(part_it->seconds_alive()); }
        
    void sin_acc_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        {
            part_it->p_acceleration[0] = sin(part_it->seconds_alive());
            part_it->p_velocity[0] = -cos(part_it->seconds_alive());
            part_it->p_position[0] = -sin(part_it->seconds_alive());
        }
    void sin_acc_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_acceleration[1] = sin(part_it->seconds_alive()); }
    void sin_acc_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_acceleration[2] = sin(part_it->seconds_alive()); }
    
    // COS
    void cos_pos_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[0] = cos(part_it->seconds_alive()); }
    void cos_pos_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[1] = cos(part_it->seconds_alive()); }
    void cos_pos_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[2] = cos(part_it->seconds_alive()); }
        
    void cos_vel_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[0] = cos(part_it->seconds_alive()); }
    void cos_vel_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[1] = cos(part_it->seconds_alive()); }
    void cos_vel_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[2] = cos(part_it->seconds_alive()); }

    void cos_acc_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_acceleration[0] = cos(part_it->seconds_alive()); }
    void cos_acc_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_acceleration[1] = cos(part_it->seconds_alive()); }
    void cos_acc_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_acceleration[2] = cos(part_it->seconds_alive()); }
        
    // EXP
    void exp_pos_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[0] = exp(part_it->seconds_alive()); }
    void exp_pos_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[1] = exp(part_it->seconds_alive()); }
    void exp_pos_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_position[2] = exp(part_it->seconds_alive()); }
    
    void exp_vel_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[0] = exp(part_it->seconds_alive()); }
    void exp_vel_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[1] = exp(part_it->seconds_alive()); }
    void exp_vel_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_velocity[2] = exp(part_it->seconds_alive()); }
    
    void exp_acc_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_acceleration[0] = exp(part_it->seconds_alive()); }
    void exp_acc_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_acceleration[1] = exp(part_it->seconds_alive()); }
    void exp_acc_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
        { part_it->p_acceleration[2] = exp(part_it->seconds_alive()); }
        
    // BUTTERFLY CURVE
    void butterfly_curve_xy(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
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
    void butterfly_curve_xz(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
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
    void butterfly_curve_yz(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
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
    
    // Log Spiral
    void log_spiral_xy(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float a = 0.2, b = 0.5, t = (float)part_it->seconds_alive();
        part_it->p_position[0] = a * cos(t) * exp(b * t);
        part_it->p_position[1] = a * sin(t) * exp(b * t);
    }
    
    void log_spiral_xz(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float a = 0.2, b = 0.5, t = (float)part_it->seconds_alive();
        part_it->p_position[0] = a * cos(t) * exp(b * t);
        part_it->p_position[2] = a * sin(t) * exp(b * t);
    }
    
    void log_spiral_yz(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float a = 0.2, b = 0.5, t = (float)part_it->seconds_alive();
        part_it->p_position[1] = a * cos(t) * exp(b * t);
        part_it->p_position[2] = a * sin(t) * exp(b * t);
    }
	
	// SINE_WAVE
	void sine_wave_y_to_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
	{
		part_it->p_position[0] = sin(part_it->p_position[1]);
		part_it->p_velocity[0] = part_it->p_velocity[2];
		part_it->p_acceleration[0] = part_it->p_acceleration[1] = part_it->p_acceleration[2] = 0.0f;
		
		part_it->p_velocity[1] = 1.0f;
	}
    // COS_WAVE
	void cos_wave_y_to_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
	{
		part_it->p_position[0] = cos(part_it->p_position[1]);
		part_it->p_velocity[0] = part_it->p_velocity[2];
		part_it->p_acceleration[0] = part_it->p_acceleration[1] = part_it->p_acceleration[2] = 0.0f;
		
		part_it->p_velocity[1] = 1.0f;
	}
    // TAN_GRAPH
	void tan_graph_y_to_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
	{
		part_it->p_position[0] = tan(part_it->p_position[1]);
		part_it->p_velocity[0] = part_it->p_velocity[2];
		part_it->p_acceleration[0] = part_it->p_acceleration[1] = part_it->p_acceleration[2] = 0.0f;
		
		part_it->p_velocity[1] = 1.0f;
	}
    // SINH_GRAPH
	void sinh_graph_y_to_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
	{
		part_it->p_position[0] = sinh(part_it->p_position[1]);
		part_it->p_velocity[0] = part_it->p_velocity[2];
		part_it->p_acceleration[0] = part_it->p_acceleration[1] = part_it->p_acceleration[2] = 0.0f;
		
        //part_it->p_acceleration[0] = sinh(part_it->p_position[1]);
		part_it->p_velocity[1] = 1.0f;
	}
    // COSH_GRAPH
	void cosh_graph_y_to_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
	{
		part_it->p_position[0] = cosh(part_it->p_position[1]);
		part_it->p_velocity[0] = part_it->p_velocity[2];
		part_it->p_acceleration[0] = part_it->p_acceleration[1] = part_it->p_acceleration[2] = 0.0f;
		
        //part_it->p_acceleration[0] = cosh(part_it->p_position[1]);
		part_it->p_velocity[1] = 1.0f;
	}
    // TANH_GRAPH
	void tanh_graph_y_to_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
	{
		part_it->p_position[0] = tanh(part_it->p_position[1]);
		part_it->p_velocity[0] = part_it->p_velocity[2];
		part_it->p_acceleration[0] = part_it->p_acceleration[1] = part_it->p_acceleration[2] = 0.0f;
		
        //part_it->p_acceleration[0] = tanh(part_it->p_position[1]);
		part_it->p_velocity[1] = 1.0f;
	}
        
    // COLORS
    void white(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        part_it->p_color[0] = 1.0f;
        part_it->p_color[1] = 1.0f;
        part_it->p_color[2] = 1.0f;
    }
    void black(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        part_it->p_color[0] = 0.0f;
        part_it->p_color[1] = 0.0f;
        part_it->p_color[2] = 0.0f;
    }
    void red(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        part_it->p_color[0] = 1.0f;
        part_it->p_color[1] = 0.0f;
        part_it->p_color[2] = 0.0f;
    }
    void yellow(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        part_it->p_color[0] = 1.0f;
        part_it->p_color[1] = 1.0f;
        part_it->p_color[2] = 0.0f;
    }
    void green(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        part_it->p_color[0] = 0.0f;
        part_it->p_color[1] = 1.0f;
        part_it->p_color[2] = 0.0f;
    }
    void cyan(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        part_it->p_color[0] = 0.0f;
        part_it->p_color[1] = 1.0f;
        part_it->p_color[2] = 1.0f;
    }
    void blue(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        part_it->p_color[0] = 0.0f;
        part_it->p_color[1] = 0.0f;
        part_it->p_color[2] = 1.0f;
    }
    void magenta(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        part_it->p_color[0] = 1.0f;
        part_it->p_color[1] = 0.0f;
        part_it->p_color[2] = 1.0f;
    }
    
    // COLORS_TRANSITIONS
    void white_to_black(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        part_it->p_color[0] = lerp(1.0f, 0.0f, k);
        part_it->p_color[1] = lerp(1.0f, 0.0f, k);
        part_it->p_color[2] = lerp(1.0f, 0.0f, k);
    }
    void black_to_white(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        part_it->p_color[0] = lerp(0.0f, 1.0f, k);
        part_it->p_color[1] = lerp(0.0f, 1.0f, k);
        part_it->p_color[2] = lerp(0.0f, 1.0f, k);
    }
    void red_to_cyan(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        part_it->p_color[0] = lerp(1.0f, 0.0f, k);
        part_it->p_color[1] = lerp(0.0f, 1.0f, k);
        part_it->p_color[2] = lerp(0.0f, 1.0f, k);
    }
    void yellow_to_blue(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        part_it->p_color[0] = lerp(1.0f, 0.0f, k);
        part_it->p_color[1] = lerp(1.0f, 0.0f, k);
        part_it->p_color[2] = lerp(0.0f, 1.0f, k);
    }
    void green_to_magenta(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        part_it->p_color[0] = lerp(0.0f, 1.0f, k);
        part_it->p_color[1] = lerp(1.0f, 0.0f, k);
        part_it->p_color[2] = lerp(0.0f, 1.0f, k);
    }
    void cyan_to_red(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        part_it->p_color[0] = lerp(0.0f, 1.0f, k);
        part_it->p_color[1] = lerp(1.0f, 0.0f, k);
        part_it->p_color[2] = lerp(1.0f, 0.0f, k);
    }
    void blue_to_yellow(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        part_it->p_color[0] = lerp(0.0f, 1.0f, k);
        part_it->p_color[1] = lerp(0.0f, 1.0f, k);
        part_it->p_color[2] = lerp(1.0f, 0.0f, k);
    }
    void magenta_to_green(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        part_it->p_color[0] = lerp(1.0f, 0.0f, k);
        part_it->p_color[1] = lerp(0.0f, 1.0f, k);
        part_it->p_color[2] = lerp(1.0f, 0.0f, k);
    }
    
    // ALPHA_CHANGES
    void fade(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        part_it->p_color[3] = lerp(1.0, 0.0, k);
    }
    void un_fade(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        part_it->p_color[3] = lerp(0.0, 1.0, k);
    }
    void fade_in_and_out(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        k = (k > 0.5f) ? k : 1.0f - k;
        part_it->p_color[3] = lerp(0.0, 1.0, k);
    }
    void fade_in_and_out_edge(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float on = 0.05f;
        float off = 1.0f - on;
        float k = 1.0f - ((float)(part_it->p_alive_time) / (float)(part_it->p_lifespan));
        float k2 = 0.0f;
        // FADE IN
        if(k > off)
            k2 = ((k - off) / on);
        if(k < 0.2f)
            k2 = 1.0f - (k / on);
        part_it->p_color[3] = lerp(0.0, 1.0, k2);
    }
    
    //CIRCLE
    void circle_xy(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float t = (float)part_it->seconds_alive();
        t = fmodf(abs(t), 2 * PI);
        part_it->p_position[0] = sin(t);
        part_it->p_position[1] = cos(t);
    }
    
    // STEP
    void step(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float ax, ay, az, mag;
        ax = -part_it->p_position[0] + source_e->center[0];
        ay = -part_it->p_position[1] + source_e->center[1];
        az = -part_it->p_position[2] + source_e->center[2];
        mag = ax*ax + ay*ay * az*az;
        if(mag > 0.1f)
        {
            float scale_x = mag;
            float scale_y = mag;
            float scale_z = mag;
            part_it->p_acceleration[0] = scale_x * (ax / mag);
            part_it->p_acceleration[1] = scale_y * (ay / mag);
            part_it->p_acceleration[2] = scale_z * (az / mag);
        }
        else
        {
            if(part_it->p_acceleration[0] == part_it->p_acceleration[1] && part_it->p_acceleration[0] == part_it->p_acceleration[0])
                part_it->p_acceleration[0] = part_it->p_acceleration[1] = part_it->p_acceleration[2] = 0.1f;;
        }
    }
    
    // GRAVITY
    void gravity_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float t = delta_time / 1000.0f;
        float gv = GRAVITY * t;
        part_it->p_velocity[1] = (part_it->p_velocity[1] + 0.5 * gv) * t;
    }
    
    void gravity_b(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        float ax,ay,az,mag,gf,gfm;
        ax = -part_it->p_position[0] + source_e->center[0];
        ay = -part_it->p_position[1] + source_e->center[1];
        az = -part_it->p_position[2] + source_e->center[2];
        mag = ax*ax + ay*ay * az*az;
        gf = (GRAV_CONST * source_e->mass) / (mag * mag);
        gfm = (gf > GRAV_MAX) ? GRAV_MAX : gf;
        ax = ax / mag;
        ay = ay / mag;
        az = az / mag;
        
        part_it->p_acceleration[0] = ax * gf;
        part_it->p_acceleration[1] = ay * gf;
        part_it->p_acceleration[2] = az * gf;
    }
    
    void rotate(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time)
    {
        double rotation_time = 60;
        float theta = ((delta_time / 1000.0) / rotation_time) * 2.0f * PI;
        
        part_it->p_position[0] = part_it->p_position[0] * cos(theta) - part_it->p_position[2] * sin(theta);
        part_it->p_position[2] = part_it->p_position[0] * sin(theta) + part_it->p_position[2] * cos(theta);
    }
}


////////////////////////
// SPAWNING FUNCTIONS //
////////////////////////
namespace spawner
{
    particle center(const double& lifespan, const emitter* source_e)
    {
        particle p(0.0f,0.0f,0.0f, lifespan);
        p.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return p;
    }
    particle x_line(const double& lifespan, const emitter* source_e)
    {
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float p = base + fine / scale;
        p = (rand() % 2) ? -p : p;
        particle pa(p,0.0f,0.0f, lifespan);
        pa.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return pa;
    }
    particle y_line(const double& lifespan, const emitter* source_e)
    {
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float p = base + fine / scale;
        p = (rand() % 2) ? -p : p;
        particle pa(0.0f,p,0.0f, lifespan);
        pa.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return pa;
    }
    particle z_line(const double& lifespan, const emitter* source_e)
    {
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float p = base + fine / scale;
        p = (rand() % 2) ? -p : p;
        particle pa(0.0f,0.0f,p, lifespan);
        pa.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return pa;
    }
    
    particle random_pos(const double& lifespan, const emitter* source_e)
    {
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float p_x = (base + fine / scale);
        p_x = (rand() % 2) ? p_x : -p_x;
        
        base = rand() / scale;
        fine = rand() / scale;
        float p_y = (base + fine / scale);
        p_y = (rand() % 2) ? p_y : -p_y;
        
        base = rand() / scale;
        fine = rand() / scale;
        float p_z = (base + fine / scale);
        p_z = (rand() % 2) ? p_z : -p_z;
        
        particle p(p_x, p_y, p_z, lifespan);
        p.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return p;
    }
    
    particle random_vel(const double& lifespan, const emitter* source_e)
    {
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float v_x = (base + fine / scale);
        v_x = (rand() % 2) ? v_x : -v_x;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_y = (base + fine / scale);
        v_y = (rand() % 2) ? v_y : -v_y;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_z = (base + fine / scale);
        v_z = (rand() % 2) ? v_z : -v_z;
        
        particle p(0.0f,0.0f,0.0f,v_x, v_y, v_z, lifespan);
        p.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return p;
    }
    
    particle random_acc(const double& lifespan, const emitter* source_e)
    {
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float a_x = (base + fine / scale);
        a_x = (rand() % 2) ? a_x : -a_x;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_y = (base + fine / scale);
        a_y = (rand() % 2) ? a_y : -a_y;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_z = (base + fine / scale);
        a_z = (rand() % 2) ? a_z : -a_z;
        
        particle p(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,a_x, a_y, a_z, lifespan);
        p.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return p;
    }
    
    particle random_full(const double& lifespan, const emitter* source_e)
    {
        // POS
        float scale = RAND_MAX + 1.0f;
        float base = rand() / scale;
        float fine = rand() / scale;
        float p_x = (base + fine / scale);
        p_x = (rand() % 2) ? p_x : -p_x;
        
        base = rand() / scale;
        fine = rand() / scale;
        float p_y = (base + fine / scale);
        p_y = (rand() % 2) ? p_y : -p_y;
        
        base = rand() / scale;
        fine = rand() / scale;
        float p_z = (base + fine / scale);
        p_z = (rand() % 2) ? p_z : -p_z;
        // VEL
        base = rand() / scale;
        fine = rand() / scale;
        float v_x = (base + fine / scale);
        v_x = (rand() % 2) ? v_x : -v_x;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_y = (base + fine / scale);
        v_y = (rand() % 2) ? v_y : -v_y;
        
        base = rand() / scale;
        fine = rand() / scale;
        float v_z = (base + fine / scale);
        v_z = (rand() % 2) ? v_z : -v_z;
        // ACC
        base = rand() / scale;
        fine = rand() / scale;
        float a_x = (base + fine / scale);
        a_x = (rand() % 2) ? a_x : -a_x;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_y = (base + fine / scale);
        a_y = (rand() % 2) ? a_y : -a_y;
        
        base = rand() / scale;
        fine = rand() / scale;
        float a_z = (base + fine / scale);
        a_z = (rand() % 2) ? a_z : -a_z;
        
        particle p(p_x,p_y,p_z,v_x,v_y,v_z,a_x, a_y, a_z, lifespan);
        p.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return p;
    }
	
	particle rand_sphere(const double& lifespan, const emitter* source_e)
    {
        float radius, phi, theta, z, px, py, pz;
        radius = 5.0f;
        phi = (rand() % 360)* (PI / 180.0f);
        z = (rand() % 2) ? -((float)rand() / (float)RAND_MAX) * radius :
                            ((float)rand() / (float)RAND_MAX) * radius;
        theta = asin( z / radius);
        
        px = radius * cos(theta) * cos(phi);
        py = radius * cos(theta) * sin(phi);
        pz = z;
        
        particle p(px,py,pz,lifespan);
        p.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return p;
    }
    
	// CONE SPAWNER
	particle cone_vel(const double& lifespan, const emitter* source_e)
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
        
        particle p(0.0f,0.0f,0.0f,v_x, v_y, v_z, lifespan);
        p.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return p;
    }
    
    particle cone_acc(const double& lifespan, const emitter* source_e)
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
        
        particle p(0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,a_x, a_y, a_z, lifespan);
        p.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return p;
    }
    
    particle cone_full(const double& lifespan, const emitter* source_e)
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
        
        particle p(p_x,p_y,p_z,v_x,v_y,v_z,a_x, a_y, a_z, lifespan);
        p.set_color(source_e->base_color[0], source_e->base_color[1], source_e->base_color[2], source_e->base_color[3]);
        return p;
    }
    
    void random_color(particle& p)
    {
        p.set_color((rand() % 256) / 256.0f, (rand() % 256) / 256.0f, (rand() % 256) / 256.0f, 1.0f);
    }
}