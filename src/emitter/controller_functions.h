#ifndef _CONTROLLER_FUNCTIONS_H_
#define _CONTROLLER_FUNCTIONS_H_

#include "emitter.h"
#include "particle.h"

#include <vector>

using namespace std;

class emitter;

namespace controller
{
    //typedef void (*fptr)(vector<particle>::iterator, const emitter*, const double&);
    // ZERO THINGS
    void zero_pos_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void zero_pos_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void zero_pos_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    void zero_vel_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void zero_vel_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void zero_vel_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    void zero_acc_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void zero_acc_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void zero_acc_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    void zero_all_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void zero_all_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void zero_all_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    // BASE MODIFICATIONS WITH SIN
    void sin_pos_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void sin_pos_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void sin_pos_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    void sin_vel_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void sin_vel_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void sin_vel_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);

    void sin_acc_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void sin_acc_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void sin_acc_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    // BASE MODIFICATIONS WITH COS
    void cos_pos_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void cos_pos_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void cos_pos_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    void cos_vel_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void cos_vel_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void cos_vel_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);

    void cos_acc_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void cos_acc_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void cos_acc_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    // BASE MODIFICATIONS WITH EXP
    void exp_pos_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void exp_pos_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void exp_pos_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    void exp_vel_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void exp_vel_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void exp_vel_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    void exp_acc_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void exp_acc_y(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void exp_acc_z(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    // BUTTERFLY CURVE
    void butterfly_curve_xy(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void butterfly_curve_xz(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void butterfly_curve_yz(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    // Log Spiral
    void log_spiral_xy(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void log_spiral_xz(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void log_spiral_yz(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
	
	// SINE_WAVE
	void sine_wave_y_to_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    // TAN_GRAPH
	void tan_graph_y_to_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    // COSH_GRAPH
	void cosh_graph_y_to_x(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);

    // COLORS
    void white(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void black(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void red(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void yellow(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void green(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void cyan(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void blue(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void magenta(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    // COLOR_TRANSITIONS
    void white_to_black(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void black_to_white(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void red_to_cyan(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void yellow_to_blue(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void green_to_magenta(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void cyan_to_red(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void blue_to_yellow(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void magenta_to_green(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    // ALPHA_CHANGES
    void fade(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    void un_fade(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
    
    // CIRCLE
    void circle_xy(vector<particle>::iterator part_it, const emitter* source_e, const double& delta_time);
}

namespace spawner
{
    // LINES
    particle center(const double& lifespan, const emitter* source_e);
    particle x_line(const double& lifespan, const emitter* source_e);
    particle y_line(const double& lifespan, const emitter* source_e);
    particle z_line(const double& lifespan, const emitter* source_e);

	// RANDOM
    particle random_pos(const double& lifespan, const emitter* source_e);
    particle random_vel(const double& lifespan, const emitter* source_e);
    particle random_acc(const double& lifespan, const emitter* source_e);
    particle random_full(const double& lifespan, const emitter* source_e);
	
	// CONE
	particle cone_vel(const double& lifespan, const emitter* source_e);
    particle cone_acc(const double& lifespan, const emitter* source_e);
    particle cone_full(const double& lifespan, const emitter* source_e);
    
    typedef particle (*sptr)(const double&, const emitter*);
    const uint32_t num_spawn_controllers = 7;
    const sptr spawn_controllers[] = {random_pos, random_vel, random_acc, random_full, cone_vel, cone_acc, cone_full};
}

#endif