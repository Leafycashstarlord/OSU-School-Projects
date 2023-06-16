glm::vec3
WhatPartOfALivesInBDir( glm::vec3 a, glm::vec3 b )
{
	return (glm::normalize(b) * glm::dot(a, glm::normalize(b)));
}


glm::vec3
WhatPartOfALivesPerpToB( glm::vec3 a, glm::vec3 b )
{
	return a - (glm::normalize(b) * glm::dot(a, glm::normalize(b)));
}


glm::vec3
UnitSurfaceNormal( glm::vec3 q, glm::vec3 r, glm::vec3 s )
{
	 return glm::normalize(glm::cross((r-q),(s-q)));
}


float
Area( glm::vec3 q, glm::vec3 r, glm::vec3 s )
{
	 return 0.5 * glm::length(glm::cross((r-q),(s-q)));
}


bool
IsPointInTriangle( glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p )
{
	glm::vec3 n = cross((r-q),(s-q));
	glm::vec3 nq = cross((r-q),(p-q));
	glm::vec3 nr = cross((s-r),(p-r));
	glm::vec3 ns = cross((q-s),(p-s));
	if (dot(n,nq) > 0 && dot(n,nr) > 0 && dot(n,ns) > 0){
		return true;
	}else{
		return false;
	} 
}



float
DistanceFromPointToPlane( glm::vec3 q, glm::vec3 r, glm::vec3 s, glm::vec3 p )
{
	return glm::dot((p - q), UnitSurfaceNormal(q, r, s));
}


void
WhoAmI( std::string &yourName, std::string &yourEmailAddress )
{
	yourName = "Jackson Rollins";
	yourEmailAddress = "rollijac@oregonstate.edu" ;
}
