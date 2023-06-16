

// *******************
// VERTEX BUFFER DATA:
// *******************

#ifdef DEFINITION
struct vertex
{
	glm::vec3	position;
	glm::vec3	normal;
	glm::vec3	color;
	glm::vec2	texCoord;
};
#endif

struct vertex VertexData[ ] =
{
	// triangle 0-1-3:
	// vertex #0:
	{
		{ -1., -1., -1. },
		{  0., -1.,  0. },
		{  0.,  0.,  0. },
		{  0.,  0. }
	},

	// vertex #1:
	{
		{  1., -1., -1. },
		{  0., -1.,  0. },
		{  1.,  0.,  0. },
		{  1.,  0. }
	},

	// vertex #3:
	{
		{  1., -1.,  1. },
		{  0., -1.,  0. },
		{  1.,  0.,  1. },
		{  1.,  1. }
	},

	// triangle 0-3-2:
	// vertex #0:
	{
		{ -1., -1., -1. },
		{  0., -1.,  0. },
		{  0.,  0.,  0. },
		{  0.,  0. }
	},

	// vertex #3:
	{
		{  1., -1.,  1. },
		{  0., -1.,  0. },
		{  1.,  0.,  1. },
		{  1.,  1. }
	},

	// vertex #2:
	{
		{ -1., -1.,  1. },
		{  0., -1.,  0. },
		{  0.,  0.,  1. },
		{  0.,  1. }
	},

	// triangle 0-1-4:
	// vertex #0:
	{
		{ -1., -1., -1. },
		{  0., -1.,  0. },
		{  0.,  0.,  0. },
		{  0.,  0. }
	},

	// vertex #1:
	{
		{  1., -1., -1. },
		{  0., -1.,  0. },
		{  1.,  0.,  0. },
		{  1.,  0. }
	},

	// vertex #4:
	{
		{  0.,  0.,  1. },
		{ -1.,  0.,  0. },
		{  0.,  1.,  0. },
		{  0., 1. }
	},

	// triangle 0-2-4:
	// vertex #0:
	{
		{ -1., -1., -1. },
		{  0., -1.,  0. },
		{  0.,  0.,  0. },
		{  0.,  0. }
	},

	// vertex #2:
	{
		{ -1., -1.,  1. },
		{  0., -1.,  0. },
		{  0.,  0.,  1. },
		{  0.,  1. }
	},

	// vertex #4:
	{
		{  0.,  0.,  1. },
		{ -1.,  0.,  0. },
		{  0.,  1.,  0. },
		{  0., 1. }
	},

	// triangle 1-3-4:
	// vertex #1:
	{
		{  1., -1., -1. },
		{  0., -1.,  0. },
		{  1.,  0.,  0. },
		{  1.,  0. }
	},

	// vertex #3:
	{
		{  1., -1.,  1. },
		{  0., -1.,  0. },
		{  1.,  0.,  1. },
		{  1.,  1. }
	},

	// vertex #4:
	{
		{  0.,  0.,  1. },
		{ -1.,  0.,  0. },
		{  0.,  1.,  0. },
		{  0., 1. }
	},

	// triangle 2-3-4:
	// vertex #2:
	{
		{ -1., -1.,  1. },
		{  0., -1.,  0. },
		{  0.,  0.,  1. },
		{  0.,  1. }
	},

	// vertex #3:
	{
		{  1., -1.,  1. },
		{  0., -1.,  0. },
		{  1.,  0.,  1. },
		{  1.,  1. }
	},

	// vertex #4:
	{
		{  0.,  0.,  1. },
		{ -1.,  0.,  0. },
		{  0.,  1.,  0. },
		{  0., 1. }
	},
};


struct vertex JustVertexData[ ] =
{
	// vertex #0:
	{
		{ -1., -1., -1. },
		{  0., -1.,  0. },
		{  0.,  0.,  0. },
		{  0.,  0. }
	},

	// vertex #1:
	{
		{  1., -1., -1. },
		{  0., -1.,  0. },
		{  1.,  0.,  0. },
		{  1.,  0. }
	},

	// vertex #2:
	{
		{ -1., -1.,  1. },
		{  0., -1.,  0. },
		{  0.,  0.,  1. },
		{  0.,  1. }
	},

	// vertex #3:
	{
		{  1., -1.,  1. },
		{  0., -1.,  0. },
		{  1.,  0.,  1. },
		{  1.,  1. }
	},

	// vertex #4:
	{
		{  0.,  0.,  1. },
		{ -1.,  0.,  0. },
		{  0.,  1.,  0. },
		{  0., 1. }
	},

};

int JustIndexData[ ] =
{
	0, 1, 3,
	0, 3, 2,
	0, 1, 4,
	0, 2, 4,
	1, 3, 4,
	2, 3, 4
};