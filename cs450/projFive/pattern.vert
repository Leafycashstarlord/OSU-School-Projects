#version 330 compatibility

uniform float	vTime;		// "Time", from Animate( )
out vec2  	vST;		// texture coords

const float PI = 	3.14159265;
const float AMP = 	0.2;		// amplitude
const float W = 	2.;		// frequency

void
main( )
{ 
	vST = gl_MultiTexCoord0.st;
	vec3 vert = gl_Vertex.xyz;
	vert.x = gl_Vertex.x + sin(gl_Vertex.z*W + vTime) * AMP;
	vert.y = gl_Vertex.y + cos(gl_Vertex.x*W + vTime) * AMP;
	vert.z = gl_Vertex.z + sin(gl_Vertex.y*W*2 + vTime) * AMP;

	gl_Position = gl_ModelViewProjectionMatrix * vec4( vert, 1. );
}
