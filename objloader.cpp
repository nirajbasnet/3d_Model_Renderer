#include "objloader.hpp"

bool loadOBJ(
	const char * path, 
	std::vector<vec3> & out_vertices, 
	std::vector<unsigned int> & out_indices)
{
	//printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices;
	std::vector<vec3> temp_vertices;
	vec4 temp;

	
	FILE * file = fopen(path, "r");
	if( file == NULL ){
		//printf("Impossible to open the file ! Are you in the right path ?\n");
		getchar();
		return false;
		
	}

	while( 1 ){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "f") == 0){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3];
			fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
			vertexIndices.push_back(vertexIndex[0]-1);
			vertexIndices.push_back(vertexIndex[1]-1);
			vertexIndices.push_back(vertexIndex[2]-1);
		}

	}
out_vertices = temp_vertices;
out_indices = vertexIndices;

	return true;
}



