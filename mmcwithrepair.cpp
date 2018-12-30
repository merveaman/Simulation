/*********************************************************
A simple M/M/m/k queue simulation


*********************************************************/

#include<iostream>
#include <stdlib.h> // Needed for rand() and RAND_MAX
#include <cmath> // Needed for log()
#include <random>
using namespace std;

//----- Constants -------------------------------------------------------------
#define SIM_TIME 1.0e6 // Simulation time
#define ARR_TIME 1.25 // Mean time between arrivals
#define SERV_TIME 1.00 // Mean service time
#define IDLE 0         // server status
#define BUSY 1         // server status

//----- Function prototypes ---------------------------------------------------
double expntl(double x); // Generate exponential RV with mean x
double lognormal(double x);
double weibull(double x);


/********************** Main program******************************/
int main(void)
{

double end_time = SIM_TIME; // Total time to simulate
double Ta=ARR_TIME ; // Mean time between arrivals
double Ts = SERV_TIME; // Mean service time
int server_status=0;
int m=2;
int m1; // servers 1
int m2; //server 2
double time = 0.0; // Simulation time
double t1 = 0.0; // Time for next event #1 (arrival)
double t2 = SIM_TIME; // Time for next event #2 (departure)
long int n = 0; // Number of customers in the system
long int k=10; //buffer space or queue size
float p;
double c = 0.0; // Number of service completions
double s = 0.0; // Area of number of customers in system
double b = 0.0; // Total busy time
double tn = time; // Variable for "last event time"
double tb; // Variable for "last start of busy time"
double x; // Throughput
double l; // Mean number in the system
double w; // Mean residence time // average time spent in system
double u; // Utilization
// Main simulation loop
//for(int i=1;i<=SIM_TIME;i++)
//{ p=0.02*i; Ta=Ts/(m*p);

while (time < end_time)
{ 
if (t1 < t2) // *** Event #1 (arrival)
{
time = t1;
s = s + n * (time - tn); // Update area under "s" curve
if(n<k) 
n++;
tn = time; // tn = "last event time" for next event
t1 = time + expntl(Ta);
if (n == 1)
{
tb = time;
t2 = time + weibull(Ts);
}

}
else // *** Event #2 (departure)
{
time = t2;
s = s + n * (time - tn); // Update area under "s" curve


if(n>m)
n-=m; 
else n=0;

tn = time; // tn = "last event time" for next event
c++; // Increment number of completions


if (n > 0)
t2 = time + weibull(Ts);
else

t2 = end_time;
b = b + time - tb; // Update busy time sum if empty
}

}
// End of simulation so update busy time sum

b = b + time - tb;

x = c / time; // Compute throughput rate
l = s / time; // Compute mean number in system
w = l / x; // Compute mean residence or system time
u = b/(time*m); // Compute server utilization

//if(l>0)
//cout<<p<<"\t"<<l<<endl;
//}
//cout<<"Throuput="<<x<<endl;
//cout<<"Average number of customers in system="<<l<<endl;
//cout<<"Time spent in queue="<<x<<endl;

// Output results
cout<<"========================================== ===================== \n"<<endl;
cout<<"= *** Results from M/M/c/k simulation *** = \n"<<endl;
cout<<"========================================== ===================== \n"<<endl;
cout<<"= Total simulated time =  "<< end_time<<"sec "<<endl;
cout<<"========================================== ===================== \n"<<endl;
cout<<"= INPUTS: \n";
cout<<"= Mean time between arrivals = "<< Ta<<"  sec "<<endl;
cout<<"= Mean service time = "<<Ts<<"  sec "<<endl;
cout<<"========================================== ===================== \n"<<endl;
cout<<"= OUTPUTS: \n"<<endl;
cout<<"= Number of completions = "<<c<<"  cust "<<endl;
cout<<"= Throughput rate = "<<x<<"  cust/sec "<<endl;
cout<<"= Server utilization = "<< u<<endl;
cout<<"= Mean  number of customer in system = "<< l<<"  cust "<<endl;
cout<<"= Mean residence time = " << w<<"  sec "<<endl;

cout<<"========================================== ===================== \n";

return 0;
}

/************************************************************************
Function to generate exponentially distributed RVs
Input: x (mean value of distribution)
Output: Returns with exponential RV
*************************************************************************/
double expntl(double x)
{
double z; // Uniform random number from 0 to 1
// Pull a uniform RV (0 < z < 1)
do
{
z = ((double) rand() / RAND_MAX);
}
while ((z == 0) || (z == 1));

return(-x * log(z));
}

double unif() {
	double z; // Uniform random number from 0 to 1
// Pull a uniform RV (0 < z < 1)
z = ((double) rand() / RAND_MAX);
return z;
}
double lognormal(double x)
{ 
	std::default_random_engine generator;
    std::lognormal_distribution<double> distribution(0.1,x);
    double number = distribution(generator);
    return number;
	
	
}
double weibull(double x) // assume b=1 and g=0
{   std::default_random_engine generator;
   std::weibull_distribution<double> distribution(2.0,x);
   double number = distribution(generator);
   return number;
	
}


