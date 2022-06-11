#version 330 compatibility

uniform sampler3D	Noise3;
uniform float 		uNoiseAmp;
uniform float 		uNoiseFreq;
uniform vec4		uColor;
uniform vec4		uSpecularColor;
uniform	float		uKa, uKd, uKs, uKr;
uniform samplerCube uReflectUnit;

in vec3	vNs;
in vec3	vNf;
in vec3	vEs;
in vec3	vEf;
in vec3	vLs;
in vec3	vLf;
in vec3	vMC;

const vec4  WHITE = vec4( 1.,1.,1.,1. );

vec3
RotateNormal( float angx, float angy, vec3 n )
{
	float cx = cos( angx );
	float sx = sin( angx );
	float cy = cos( angy );
	float sy = sin( angy );
	
	// rotate about x:
	float yp =  n.y*cx - n.z*sx;	// y'
	n.z      =  n.y*sx + n.z*cx;	// z'
	n.y      =  yp;
	// n.x      =  n.x;

	// rotate about y:
	float xp =  n.x*cy + n.z*sy;	// x'
	n.z      = -n.x*sy + n.z*cy;	// z'
	n.x      =  xp;
	// n.y      =  n.y;

	return normalize( n );
}


void
main( )
{
	vec4 nvx = texture( Noise3, uNoiseFreq*vMC );
	vec4 nvy = texture( Noise3, uNoiseFreq*vec3(vMC.xy,vMC.z+0.5) );

	float angx = nvx.r + nvx.g + nvx.b + nvx.a;
	angx = angx - 2.;
	angx *= uNoiseAmp;

	float angy = nvy.r + nvy.g + nvy.b + nvy.a;
	angy = angy - 2.;
	angy *= uNoiseAmp;

	vec3 Normal = RotateNormal( cos(angx), cos(angy), vNs );
	vec3 Light = normalize(vLs);
	vec3 Eye = normalize(vEs);

	vec4 ambient = uKa * uColor;

	float d = max( dot(Normal,Light), 0. );
	vec4 diffuse = uKd * d * uColor;

	float s = 0.;
	vec3 ref = normalize( reflect( -Light, Normal ) );
	if( dot(Normal,Light) > 0. )
	{
		s = pow( max( dot(Eye,ref),0. ), 10 );
	}

	vec4 specular = uKs * s * uSpecularColor;
	vec3 reflcolor = textureCube( uReflectUnit, ref ).rgb;
	gl_FragColor = vec4( ambient.rgb + diffuse.rgb + specular.rgb + uKr*reflcolor.rgb, 1. );
}