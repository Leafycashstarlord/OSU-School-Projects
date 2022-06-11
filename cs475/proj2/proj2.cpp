//Name: Jackson E. Rollins
//Date: 4/27/2022
//ID: 932932878

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <fstream>

#ifndef NUMTIMES
#define NUMTIMES 20
#endif

int NUMNODES = 0;
int NUMT = 0;

// The code to evaluate the height at a given <i>iu</i> and <i>iv</i> is:

const float N = 2.5f;
const float R = 1.2f;

float
Height( int iu, int iv )	// iu,iv = 0 .. NUMNODES-1
{
	float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);	// -1. to +1.
	float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);	// -1. to +1.

	float xn = pow( fabs(x), (double)N );
	float yn = pow( fabs(y), (double)N );
	float rn = pow( fabs(R), (double)N );
	float r = rn - xn - yn;
	if( r <= 0. )
	        return 0.;
	float height = pow( r, 1./(double)N );
	return height;
}


// The main Program

#define XMIN     -1.
#define XMAX      1.
#define YMIN     -1.
#define YMAX      1.

float Height( int, int );	// function prototype

int main( int argc, char *argv[ ] )
{
	if(argc > 2){
		NUMT = atoi(argv[1]);
		NUMNODES = atoi(argv[2]);
	}
	omp_set_num_threads(NUMT);

	// the area of a single full-sized tile:
	// (not all tiles are full-sized, though)

	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
				( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

	// sum up the weighted heights into the variable "volume"
	// using an OpenMP for-loop and a reduction:

	double maxPerf = 0.;
	float volume = 0;

	for(int i = 0; i < NUMTIMES; i++){
		double time1 = omp_get_wtime();
		#pragma omp parallel for collapse(2) default(none) shared(fullTileArea, NUMNODES) reduction(+:volume)
		for( int iv = 0; iv < NUMNODES; iv++ ){
			for( int iu = 0; iu < NUMNODES; iu++ ){
				float z = Height( iu, iv );
				float temp = fullTileArea * z;
				if((iv == 0 || iv == NUMNODES - 1) && (iu == 0 || iu == NUMNODES - 1)){
					temp = temp * 0.25;
				}else if((iv == 0 || iv == NUMNODES - 1) || (iu == 0 || iu == NUMNODES - 1)){
					temp = temp * 0.5;
				}
				volume = volume + temp;
			}
		}

		double time2 = omp_get_wtime();
		double megaHeightsPerSecond = (double)(NUMNODES * NUMNODES) / (time2-time1) / 1000000.;
        if(megaHeightsPerSecond > maxPerf){
            maxPerf = megaHeightsPerSecond;
        }
	}
	volume = volume / 10;
	printf("%2d,%8d,%6.2lf,%6.2lf\n",NUMT, NUMNODES, maxPerf,volume);
}