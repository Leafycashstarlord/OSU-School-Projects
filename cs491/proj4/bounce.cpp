#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <string>


#define _USE_MATH_DEFINES
#include <math.h>

const float RADIUS  = { 0.50f };
const float XLEFT   = { -5.f };
const float XRIGHT  = {  5.f };
const float YBOTTOM = { -3.f };

// flags to indicate which surface was hit:
// (these are #define'd so that they can be used in a switch statement)

#define NOTHING_HIT     -1
#define HIT_LEFT         0
#define HIT_RIGHT        1
#define HIT_FLOOR1       2
#define HIT_FLOOR2       3

// a tolerance to allow for floating-point roundoff problems:

const float EPSILON = { 0.001f };

const float TOL = { 0.1f };

extern float   CoefRest;
extern float   Gravity;
extern float   Vxnow, Vynow;
extern float   Xnow, Ynow;

void
Bounce( float dt )
{
	while( dt > EPSILON )
	{
		float tmin = dt;	// minimum time to do something
		int which = NOTHING_HIT; // which reason was it for doing the something

		// these four collision times are computed using your projectile motion equations:

		float tleft = (XLEFT + RADIUS - Xnow) / Vxnow;	// time to hit the left wall
		if( tleft > EPSILON  &&  tleft < tmin )
		{
			tmin = tleft;
			which = HIT_LEFT;
		}
		float tright = (XRIGHT - RADIUS - Xnow) / Vxnow;	// time to hit the right wall
		if( tright > EPSILON  &&  tright < tmin )
		{
			tmin = tright;
			which = HIT_RIGHT;
		}
		float tfloor1 = (-Vynow + sqrt((Vynow*Vynow) - ((2*Gravity)*(Ynow - YBOTTOM - RADIUS)))) / Gravity;	// time to hit the floor
		if( tfloor1 > EPSILON  &&  tfloor1 < tmin )
		{
			tmin = tfloor1;
			which = HIT_FLOOR1;
		}
		float tfloor2 = (-Vynow - sqrt((Vynow*Vynow) - ((2*Gravity)*(Ynow - YBOTTOM - RADIUS)))) / Gravity;	// time to hit the floor (note there are 2 answers)
		if( tfloor2 > EPSILON  &&  tfloor2 < tmin )
		{
			tmin = tfloor2;
			which = HIT_FLOOR2;
		}

		// tmin is now set to the smallest of:
		//	dt, tleft, tright, tfloor1, tfloor2
		// which are positive

		// which is set to:
		//	NOTHING_HIT, HIT_LEFT, HIT_RIGHT, HIT_FLOOR1, or HIT_FLOOR2
		// to show what was the first thing hit

		// take a time step of time length tmin, using the projectile motion equations:
		// if a bounce is going to occur, tmin takes the ball right up to the surface:

		// remember to make these a function of tmin, not dt!
		Xnow  = Xnow + Vxnow*tmin;
                Vxnow = Vxnow;
                Ynow  = Ynow + Vynow*tmin + 0.5*Gravity*tmin*tmin;
                Vynow = Vynow + Gravity*tmin;


		// a "bounce trick":

		if( Ynow < YBOTTOM+RADIUS )
			Ynow = YBOTTOM+RADIUS;		// floating point roundoff sometimes messes up

		if( Xnow < XLEFT+RADIUS )
			Xnow = XLEFT+RADIUS;

		if( Xnow > XRIGHT-RADIUS )
			Xnow = XRIGHT-RADIUS;


		// depending on what caused the bounce, change the proper velocity component:
		// if nothing was hit in this time step, just return:

		switch( which )
		{
			case NOTHING_HIT:
				return;

			case HIT_LEFT:
				Vxnow = -CoefRest * Vxnow;
				break;

			case HIT_RIGHT:
				Vxnow = -CoefRest * Vxnow;
				break;

			case HIT_FLOOR1:
				Vynow = -CoefRest * Vynow;
				break;

			case HIT_FLOOR2:
				Vynow = -CoefRest * Vynow;
				break;
		}

		dt -= tmin;	// after the bounce, we might still have some time step left
	}
}

void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
        yourName = "Jackson Rollins";
        yourEmailAddress = "rollijac@oregonstate.edu" ;
}