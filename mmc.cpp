#include<iostream>
#include <stdlib.h>
#include <random>
#include <cmath> 
using namespace std;
#define SIM_TIME 1.0e6 
#define ARR_TIME 1.25 
#define SERV_TIME 1.00 
#define IDLE 0         
#define BUSY 1

double expntl(double x);
int poissonDist(void);


int main(void)
{

double end_time = SIM_TIME; // Total time to simulate
double Ta=poissonDist(); // Mean time between arrivals
double Ts = SERV_TIME; // Mean service time
int server_status=0;
int m=2;
int m1; // servers 1
int m2; //server 2
double time = 0.0; // Simulation time
double arrival_time = 0.0; // Time for next event #1 (arrival)
double departure_time = SIM_TIME; // Time for next event #2 (departure)
long int n = 0; // Number of customers in the system
long int k=1000; //buffer space or queue size
float p;
double c = 0.0; // Number of service completions
double customers_in_system = 0.0;
double total_busy_time = 0.0; 
double last_event_time = time; 
double current_busy_time_start_time; 
double throughput;  
double l; // Mean number in the system
double w; // Mean residence time // average time spent in system
double u; // Utilization

while (time < end_time)
{ 
if (arrival_time < departure_time) 
{
time = arrival_time;
customers_in_system = customers_in_system + n * (time - last_event_time); 
if(n<k) 
n++;
last_event_time = time; 
arrival_time = time + poissonDist();
if (n == 1)
{
current_busy_time_start_time = time;
departure_time = time + expntl(Ts);
}

}
else 
{
time = departure_time;
customers_in_system = customers_in_system + n * (time - last_event_time); 

if(n>m)
n-=m; 
else n=0;

last_event_time = time;
c++; 


if (n > 0)
departure_time = time + expntl(Ts);
else

departure_time = end_time;
total_busy_time = total_busy_time + time - current_busy_time_start_time; 
}

}

total_busy_time = total_busy_time + time - current_busy_time_start_time;
throughput = c / time; 
l = customers_in_system / time; 
w = l / throughput; 
u = total_busy_time/(time*m); 

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
cout<<"Throughput rate = "<<throughput<<"  cust/sec "<<endl;
cout<<"Server utilization = "<< u<<endl;
cout<<"Mean  number of customer in system = "<< l<<"  cust "<<endl;
cout<<"Mean residence time = " << w<<"  sec "<<endl;

cout<<"\n";

return 0;
}

double expntl(double x)
{
double z; 
do
{
z = ((double) rand() / RAND_MAX);
}
while ((z == 0) || (z == 1));

return(-x * log(z));
}

double unif() {
	double z;
	z = ((double) rand() / RAND_MAX);
	return z;
}
double lognormal(double x)
{
	
	double z,X,Y;
	double r1 = unif();
	double r2 = unif();
	return z;
}
double weibull(double a) 
{   double x;
	double r1 = unif();
	x=(-a*log(1-r1));
	return x;	
}

int poissonDist(void){

default_random_engine generator;
poisson_distribution<int> distribution(4.1);
int number = distribution(generator);
return number;
}
