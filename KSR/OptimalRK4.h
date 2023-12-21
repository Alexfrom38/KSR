#pragma once
#include"SquareMatrix.h"
#include <fstream>
#include <iomanip>
class TOptimalRK
{
protected:
	TSquareMatrix<double> A;
	TSquareMatrix<double> E;
	TSquareMatrix<double> B;
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
	std::vector<double> Vn;

	std::vector<double> local_error_v1;
	std::vector<double> local_error_v2;
	std::vector<double> V1;
	std::vector<double> V2;
	


	double lambda;
	double sigma;
	double temp;
	double h ;

	double a = 0.5 - (sqrt(3) / 6);
	double b = 0.25 - (sqrt(3) / 6);
	double c = 0.5 + (sqrt(3) / 6);
	double d = 0.25 + (sqrt(3) / 6);
	size_t max_count_of_iter;
	double x_l = 0, x_r = 0;
	double step = 0;
public:
	TOptimalRK(double left_x, double right_x, double _h = 0.1, double V1 = 0, double V2 = 0, size_t max_count_of_iter = 10000000, double precision = 1e-5)
	{
		A.fill(-500.005, 499.995, 499.995, -500.005);
		E.fill(1.0, 0.0, 0.0, 1.0);
		//Vn[0] = V1;
		//Vn[1] = V2;
		Vn = { V1,V2 };
		h = _h;
		x_l = left_x;
		x_r = right_x;

		lambda = h * d;
		sigma = h * h * b * d;

	};
	
	void FillZero()
	{
		B.fill(0, 0, 0, 0);
		F.fill(0, 0, 0, 0);
		M.fill(0, 0, 0, 0);
		Q.fill(0, 0, 0, 0);
		Vn_lambda_F_Vn.clear();
		lambda_F_Vn.clear();
		Vn_hbK_2.clear();
		hbK_2.clear();
		K_1.clear();
		K_2.clear();

	};

	void Get_K(double _h, std::vector<double> _Vn)
	{
		Vn = _Vn;
		temp = 1;
		h = _h;
	

		B = E * 4 - A * h;
		B = B.GetReverseMatrix();
		///////
		F = B * A * 4;
		M = (A * sigma) * F;
		M = E * 4 - (A * sigma) * F - (A * h);
		M = M.GetReverseMatrix();
		Q = M * 4 * A;

		Vn_lambda_F_Vn = Vn;
		lambda_F_Vn = (F * lambda) * Vn;

		Vn_lambda_F_Vn[0] += lambda_F_Vn[0];
		Vn_lambda_F_Vn[1] += lambda_F_Vn[1];

		K_2 = Q * Vn_lambda_F_Vn;

		Vn_hbK_2 = Vn;

		hbK_2 = K_2;
		hbK_2[0] = hbK_2[0] * b * h;
		hbK_2[1] = hbK_2[1] * b * h;

		Vn_hbK_2[0] += hbK_2[0];
		Vn_hbK_2[1] += hbK_2[1];
		K_1 = F * Vn_hbK_2;

		std::cout << std::setprecision(16) << "K_1 = " << K_1[0] << ' ' << K_1[1] << std::endl;
		std::cout << std::setprecision(16) << "K_2 = " << K_2[0] << ' ' << K_2[1] << std::endl;

	};

	void Get_Points(double prev_V1, double prev_V2, double h_i)
	{
		double curr_x = x_l;
		size_t count_of_iter = 0;
		std::fstream f;
		f.open("output.txt", std::fstream::in | std::fstream::out);
		std::ifstream f_in;
		step = h;
		
		V1.push_back(prev_V1);
		V2.push_back(prev_V2);
		

		do 
		{
			
			Vn[0] = V1[count_of_iter];
			Vn[1] = V2[count_of_iter];
			Get_K(step, Vn);
			
			V1.push_back(V1[count_of_iter] + (step / 2) * (K_1[0] + K_2[0]));
			V2.push_back(V2[count_of_iter] + (step / 2) * (K_1[1] + K_2[1]));
			
			std::cout << "V1 = " << V1[count_of_iter] << std::endl;
			std::cout << "V2 = " << V2[count_of_iter] << std::endl;
			std::cout << "curr_x" << curr_x << std::endl;
			std::cout << std::endl;
			curr_x = curr_x + step;
			count_of_iter++;
			FillZero();


		} while (curr_x <= x_r+step);

	};

	void Insert_In_File(std::vector<double> new_array, size_t count, std::fstream& stream)
	{
		if (stream.is_open())
		{
			for (size_t i = 0; i < new_array.size(); i++)
				stream << new_array[i] << std::setprecision(16) << " ";
			stream << "\n";
			stream << "\n";
		}
		else
			throw "The file isn't exist";
	}

};