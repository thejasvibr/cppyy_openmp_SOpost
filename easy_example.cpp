#include <omp.h>
#include <iostream>
#include <Eigen/Dense>
#include <chrono>
#include <vector>
#include <thread>

using Eigen::VectorXd;
using Eigen::MatrixXd;

std::vector<MatrixXd> some_linearalgebra(){
	std::vector<MatrixXd> solutions;
	std::srand((unsigned int) time(0));
	MatrixXd arraygeom(5,3);
	arraygeom = MatrixXd::Random(5,3);
	VectorXd row1 = arraygeom.block(0,0,1,3).transpose();
	arraygeom.rowwise() -= row1.transpose();
	MatrixXd pinv_arraygeom(3,5);


	// calculate the pseudoinverse of arraygeom
	pinv_arraygeom = arraygeom.completeOrthogonalDecomposition().pseudoInverse();
	//std::cout << pinv_arraygeom << std::endl;
	solutions.push_back(pinv_arraygeom);
	solutions.push_back(pinv_arraygeom);
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	return solutions;
	//return 0;
}


std::vector<std::vector<MatrixXd>> pll_somelinalgeb(){

int num_runs = 5000;
std::vector<std::vector<MatrixXd>> all_solns(num_runs);

#pragma omp parallel for
for (int i=0; i<num_runs; i++){
	all_solns[i] = some_linearalgebra();
}
return all_solns;
}

int main(){
std::vector<MatrixXd> main_out;
main_out = some_linearalgebra();

auto start = std::chrono::system_clock::now();

std::vector<std::vector<MatrixXd>> main2_out;
main2_out = pll_somelinalgeb();
auto end = std::chrono::system_clock::now();
std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;


return 0;
}


