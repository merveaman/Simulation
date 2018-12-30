//----- Include files ----------------------------------------------------------
#include<iostream> // Needed for printf()
#include <random> //and rand()
#include <cmath> // Needed for log()

//----- Constants --------------------------------------------------------------
#define SIM_TIME 1.0e6 // Simulation time
#define ARR_TIME 1.25 // Mean time between arrivals
#define SERV_TIME 1.00 // Mean service time

using namespace std;
//----- Function prototypes ----------------------------------------------------

//double exponential(double x); // Generate exponential RV with mean x


class MM1
{
double end_time; //Total time to simulate
double Ta;      //Mean time between arrivals
double Ts;     // Mean service time
double time; // Simulation time
double t1;  // Time for next event #1 (arrival)
double t2; //Time for next event #2 (departure)
unsigned int n; //Number of customers in the system
unsigned int c;  // Number of service completions
double b; // Total busy time
double s;//  number of customers in system
double tn = time; // Variable for "last event time"
double tb; // Variable for "last start of busy time"
double x; // Throughput
double u; // Utilization
double l; // Mean number in the system
double w; // Mean residence time
public:
void initialize();	
void simulate();
void report();
double exponential(double x);
};

void MM1::initialize()
{    end_time = SIM_TIME; // Total time to simulate
     Ta = ARR_TIME; // Mean time between arrivals
     Ts = SERV_TIME; // Mean service time
	 n = 0; // Number of customers in the system
     c = 0; // Number of service completions 
 	 b = 0.0; // Total busy time
     s = 0.0; // Area of number of customers in system
     time = 0.0; // Simulation time
     t1 = 0.0; // Time for next event #1 (arrival)
     t2 = SIM_TIME; // Time for next event #2 (departure)
	 tn = time; 
}

void MM1::simulate()
{ while (time < end_time)
{
if (t1 < t2) // *** Event #1 (arrival) ***
{
time = t1;
s = s + n * (time - tn); // Update area under "s" curve
n++;
tn = time; // tn = "last event time" for next event
t1 = time + exponential(Ta);
if (n == 1)
{
tb = time; // Set "last start of busy time"
t2 = time + exponential(Ts);
}
}
else // *** Event #2 (departure) ***
{
time = t2;
s = s + n * (time - tn); // Update area under "s" curve
n--;
tn = time; // tn = "last event time" for next event
c++; // Increment number of completions
if (n > 0)
t2 = time + exponential(Ts);
else
{
t2 = SIM_TIME;
b = b + time - tb; // Update busy time sum if empty
}
}
}

// End of simulation so update busy time sum
b = b + time - tb;

// Compute outputs
x = c / time; // Compute throughput rate
u = b / time; // Compute server utilization
l = s / time; // Compute mean number in system
w = l / x; // Compute mean residence or system time
	
}


double MM1::exponential(double x){
	double z; // Uniform random number from 0 to 1

// Pull a uniform RV (0 < z < 1)
do
{
z =z = ((double) rand() / RAND_MAX);
}
while ((z == 0) || (z == 1));

return(-x * log(z));
}

void MM1::report()
{
cout<<"========================================== ===================== \n"<<endl;
cout<<"= *** Results from M/M/1 simulation *** = \n"<<endl;
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
	
}
	
int main()
{
	
	MM1 queue;
	queue.initialize();
	queue.simulate();
	queue.report();

	return 0;
}



