#version 330 compatibility

uniform samplerCube uRefractUnit;
uniform samplerCube uReflectUnit;
uniform sampler2D uNormalTex;
uniform sampler2D uColorTex;
uniform float uMix;
uniform float uWhiteMix;
const vec4  WHITE = vec4( 1.,1.,1.,1. );

uniform float uPower;
uniform float uRtheta;
const float PI = 3.141592653589793238462643383;

in vec3	vNs;
in vec3	vNf;
in vec3	vEs;
in vec3	vEf;
in vec3	vLs;
in vec3	vLf;
in vec3	vMC;
in vec2 vST;

float
atan2( float y, float x )
{
        if( x == 0. )
        {
                if( y >= 0. )
                        return  PI/2.;
                else
                        return -PI/2.;
        }
        return atan(y,x);
}

void
main( )
{
	float refin;

	vec3 Normal;
	vec3 Light;
	vec3 Eye;
	
	vec2 sT = vST - vec2(0.5,0.5);  // put (0,0) in the middle so that the range is -0.5 to +0.5
	float rad = length(sT);
	float radius = pow((2*rad), uPower);

	float angle  = atan2( sT.y, sT.x );
	float ang = angle - uRtheta * radius;

	sT = radius * vec2( cos(ang),sin(ang) );  	// now in the range -1. to +1.
	sT += 1;                       		// change the range to 0. to +2.
	sT *= 0.5; 		       				// change the range to 0. to +1.

	Normal = normalize ((texture2D(uNormalTex,sT.st).xyz*2.0 - 1.0));
	Light = normalize(vLs);
	Eye = normalize(vEs);
	 if ( texture2D(uColorTex,sT.st).b > .99){
		discard; 
	 }
    vec3 vRefractVector = refract( Eye, Normal, 0 );
	vec3 vReflectVector = reflect( Eye, Normal );

    vec4 reflectcolor = textureCube( uReflectUnit, vReflectVector );
	vec4 refractcolor;
	if( all( equal( vRefractVector, vec3(0.,0.,0.) ) ) )
	{
		refractcolor = reflectcolor;
	}
	else
	{
		refractcolor = textureCube( uRefractUnit, vRefractVector );
		refractcolor = mix( refractcolor, WHITE, uWhiteMix );
	}
    gl_FragColor = mix(refractcolor, reflectcolor, uMix);
}