#include "kalman_filter.h"

using Eigen::MatrixXd;
using Eigen::VectorXd;

/* 
 * Please note that the Eigen library does not initialize 
 *   VectorXd or MatrixXd objects with zeros upon creation.
 */

KalmanFilter::KalmanFilter() {}

KalmanFilter::~KalmanFilter() {}

void KalmanFilter::Init(VectorXd &x_in, MatrixXd &P_in, MatrixXd &F_in,
                        MatrixXd &H_in, MatrixXd &R_in, MatrixXd &Q_in) {
  x_ = x_in;
  P_ = P_in;
  F_ = F_in;
  // H_ = H_in;
  // R_ = R_in;
  Q_ = Q_in;
}

void KalmanFilter::Predict() {
  /**
   * TODO: predict the state
   */
  x_ = F_ * x_;
  P_ = F_*P_*F_.transpose() + Q_;
}

void KalmanFilter::Update(const VectorXd &z) {
  /**
   * TODO: update the state by using Kalman Filter equations
   */
  VectorXd y = z - H_laser_*x_;
  MatrixXd S = H_laser_*P_*H_laser_.transpose() + R_laser_;
  MatrixXd K = P_*H_laser_.transpose()*S.inverse();
  
  // New estimates
  x_ = x_ + K*y;
  MatrixXd I = MatrixXd::Identity(x_.size(), x_.size());
  P_ = (I - K*H_laser_) * P_;
}

void KalmanFilter::UpdateEKF(const VectorXd &z) {
  /**
   * TODO: update the state by using Extended Kalman Filter equations
   */
  float px = x_(0);
  float py = x_(1);
  float vx = x_(2);
  float vy = x_(3);

  VectorXd h(3);
  h << sqrt(px*px + py*py),
      atan2(py,px),        // atan2() returns radian in range [-pi, pi]
      (px*vx+py*vy)/sqrt(px*px+py*py);
  
  VectorXd y = z - h;
  // Make sure theta is normalized between (-pi, pi)
  y(1) = normalize_theta_radar(y);

  MatrixXd S = H_radar_*P_*H_radar_.transpose() + R_radar_;
  MatrixXd K = P_*H_radar_.transpose()*S.inverse();

  // New estimates
  x_ = x_ + K*y;
  MatrixXd I = MatrixXd::Identity(x_.size(), x_.size());
  P_ = (I - K*H_radar_) * P_;
}

float normalize_theta_radar(const Eigen::VectorXd y)
{
  float theta = y(1);
  while(1) {
    if (theta > M_PI) {
      theta -= 2*M_PI;
    } 
    else if(theta < -M_PI) {
      theta += 2*M_PI;
    }
    else {
      break;
    }
  }
  return theta;
}