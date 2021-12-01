#version 330 compatibility

uniform float	fTime;		// "Time", from Animate( )
in vec2  	vST;		// texture coords
float	uSize = 0.2;
float	uS0 = .5;
float	uT0 = .5;
float radius = uSize;
float ds = vST.s - uS0;
float dt = vST.t - uT0;

void
main( )
{
	vec3 myColor = vec3(1, 0, 0 );
	if( ((ds*ds*fTime) + (dt*dt*fTime)) <= (radius*radius))
	{
		myColor = vec3( 0, 0, 1 );
	}
	gl_FragColor = vec4( myColor,  1. );
}
