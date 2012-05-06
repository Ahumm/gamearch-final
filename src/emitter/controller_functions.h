#ifndef _CONTROLLER_FUNCTIONS_H_
#define _CONTROLLER_FUNCTIONS_H_

#include "emitter.h"
#include "particle.h"

#include <vector>

using namespace std;

namespace controller
{
    //typedef void (*fptr)(vector<particle>::iterator, const double&);
    // BASE MODIFICATIONS WITH SIN
    void sin_pos_x(vector<particle>::iterator part_it, const double& delta_time);
    void sin_pos_y(vector<particle>::iterator part_it, const double& delta_time);
    void sin_pos_z(vector<particle>::iterator part_it, const double& delta_time);
    
    void sin_vel_x(vector<particle>::iterator part_it, const double& delta_time);
    void sin_vel_y(vector<particle>::iterator part_it, const double& delta_time);
    void sin_vel_z(vector<particle>::iterator part_it, const double& delta_time);

    void sin_acc_x(vector<particle>::iterator part_it, const double& delta_time);
    void sin_acc_y(vector<particle>::iterator part_it, const double& delta_time);
    void sin_acc_z(vector<particle>::iterator part_it, const double& delta_time);
    
    // BASE MODIFICATIONS WITH COS
    void cos_pos_x(vector<particle>::iterator part_it, const double& delta_time);
    void cos_pos_y(vector<particle>::iterator part_it, const double& delta_time);
    void cos_pos_z(vector<particle>::iterator part_it, const double& delta_time);
    
    void cos_vel_x(vector<particle>::iterator part_it, const double& delta_time);
    void cos_vel_y(vector<particle>::iterator part_it, const double& delta_time);
    void cos_vel_z(vector<particle>::iterator part_it, const double& delta_time);

    void cos_acc_x(vector<particle>::iterator part_it, const double& delta_time);
    void cos_acc_y(vector<particle>::iterator part_it, const double& delta_time);
    void cos_acc_z(vector<particle>::iterator part_it, const double& delta_time);
    
    // BASE MODIFICATIONS WITH EXP
    void exp_pos_x(vector<particle>::iterator part_it, const double& delta_time);
    void exp_pos_y(vector<particle>::iterator part_it, const double& delta_time);
    void exp_pos_z(vector<particle>::iterator part_it, const double& delta_time);
    
    void exp_vel_x(vector<particle>::iterator part_it, const double& delta_time);
    void exp_vel_y(vector<particle>::iterator part_it, const double& delta_time);
    void exp_vel_z(vector<particle>::iterator part_it, const double& delta_time);
    
    void exp_acc_x(vector<particle>::iterator part_it, const double& delta_time);
    void exp_acc_y(vector<particle>::iterator part_it, const double& delta_time);
    void exp_acc_z(vector<particle>::iterator part_it, const double& delta_time);
    
    // BUTTERFLY CURVE
    void butterfly_curve_xy(vector<particle>::iterator part_it, const double& delta_time);
    void butterfly_curve_xz(vector<particle>::iterator part_it, const double& delta_time);
    void butterfly_curve_yz(vector<particle>::iterator part_it, const double& delta_time);
    
    // Log Spiral
    void log_spiral_xy(vector<particle>::iterator part_it, const double& delta_time);
    void log_spiral_xz(vector<particle>::iterator part_it, const double& delta_time);
    void log_spiral_yz(vector<particle>::iterator part_it, const double& delta_time);
	
	// SINE_WAVE
	void sine_wave_y_to_x(vector<particle>::iterator part_it, const double& delta_time);
    // TAN_GRAPH
	void tan_graph_y_to_x(vector<particle>::iterator part_it, const double& delta_time);
    // COSH_GRAPH
	void cosh_graph_y_to_x(vector<particle>::iterator part_it, const double& delta_time);

    // COLOR_TRANSITIONS
    void red_to_yellow(vector<particle>::iterator part_it, const double& delta_time);
    void yellow_to_blue(vector<particle>::iterator part_it, const double& delta_time);
    void blue_to_red(vector<particle>::iterator part_it, const double& delta_time);
}

namespace spawner
{
	// Random
    particle random_pos(const double& lifespan);
    particle random_vel(const double& lifespan);
    particle random_acc(const double& lifespan);
    particle random_full(const double& lifespan);
	
	// CONE
	particle cone_vel(const double& lifespan);
    particle cone_acc(const double& lifespan);
    particle cone_full(const double& lifespan);
    
    typedef particle (*sptr)(const double&);
    const uint32_t num_spawn_controllers = 7;
    const sptr spawn_controllers[] = {random_pos, random_vel, random_acc, random_full, cone_vel, cone_acc, cone_full};
}

#endif