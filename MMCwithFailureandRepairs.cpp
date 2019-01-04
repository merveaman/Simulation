/*********************************************************
A simple M/M/c with breakdowns and repairs

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
int server_status1;
int server_status2;
int m;

double delay; // waiting time in queue
double Delay; // delay caused by failure and repairs
double time; // Simulation time
double T_br; // time to breakdown
double T_rp; // time to repair
double t1 ; // Time for next event #1 (arrival)
double t2 ; // Time for next event #2 (departure)
double t3; // Time for next event #3 (departure)
long int n; // Number of customers in the system in the queue
double c ; // Number of service completions
double s ; //  number of customers in system
double b ; // Total busy time
double tn ; // Variable for "last event time"
double tb; // Variable for "last start of busy time"
double x; // Throughput
double l; // Mean number in the system
float lq; // Average number in queue
double w; // Average time spent in system
float wq; // Average waiting time in queue
double u; // Utilization
float po; // probability of zero customers in system


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
server_status1=0;
server_status2=0;
m=2;
 time = 0.0; // Simulation time
 t1 = 0.0; // Time for next event #1 (arrival)
 t2 = SIM_TIME; // Time for next event #2 (departure1)
 t3= SIM_TIME;  //  Time for next event #3 (departure2)
 n = 0; // Number of customers in the system

 c = 0.0; // Number of service completions
 s = 0.0; // Area of number of customers in system
 b = 0.0; // Total busy time
 tn = time; // Variable for "last event time"

}


void MMC::simulate(){
	while (time < end_time)
{ 
if (t1 < t2)	{  // arrival process
time = t1;
s = s + n * (time - tn); // Update area under "s" curve

T_br=weibull(1);
if(T_br>t1){
	Delay+=T_br;
	T_rp=lognormal(1);
	Delay+=T_rp; 
	
}

if (server_status1==BUSY && server_status2==BUSY){
             n++;
tn = time; // tn = "last event time" for next event
t1 = time + expntl(Ta);	
tb = time;
t2 = time + expntl(Ts);


}

 else if (server_status1 == BUSY &&  server_status2==IDLE)
    {
    	server_status2= BUSY;
         
        tn = time; // tn = "last event time" for next event
t1 = time + expntl(Ta);	
tb = time;
t2 = time + expntl(Ts);

	}
	else if (server_status1 == IDLE &&  server_status2==BUSY)
    {
    	server_status1= BUSY;
         
          
tn = time; // tn = "last event time" for next event
t1 = time + expntl(Ta);	
tb = time;
t3 = time + expntl(Ts);

	}
 
    else
    {
        server_status1 = BUSY;
        server_status2= BUSY;
         
         
tn = time; // tn = "last event time" for next event
t1 = time + expntl(Ta);	
tb = time;
t2 = time + expntl(Ts);
t3=  time + expntl(Ts);

         
    }


}

else{ // departure process from server 1 and server 2
	
time = t2;
s = s + n * (time - tn); 
if (n==0)
{          server_status1= IDLE;
           server_status2= IDLE;
           t2 = end_time;
           t3 = end_time;
           b=b+time-tb;
	
}

else{
	--n;  
	tn = time; // tn = "last event time" for next event
    c++;    
	t2 = time + expntl(Ts);
	t3 = time + expntl(Ts);
	b=b+time-tb;
	lq++;
    delay= t1-time+Delay;
    wq+= delay;
}
 
	
}
	

}
// End of simulation so update busy time sum

b = b + time - tb;
x = c / time; // Compute throughput rate
l = s / time; // Compute mean number in system
w = l / x; // Compute mean residence or system time
u = Ta/(Ts*m); // Compute server utilization
lq=lq/time;   // compute mean queue length
wq=wq/c;  // Average waiting time increased due to failure and repairs


po=1-0.8;

	
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
cout<<"Average  number of customer in system L = "<< l<<"  cust "<<endl;
cout<<"Average waiting  time in system W = " << w<<"  sec "<<endl;
cout<<"Average  number of customer in queue Lq = "<<lq <<"  cust "<<endl;
cout<<"Average waiting  time in queue Wq = " << wq<<"  sec "<<endl;

cout<<"Probability of zero customer in system Po= "<<po<<endl;
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
    std::lognormal_distribution<double> distribution(0.1,x); //assumption that mean= 0.1 and variance =1
    double number = distribution(generator);
    return number;
}

double MMC::weibull(double x){
	std::default_random_engine generator;
    std::weibull_distribution<double> distribution(2.0,x); // assumption that  b= 1 and n=0
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
	return 0;
}

