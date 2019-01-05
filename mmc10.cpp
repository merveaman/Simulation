/*********************************************************
A simple M/M/c/k queue simulation


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
double time; // Simulation time
double arrival_time; // Time for next event #1 (arrival)
double departure_time; // Time for next event #2 (departure)
double departure_time2; // Time for next event #3 (departure)
long int n; // Number of customers in the system in the queue
long int queue_size; //buffer space or queue size
double c ; // Number of service completions
double customers_in_system; //  number of customers in system
double total_busy_time; // Total busy time
double last_event_time ; // Variable for "last event time"
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
 arrival_time = 0.0; // Time for next event #1 (arrival)
 departure_time = SIM_TIME; // Time for next event #2 (departure1)
 departure_time2= SIM_TIME;  //  Time for next event #3 (departure2)
 n = 0; // Number of customers in the system
 queue_size=10; //buffer space or queue size
 c = 0.0; // Number of service completions
 customers_in_system = 0.0; // Area of number of customers in system
 total_busy_time = 0.0; // Total busy time
 last_event_time = time; // Variable for "last event time"

}


void MMC::simulate(){
	while (time < end_time)
{ 
if (arrival_time < departure_time)	{  // arrival process
time = arrival_time;
customers_in_system = customers_in_system + n * (time - last_event_time); // Update area under "s" curve
if (server_status1==BUSY && server_status2==BUSY){
             n++;
             
if (n > queue_size) 
        {
            cout<<"\nOverflow of the array time_arrival at";
             
            cout<<"time: "<<time;
             
           break;
        }


last_event_time = time; // tn = "last event time" for next event
arrival_time = time + expntl(Ta);	
tb = time;
departure_time = time + expntl(Ts);


}

 else if (server_status1 == BUSY &&  server_status2==IDLE)
    {
    	server_status2= BUSY;
         
        tn = time; // tn = "last event time" for next event
arrival_time = time + expntl(Ta);	
tb = time;
departure_time = time + expntl(Ts);

	}
	else if (server_status1 == IDLE &&  server_status2==BUSY)
    {
    	server_status1= BUSY;
         
          
last_event_time = time; // tn = "last event time" for next event
arrival_time = time + expntl(Ta);	
tb = time;
departure_time2 = time + expntl(Ts);

	}
 
    else
    {
        server_status1 = BUSY;
        server_status2= BUSY;
         
         
last_event_time = time; // tn = "last event time" for next event
arrival_time = time + expntl(Ta);	
tb = time;
departure_time = time + expntl(Ts);
departure_time2=  time + expntl(Ts);

         
    }


}

else{ // departure process from server 1 and server 2
	
time = departure_time;
customers_in_system = customers_in_system + n * (time - last_event_time); 
if (n==0)
{          server_status1= IDLE;
           server_status2= IDLE;
           departure_time = end_time;
           departure_time2 = end_time;
           total_busy_time=total_busy_time+time-tb;
	
}

else{
	--n;  
	last_event_time = time; // tn = "last event time" for next event
    c++;    
	departure_time = time + expntl(Ts);
	departure_time2 = time + expntl(Ts);
	total_busy_time=total_busy_time+time-tb;
	lq++;
    delay= arrival_time-time;
    wq+= delay;
}
 
	
}
	

}
// End of simulation so update busy time sum

total_busy_time = total_busy_time + time - tb;
x = c / time; // Compute throughput rate
l = customers_in_system / time; // Compute mean number in system
w = l / x; // Compute mean residence or system time
u = b/(time*m); // Compute server utilization
lq=lq/time;     //compute mean queue length
wq=wq/c;       //compute waiting time in queue

po=1-0.8;

	
}

void MMC::report()
{

cout<<"========================================== ===================== \n"<<endl;
cout<<"\n"<<endl;
cout<<"Results from M/M/c/10 simulation\n"<<endl;
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
	return 0;
}


