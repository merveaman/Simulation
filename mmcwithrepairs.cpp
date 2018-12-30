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



class MMC{
	
double end_time; // Total time to simulate
double Ta ; // Mean time between arrivals
double Ts ; // Mean service time
int server_status;
int m,m1, m2; //server 1 and 2
double time; // Simulation time
double t1 ; // Time for next event #1 (arrival)
double t2 ; // Time for next event #2 (departure)
long int n; // Number of customers in the system
long int k; //buffer space or queue size
float p;
double c ; // Number of service completions
double s ; //  number of customers in system
double b ; // Total busy time
double tn ; // Variable for "last event time"
double tb; // Variable for "last start of busy time"
double x; // Throughput
double l; // Mean number in the system
double w; // Mean residence time // average time spent in system
double u; // Utilization

public:
    void initialize();	
    void simulate();
    void report();
    double expntl(double x);
    double lognormal(double x);
    double weibull(double x);
    int poissonDist();
};
/********************** Functions******************************/
void MMC::initialize()
{
 end_time = SIM_TIME; // Total time to simulate
 Ta=ARR_TIME ; // Mean time between arrivals
 Ts = SERV_TIME; // Mean service time
server_status=0;
 m=2;
 time = 0.0; // Simulation time
 t1 = 0.0; // Time for next event #1 (arrival)
 t2 = SIM_TIME; // Time for next event #2 (departure)
 n = 0; // Number of customers in the system
 k=10; //buffer space or queue size
 c = 0.0; // Number of service completions
 s = 0.0; // Area of number of customers in system
 b = 0.0; // Total busy time
 tn = time; // Variable for "last event time"

}


void MMC::simulate(){
	while (time < end_time)
{ 
if (t1 < t2) // *** Event #1 (arrival)
{
time = t1;
s = s + n * (time - tn); // Update area under "s" curve
if(n<k) 
n++;
tn = time; // tn = "last event time" for next event
t1 = time + expntl(poissonDist());
if (n == 1)
{
tb = time;
t2 = time + weibull(Ts);
}

}
else // *** Event #2 (departure)
{
time = t2;
s = s + n * (time - tn); 

if(n>m)
n-=m; 
else n=0;

tn = time; // tn = "last event time" for next event
c++; 


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
	
}

void MMC::report()
{

cout<<"========================================== ===================== \n"<<endl;
cout<<"\n"<<endl;
cout<<"Results from M/M/c simulation\n"<<endl;
cout<<"\n"<<endl;
cout<<"Total simulated time =  "<< end_time<<"seconds "<<endl;
cout<<"\n"<<endl;
cout<<"INPUTS: \n";
cout<<"Mean time between arrivals = "<< Ta<<"  seconds "<<endl;
cout<<"Mean service time = "<<Ts<<"  seconds "<<endl;
cout<<"\n"<<endl;
cout<<"OUTPUTS: \n"<<endl;
cout<<"Number of completions = "<<c<<"  cust "<<endl;
cout<<"Throughput rate = "<<x<<"  cust/sec "<<endl;
cout<<"Server utilization = "<< u<<endl;
cout<<"Mean  number of customer in system = "<< l<<"  cust "<<endl;
cout<<"Mean residence time = " << w<<"  sec "<<endl;
cout<<"========================================== ===================== \n";

	
}

double MMC::expntl(double x)
{ double z; 
        
do
{
z = ((double) rand() / RAND_MAX);
}
while ((z == 0) || (z == 1));

return(-x * log(z));
		
}


double MMC::lognormal(double x)
{
	std::default_random_engine generator;
    std::lognormal_distribution<double> distribution(0.1,x);
    double number = distribution(generator);
    return number;
}

double MMC::weibull(double x){
	std::default_random_engine generator;
    std::weibull_distribution<double> distribution(2.0,x);
    double number = distribution(generator);
    return number;
	
}
int MMC::poissonDist(){
	
	std::default_random_engine generator;
    std::poisson_distribution<int> distribution(3.5);
    int number = distribution(generator);
    return number;
	
}


/********************** Main program******************************/
int main()
{
	MMC queue;
	queue.initialize();
	queue.simulate();
	queue.report();
}


