#include <iostream>
#include "Eigen/Dense"
#include <vector>

// Bad practice to use namespace std (https://stackoverflow.com/questions/1452721/why-is-using-namespace-std-considered-bad-practice)
// using namespace std;
// using namespace Eigen;
using std::cout;
using std::endl;
using std::vector;
using Eigen::VectorXd;
using Eigen::MatrixXd;

// Kalman Filter variables
VectorXd x;         // object state
MatrixXd P;         // object covariance matrix
VectorXd u;         // external motion
MatrixXd F;         // state transition matrix
MatrixXd H;         // measurement matrix
MatrixXd R;         // measurement covariance matrix
MatrixXd I;         // identity matrix
MatrixXd Q;         // process covariance matrix

vector<VectorXd> measurements;
void filter(VectorXd &x, MatrixXd &P);
void tutorial();

int main()
{
    x = VectorXd(2);
    x << 0,0;

    P = MatrixXd(2,2);
    P << 1000, 0, 0, 1000;

    u = VectorXd(2);
    u << 0, 0;

    F = MatrixXd(2,2);
    F << 1, 1, 0, 1;

    H = MatrixXd(1,2);
    H << 1, 0;

    R = MatrixXd(1,1);
    R << 1;
    
    I = MatrixXd::Identity(2,2);

    Q = MatrixXd(2,2);
    Q << 0, 0, 0, 0;

    // create a list of measurements
    VectorXd single_meas(1);
    single_meas << 1;
    measurements.push_back(single_meas);
    single_meas << 2;
    measurements.push_back(single_meas);
    single_meas << 3;
    measurements.push_back(single_meas);

    // Kalman filter algorithm
    filter(x, P);

    return 0;
}

void filter(VectorXd &x, MatrixXd &P)
{
    for(unsigned int n = 0; n < measurements.size(); ++n)
    {
        VectorXd z = measurements[n];

        // Measurement Update step
        VectorXd y = z - H*x;
        MatrixXd S = H*P*H.transpose() + R;
        MatrixXd K = P*H.transpose()*S.inverse();

        // New state
        x = x + K*y;
        P = (I - K*H)*P;

        // Prediction step
        x = F*x;
        P = F*P*F.transpose() + Q;

        cout << "x=" << endl << x << endl;
        cout << "P=" << endl << P << endl;
    }
}

// Tutorial on Eigen template
void tutorial()
{
    VectorXd my_vector(2);      // this creates a vertical vector of 2 elements
    my_vector << 10, 20;
    cout << my_vector << endl;

    MatrixXd my_matrix(2,3);
    my_matrix << 1,2,3,
                4,5,6;
    cout << my_matrix << endl;
    my_matrix(1,0) = 9;
    my_matrix(0,2) = 6;
    cout << my_matrix << endl;

    // matrix transpose
    MatrixXd my_matrix_t = my_matrix.transpose();
    cout << "Transpose: " << my_matrix_t << endl;

    // multiply matrix and vector
    MatrixXd multiply_mat = my_vector.transpose() * my_matrix;
    cout << "Multiply: " << multiply_mat << endl;

    // matrix inverse
    MatrixXd sq_matrix(3,3);
    sq_matrix << 1,2,3,4,5,6,7,8,9;
    MatrixXd sq_matrix_inv = sq_matrix.inverse();
    cout << "Square matrix: " << sq_matrix << endl;
    cout << "Inverse: " << sq_matrix_inv << endl;
}