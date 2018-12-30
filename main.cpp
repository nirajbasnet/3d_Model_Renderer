
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Vector.h"
#include "objloader.hpp"
#include "VertexShader.h"



int main(void)
{
	char c;
	VertexBuffer servo;
	std::vector <vec3> myvertices;
	std::vector<unsigned int > myindices;
	if (loadOBJ("se.obj", myvertices, myindices))
	{
		servo.BufferData(myvertices, myindices);
    }
	servo.display();
	c = getchar();
	return 0;
}


