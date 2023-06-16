#include <stdio.h>
#include <string>
#define _USE_MATH_DEFINES
#include <cmath>

#define GLM_FORCE_RADIANS
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

glm::mat4
Multiply( glm::mat4 a, glm::mat4 b )
{
	return a*b;
}



glm::vec3
Multiply( glm::mat4 a, glm::vec3 b )
{
	glm::vec4 c = glm::vec4(b, 1);
	glm::vec4 final = a*c;
	return glm::vec3(final);
}



glm::vec3
ScalePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::vec3 scale )
{
	glm::mat4 identity = glm::mat4( 1. );
	glm::mat4 scaleMatrixByItself = glm::scale( identity, scale );
	glm::vec3 relativePoint = inputPoint-centerPoint;
	glm::vec3 final = Multiply(scaleMatrixByItself, relativePoint);
	return final+centerPoint;
}



glm::vec3
RotatePointAroundAnotherPoint( glm::vec3 inputPoint, glm::vec3 centerPoint, glm::mat4 first, glm::mat4 second, glm::mat4 third )
{
	glm::vec3 relativePoint = inputPoint-centerPoint;
	glm::mat4 result = Multiply(third, second);
	result *= first;
	glm::vec3 final = Multiply(result, relativePoint);
	return final+centerPoint;
}


void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
	yourName = "Jackson Rollins";
	yourEmailAddress = "rollijac@oregonstate.edu" ;
}


void
PrintMatrix( glm::mat4 mat )
{
	for( int row = 0; row < 4; row++ )
	{
		fprintf( stderr, "  %7.2f %7.2f %7.2f %7.2f\n", mat[row][0], mat[row][1], mat[row][2], mat[row][3] );
	}
}
