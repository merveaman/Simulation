#include<iostream> 
#include <random> 
#include <cmath> 
using namespace std;

class RandomnumberGeneration{
double x;
public:	
double expntl(double x); 
double lognormal(double x);
double weibull(double x);
};

double RandomnumberGeneration::expntl(double x){
double z; // Uniform random number from 0 to 1
         // Pull a uniform RV (0 < z < 1)
do
{
z = ((double) rand() / RAND_MAX);
}
while ((z == 0) || (z == 1));

return(-x * log(z));
	
}

double RandomnumberGeneration::lognormal(double x){
	std::default_random_engine generator;
    std::lognormal_distribution<double> distribution(0.1,x);
    double number = distribution(generator);
    return number;
	
}
double RandomnumberGeneration::weibull(double x){
   std::default_random_engine generator;
   std::weibull_distribution<double> distribution(2.0,x);
   double number = distribution(generator);
   return number;
	
}

int main()
{
	RandomnumberGeneration random;
	double x=1.25;
	double number;
	number=random.expntl(x);
	cout<<number<<endl;
	number=random.lognormal(x);
	cout<<number<<endl;
	number=random.weibull(x);
	cout<<number<<endl;
	return 0;
}
