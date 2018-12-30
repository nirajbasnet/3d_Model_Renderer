#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <stdio.h>
#include <string>
#include <cstring>
#include "Vector.h"

bool loadOBJ(
	const char * path, 
	std::vector<vec3> & out_vertices, 
	std::vector<unsigned int> & out_indices
);


#endif