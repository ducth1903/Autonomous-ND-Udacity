#include "tools.h"
#include <iostream>
#include <math.h>

using Eigen::VectorXd;
using Eigen::MatrixXd;
using std::vector;

Tools::Tools() {}

Tools::~Tools() {}

VectorXd Tools::CalculateRMSE(const vector<VectorXd> &estimations,
                              const vector<VectorXd> &ground_truth) {
   /**
   * TODO: Calculate the RMSE here.
   */
   VectorXd rmse(4);
   rmse << 0,0,0,0;
   // Sanity check if estimations length > 0 and len(estimations) == len(ground_truth)
   if (estimations.size()==0 || estimations.size()!= ground_truth.size()) {
      std::cout << "Error in estimations" << std::endl;
      return rmse;
   }

   // Accumulate square residuals
   for (unsigned int i=0; i<estimations.size(); i++) {
      rmse += (estimations[i]-ground_truth[i]).array().square().matrix();
   }

   // Calculate mean
   rmse = rmse / estimations.size();

   // Calculate squared root to obtain RMSE final
   rmse = rmse.array().sqrt();

   return rmse;
}

// Calculating Jacobian matrix for RADAR measurement update
MatrixXd Tools::CalculateJacobian(const VectorXd& x_state) {
   /**
   * TODO:
   * Calculate a Jacobian here.
   */
   MatrixXd Hj(3,4);
   float px = x_state(0);
   float py = x_state(1);
   float vx = x_state(2);
   float vy = x_state(3);

   float denom = px*px + py*py;
   // check if divide by zero, return error
   if (denom==0) {
      std::cout << "Error in calcualting Jacobian: divide by zero" << std::endl;
      return Hj; 
   }

   float sqrt_denom = sqrt(denom);
   float denom_3over2 = pow(denom, 3/2);
   Hj << px/sqrt_denom, py/sqrt_denom, 0, 0,
         -py/denom, px/denom, 0, 0,
         py*(vx*py-vy*px)/denom_3over2, px*(vy*px-vx*py)/denom_3over2, px/sqrt_denom, py/sqrt_denom;
   
   return Hj;
}
