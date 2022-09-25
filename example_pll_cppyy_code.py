import cppyy
cppyy.load_library("/home/autumn/anaconda3/lib/libiomp5.so")
cppyy.add_include_path('../np_vs_eigen/eigen/')
cppyy.include('easy_example.cpp')
import datetime as dt
print('Starting the function call now ')
MatrixXd = cppyy.gbl.Eigen.MatrixXd
start = dt.datetime.now()
output = cppyy.gbl.pll_somelinalgeb()
stop = dt.datetime.now()
print((stop-start), 'seconds')

for each in output[:10]:
    print(each[0])
