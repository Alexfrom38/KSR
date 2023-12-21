#include"SquareMatrix.h"
#include<cmath>
#include"OptimalRK4.h"

#include<iomanip>
int main()
{
	TSquareMatrix<double> A(-500.005, 499.995, 499.995, -500.005);
	TSquareMatrix<double> E(1, 0, 0, 1);
	TSquareMatrix<double> B;
	std::vector<double> Vn = { 2, 4 };
	TSquareMatrix<double> F;
	TSquareMatrix<double> M;
	TSquareMatrix<double> Q;
	
	

	std::vector <double> K_2;
	std::vector <double> K_1;
	std::vector <double> Vn_lambda_F_Vn;
	std::vector <double> lambda_F_Vn;
	std::vector <double> Vn_hbK_2;
	std::vector <double> hbK_2;
	std::vector < std::vector <double>> Vec_K;

	double lambda;
	double sigma;
	double temp;
	double h = 0.1;
	double d = 0.25 + (sqrt(3) / 6);
	double b = 0.25 - (sqrt(3) / 6);


	TOptimalRK RK(0.0, 0.02, 0.01, 7.0, 13.0, 1000000, 0.11);
	RK.Get_Points(7.0, 13.0, 0.01);
	
	//
	//temp = 1;
	//h = 0.1;
	//lambda = h * d;
	//sigma = h * h * b * d;
	//


	//B = E*4-A*h;
	//B = B.GetReverseMatrix();
	///////
	//F = B * A * 4;
	//M = (A * sigma) * F;
	//M = E * 4 - (A * sigma) * F - (A * h);
	//M = M.GetReverseMatrix();
	//Q = M * 4 * A;

	//Vn_lambda_F_Vn = Vn;
	//lambda_F_Vn = (F * lambda) * Vn;

	//Vn_lambda_F_Vn[0] += lambda_F_Vn[0];
	//Vn_lambda_F_Vn[1] += lambda_F_Vn[1];

	//K_2 = Q * Vn_lambda_F_Vn;

	//Vn_hbK_2 = Vn;

	//hbK_2 = K_2;
	//hbK_2[0] = hbK_2[0] * b * h;
	//hbK_2[1] = hbK_2[1] * b * h;

	//Vn_hbK_2[0] += hbK_2[0];
	//Vn_hbK_2[1] += hbK_2[1];
	//K_1 = F * Vn_hbK_2;

	//std::cout << std::setprecision(16) << "K_1 = " << K_1[0] << ' ' << K_1[1] << std::endl;
	//std::cout << std::setprecision(16) << "K_2 = " << K_2[0] << ' ' << K_2[1] << std::endl;



	

	return 0;
}