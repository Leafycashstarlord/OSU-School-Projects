
#version 330 compatibility

in float vLightIntensity;
in vec2  vST;
in vec3 vMCposition;

uniform float uAd;
uniform float uBd;
uniform float uTol;
uniform float uNoiseAmp;
uniform float uNoiseFreq;
uniform float uAlpha;

uniform sampler3D Noise3;

void
main( )
{
	vec4 nv = texture3D( Noise3, uNoiseFreq*vMCposition);
	float n = nv.r + nv.g + nv.b + nv.a;
	n = n - 2.;
	n *= uNoiseAmp;

	float s = vST.s;
	float t = vST.t;
	float Ar = uAd/2.;
	float Br = uBd/2.;
	int numins = int ( vST.s / uAd );
	int numint = int ( vST.t / uBd );
	float sc = numins * uAd + Ar;
	float ds = s - sc;
	float tc = numint *uBd + Br;
	float dt = t - tc;

	float oldDist = sqrt(ds*ds + dt*dt);
	float newDist = oldDist + n;
	float scale = newDist/oldDist;

	ds *= scale;
	ds /= Ar;
	dt *= scale;
	dt /= Br;

	float ellipse = (ds*ds) + (dt*dt);
	float d = smoothstep( 1. - uTol, 1. + uTol, ellipse );

	gl_FragColor = vec4( vLightIntensity * mix( vec3(1.,0.,0.), vec3(0.,1.,0.) , d ), 1. );
}