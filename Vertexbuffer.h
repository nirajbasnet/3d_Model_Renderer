#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <iostream>
#include <vector>
#include "matrix.h"
#include "Vector.h"

struct Triangle
{
	unsigned int index[3];
	vec4 position[3];
	vec3 color[3];
	vec3 normal[3];
	vec3 tr_normal;
	bool clipper_status;
};

class VertexBuffer
{
public:
	unsigned int num_vertices;
	unsigned int num_indices;
	std::vector<vec3> vertices;
	std::vector<unsigned int> indices;
	std::vector<Triangle> triangles;
	vec3 objcolor;
	vec3 *normals;


	VertexBuffer()
	{
		normals = NULL;
		num_vertices = 0;
		num_indices = 0;
	}

	void FormNormals();
	void FormTriangles();



	void BufferVertexdata(std::vector<vec3> tmpvertex)
	{
		vertices = tmpvertex;
		num_vertices = vertices.size();
	}
	void BufferIndicesdata(std::vector<unsigned int> tmpindices)
	{
		indices = tmpindices;
		num_indices = indices.size();
	}
	void BufferData(std::vector<vec3> tmpvertex, std::vector<unsigned int> tmpindices)
	{
		vertices = tmpvertex;
		num_vertices = vertices.size();
		indices = tmpindices;
		num_indices = indices.size();
		FormNormals();
		FormTriangles();
	}

	void BufferColordata(vec3 color)
	{
		objcolor = color;
	}

	void display()
	{
		//for (int i = 0; i < triangles.size(); i++)
		//for (int j = 0; j < 3; j++)
			//std::cout << "\n" << i + 1 << vertices[triangles[i].index[j]].x << "\t" << vertices[triangles[i].index[j]].y << "\t" << vertices[triangles[i].index[j]].z;
		//std::cout << "\n" << i + 1 << triangles[i].normal[j].x << "\t" << triangles[i].normal[j].y << "\t" << triangles[i].normal[j].z;
		//std::cout << "\n" << i + 1 << normals[triangles[i].index[j]].x << "\t" << normals[triangles[i].index[j]].y << "\t" << normals[triangles[i].index[j]].z;
	}


};


#endif