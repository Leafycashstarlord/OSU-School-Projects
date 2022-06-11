//Name: Jackson E. Rollins
//ID: 932932878
//Date: 4/4/2022

#include <omp.h>
#include <stdio.h>
#include <math.h>

#define NUMT4       4
#define NUMT1       1
#define SIZE        16384
#define NUMTRIES    15

float A[SIZE];
float B[SIZE];
float C[SIZE];

int main(){
    #ifndef _OPENMP
            fprintf( stderr, "OpenMP is not supported here -- sorry.\n" );
            return 1;
    #endif

	// inialize the arrays:
	for( int i = 0; i < SIZE; i++ )
	{
		A[i] = 1.;
		B[i] = 2.;
	}

    //Single Thread
    omp_set_num_threads( NUMT1 );
    fprintf( stderr, "Using %d threads\n", NUMT1 );

    double maxMegaMults = 0.;
    double sumFlops = 0;

    for( int t = 0; t < NUMTRIES; t++ )
    {
            double time0 = omp_get_wtime( );

            #pragma omp parallel for
            for( int i = 0; i < SIZE; i++ )
            {
                    C[i] = A[i] * B[i];
            }

            double time1 = omp_get_wtime( );
            double megaMults = (double)SIZE/(time1-time0)/1000000.;
            sumFlops += megaMults;
            if( megaMults > maxMegaMults )
                    maxMegaMults = megaMults;
    }

    printf( "Peak Performance = %8.2lf MegaMults/Sec\n", maxMegaMults );
    printf( "Average Performance = %8.2lf MegaMults/Sec\n", sumFlops/(double)NUMTRIES);

    //Four Threads
    omp_set_num_threads( NUMT4 );
    fprintf( stderr, "Using %d threads\n", NUMT4 );

    double maxMegaMults2 = 0.;
    double sumFlops2 = 0;

    for( int t = 0; t < NUMTRIES; t++ )
    {
            double time2 = omp_get_wtime( );

            #pragma omp parallel for
            for( int i = 0; i < SIZE; i++ )
            {
                    C[i] = A[i] * B[i];
            }

            double time3 = omp_get_wtime( );
            double megaMults2 = (double)SIZE/(time3-time2)/1000000.;
            sumFlops2 += megaMults2;
            if( megaMults2 > maxMegaMults2 )
                    maxMegaMults2 = megaMults2;
    }

    printf( "Peak Performance = %8.2lf MegaMults/Sec\n", maxMegaMults2 );
    printf( "Average Performance = %8.2lf MegaMults/Sec\n", sumFlops2/(double)NUMTRIES);

    //Speedup
    double speedup = maxMegaMults2/maxMegaMults;
    printf("Speedup is %f from 1 to 4 threads\n", speedup);

    //Parallel Fraction
    float Fp = (4./3.)*( 1. - (1./speedup) );
    printf("Parallel fraction is %f\n", Fp);

    return 0;
}