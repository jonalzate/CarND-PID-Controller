#include "PID.h"
#include <cmath>
#include <iostream>

using namespace std;

/*
* PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_, double Ki_, double Kd_) {

  // Initialize gains (Proportional, Integral, Differential)
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;

  // Initialize errors to zero
  p_error = 0;
  i_error = 0;
  d_error = 0;

  // Twiddle parameters
  should_twiddle = false;
  dp = {0.1 * Kp, 0.1 * Kd, 0.1 * Ki};
  step = 1;
  param_index = 2;  // this will go back to 0 after the first twiddle loop

  // number of settle and evaluation steps
  n_settle_steps = 100;
  n_eval_steps = 2000;

  // total and best error
  total_error = 0;
  best_error = std::numeric_limits<double>::max();

  // flags to add or subtract from dp
  should_add = false;
  should_subtract = false;

}

void PID::UpdateError(double cte) {

  if (step == 1) {
        // to get correct initial d_error
        p_error = cte;
  }

  // Calculate P, I, D errors
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;

  // Update total error only if we're past number of settle steps
  if (step % (n_settle_steps + n_eval_steps) > n_settle_steps){
      total_error += pow(cte,2);
  }

  // Twiddle loop
  if (should_twiddle && step % (n_settle_steps + n_eval_steps) == 0){

       if (total_error < best_error) {
           // Update best error
           best_error = total_error;

           if (step !=  n_settle_steps + n_eval_steps) {
               // don't do this if it's the first time through
               dp[param_index] *= 1.1;
           }

           // next parameter
           param_index = (param_index + 1) % 3;
           should_add = should_subtract = false;
       }

       if (!should_add && !should_subtract) {

           // Add dp[i] to params[i]
           UpdatedParameterAtIndex(param_index, dp[param_index]);
           should_add = true;
       }
       else if (should_add && !should_subtract) {
           // Subtract dp[i] from params[i]
           UpdatedParameterAtIndex(param_index, -2 * dp[param_index]);
           should_subtract = true;
       }
       else {
           // set it back, reduce dp[i], move on to next parameter
           UpdatedParameterAtIndex(param_index, dp[param_index]);
           dp[param_index] *= 0.9;
           // next parameter
           param_index = (param_index + 1) % 3;
           should_add = should_subtract = false;
       }

       // Update total error
       total_error = 0;
   }

   // Update step
   step++;

}

double PID::TotalError() {

  // return error
  return -Kp * p_error - Kd * d_error - Ki * i_error;
}


void PID::UpdatedParameterAtIndex(int index, double amount) {
		// Update P
    if (index == 0) {
        Kp += amount;
    }
    // Update D
    else if (index == 1) {
        Kd += amount;
    }
    // Update I
    else if (index == 2) {
        Ki += amount;
    }
    else {
        std::cout << "UpdatedParameterAtIndex: index out of bounds";
    }
}

