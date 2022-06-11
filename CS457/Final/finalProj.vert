#version 330 compatibility

vec3 eyeLightPosition = vec3(10, 10, 20);

out vec3 vNs;
out vec3 vNf;
out vec3 vEs;
out vec3 vEf;
out vec3 vLs;
out vec3 vLf;
out vec3 vMC;
out vec2 vST;

void
main( )
{
	vST = gl_MultiTexCoord0.st;    
	vec4 ECposition = gl_ModelViewMatrix * gl_Vertex;

	vNf = normalize(gl_NormalMatrix*gl_Normal);
	vNs = vNf;

	vLf = eyeLightPosition - ECposition.xyz;
	vLs = vLf;

	vEf = vec3( 0., 0., 0. ) - ECposition.xyz; 
	vEs = vEf;

	vMC = gl_Vertex.xyz;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}