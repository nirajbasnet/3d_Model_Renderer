#include "Vertexbuffer.h"

void VertexBuffer::FormNormals()
{
	normals = new vec3[num_vertices];
	if (num_indices) { // Generate per - vertex normals
		for (int i = 0; i < num_indices; i += 3)
		{
			unsigned int a = indices[i];
			unsigned int b = indices[i + 1];
			unsigned int c = indices[i + 2];

			vec3 normal = vec3::cross((vertices[b] - vertices[a]), (vertices[c] - vertices[a]));

			normals[a] += normal;
			normals[b] += normal;
			normals[c] += normal;
		}
	}
	else {
		for (int i = 0; i < num_vertices; i += 3){
			vec3  a = vertices[i];
			vec3  b = vertices[i + 1];
			vec3  c = vertices[i + 2];

			vec3 normal = vec3::cross(b - a, c - a);

			normals[i] += normal;
			normals[i + 1] += normal;
			normals[i + 2] += normal;
		}
	}
	for (int i = 0; i<num_vertices; i++)
	{
		normals[i].Normalise();
	}
}
void VertexBuffer::FormTriangles()
{
	Triangle temp;
	for (int i = 0; i<num_indices; i = i + 3)
	{
		temp.index[0] = indices[i];
		temp.index[1] = indices[i + 1];
		temp.index[2] = indices[i + 2];
		temp.normal[0] = normals[indices[i]];
		temp.normal[1] = normals[indices[i+1]];
		temp.normal[2] = normals[indices[i+2]];
		temp.color[0] = vec3(1,0,0);
			temp.color[1] =vec3(1,0,0);
			temp.color[2] = vec3(1,0,0);
		temp.tr_normal=(temp.normal[0]+temp.normal[1]+temp.normal[2])/3.0;
		triangles.push_back(temp);
	}
}