//Name: Jackson E. Rollins
//Date: 5/4/2022
//ID: 932932878

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

int	NowYear;		// 2022 - 2027
int	NowMonth;		// 0 - 11
unsigned int seed = 0;

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int		NowNumDeer;		// number of deer in the current population
int		NowNumWolf;

const float GRAIN_GROWS_PER_MONTH =		9.0;
const float ONE_DEER_EATS_PER_MONTH =	1.0;
const int ONE_WOLF_KILL_DEER_PER_MONTH = 2;
const float ONE_WOLF_RUIN_GRAIN_PER_MONTH = 1.0;

const float AVG_PRECIP_PER_MONTH =		7.0;	// average
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
const float RANDOM_PRECIP =				2.0;	// plus or minus noise

const float AVG_TEMP =					60.0;	// average
const float AMP_TEMP =					20.0;	// plus or minus
const float RANDOM_TEMP =				10.0;	// plus or minus noise

const float MIDTEMP =					40.0;
const float MIDPRECIP =					10.0;

omp_lock_t		Lock;
volatile int	NumInThreadTeam;
volatile int	NumAtBarrier;
volatile int	NumGone;

float Ranf(unsigned int *, float, float);
int Ranf(unsigned int *, int, int);
float SQR(float);
void Deer();
void Grain();
void Watcher();
void Wolf();
void InitBarrier(int);
void WaitBarrier();

int main(int argc, char *argv[]){
	#ifndef _OPENMP
		fprintf(stderr, "No OpenMP support!\n");
		return 1;
	#endif

	srand(time(NULL));

	// starting date and time:
	NowMonth =    0;
	NowYear  = 2022;

	// starting state (feel free to change this if you want):
	NowNumDeer = 5;
	NowNumWolf = 2;
	NowHeight =  15.;

	float ang = (30.*(float)NowMonth + 15.) * (M_PI / 180.);

	float temp = AVG_TEMP - AMP_TEMP * cos( ang );
	NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);

	float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
	NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
	if(NowPrecip < 0.){
		NowPrecip = 0.;
	}

	InitBarrier(NUMT);
	omp_set_num_threads(NUMT);
	#pragma omp parallel sections
	{
		#pragma omp section
		{
			Deer();
		}

		#pragma omp section
		{
			Grain();
		}

		#pragma omp section
		{
			Watcher();
		}

		#pragma omp section
		{
			Wolf();	// your own
		}
	}       // implied barrier -- all functions must return in order
		// to allow any of them to get past here
}

void Deer(){
	while(NowYear < 2028){
		int nextNumDeer = NowNumDeer - NowNumWolf * ONE_WOLF_KILL_DEER_PER_MONTH;
		int carryingCapacity = (int)(NowHeight);
		if(nextNumDeer < carryingCapacity){
			nextNumDeer++;
		}
		else{
			if(nextNumDeer > carryingCapacity){
				nextNumDeer--;
			}
		}
		if(nextNumDeer < 0){
			nextNumDeer = 0;
		}

		WaitBarrier();
		NowNumDeer = nextNumDeer;
		WaitBarrier();
		WaitBarrier();
	}
}

void Grain(){
	while(NowYear < 2028){
		float tempFactor = exp(-SQR((NowTemp - MIDTEMP) / 10.));
		float precipFactor = exp(-SQR((NowPrecip - MIDPRECIP) / 10.));

		float nextHeight = NowHeight;
 		nextHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
 		nextHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;
		nextHeight -= (float)NowNumWolf * ONE_WOLF_RUIN_GRAIN_PER_MONTH;
		if(nextHeight < 0.){
			nextHeight = 0.;
		}

		WaitBarrier();
		NowHeight = nextHeight;
		WaitBarrier();
		WaitBarrier();
	}
}

void Watcher(){
	while(NowYear < 2028){
		WaitBarrier();
		WaitBarrier();

		printf("%d-%02d,%f,%f,%f,%d,%d\n", NowYear, NowMonth + 1, NowPrecip, NowTemp, NowHeight, NowNumDeer, NowNumWolf);

		NowMonth++;
		if(NowMonth >=12){
			NowYear++;
			NowMonth = 0;
		}

		float ang = (30.*(float)NowMonth + 15.) * (M_PI / 180.);

		float temp = AVG_TEMP - AMP_TEMP * cos( ang );
		NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);

		float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
		NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
		if(NowPrecip < 0.){
			NowPrecip = 0.;
		}

		WaitBarrier();
	}
}

void Wolf(){
	while(NowYear < 2028){
		int nextNumWolf = NowNumWolf;
		int carryingCapacity = NowNumDeer;
		if(nextNumWolf < carryingCapacity){
			nextNumWolf++;
		}
		else{
			if(nextNumWolf > carryingCapacity){
				nextNumWolf--;
			}
		}
		if(nextNumWolf < 0){
			nextNumWolf = 0;
		}

		WaitBarrier();
		NowNumWolf = nextNumWolf;
		WaitBarrier();
		WaitBarrier();
	}
}

float
Ranf( unsigned int *seedp,  float low, float high )
{
        float r = (float) rand_r( seedp );              // 0 - RAND_MAX

        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}


int
Ranf( unsigned int *seedp, int ilow, int ihigh )
{
        float low = (float)ilow;
        float high = (float)ihigh + 0.9999f;

        return (int)(  Ranf(seedp, low,high) );
}

float
SQR( float x )
{
        return x*x;
}

void
InitBarrier( int n )
{
        NumInThreadTeam = n;
        NumAtBarrier = 0;
	omp_init_lock( &Lock );
}

void
WaitBarrier( )
{
        omp_set_lock( &Lock );
        {
                NumAtBarrier++;
                if( NumAtBarrier == NumInThreadTeam )
                {
                        NumGone = 0;
                        NumAtBarrier = 0;
                        // let all other threads get back to what they were doing
			// before this one unlocks, knowing that they might immediately
			// call WaitBarrier( ) again:
                        while( NumGone != NumInThreadTeam-1 );
                        omp_unset_lock( &Lock );
                        return;
                }
        }
        omp_unset_lock( &Lock );

        while( NumAtBarrier != 0 );	// this waits for the nth thread to arrive

        #pragma omp atomic
        NumGone++;			// this flags how many threads have returned
}