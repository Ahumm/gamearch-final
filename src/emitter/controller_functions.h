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
}

#endif