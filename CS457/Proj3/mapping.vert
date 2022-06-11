#version 330 compatibility

uniform float uLightX;
uniform float uLightY;
uniform float uLightZ;

uniform float uA;
uniform float uK;

vec3 eyeLightPosition = vec3( uLightX, uLightY, uLightZ );

out vec3 Ns;
out vec3 Nf;
out vec3 Ls;
out vec3 Lf;
out vec3 Ef;
out vec3 Es;
out vec3 vMC;

float
Sinc( float r, float k )
{
	if( r*k == 0. )
		return 1.;
	return sin(r*k) / (r*k);
}

float
DerivSinc( float r, float k )
{
	if( r*k == 0. )
		return 0;
	return ( r*k*cos(r*k) - sin(r*k) ) / ( r*k*r*k );
}

void
main( )
{
	vec4 newVertex = gl_Vertex;
	float r = sqrt( newVertex.x*newVertex.x + newVertex.y*newVertex.y );
		// more efficient: float r = length( newVertex.xy );
	newVertex.z = uA * Sinc( r, uK );

	float dzdr = uA * DerivSinc( r, uK );
	float drdx = newVertex.x / r;
	float drdy = newVertex.y / r;
	float dzdx = dzdr * drdx;
	float dzdy = dzdr * drdy;

	vec3 Tx = vec3(1., 0., dzdx );
	vec3 Ty = vec3(0., 1., dzdy );

	vec3 newNormal = normalize( cross( Tx, Ty ) );

	vec4 ECposition = gl_ModelViewMatrix * newVertex;

	Nf = normalize( gl_NormalMatrix * newNormal ); // surface normal vector
	Ns = Nf;

	Lf = eyeLightPosition - ECposition.xyz; // vector from the point
	Ls = Lf; // to the light position

	Ef = vec3( 0., 0., 0. ) - ECposition.xyz; // vector from the point
	Es = Ef ; // to the eye position 



	gl_Position = gl_ModelViewProjectionMatrix * newVertex;
}