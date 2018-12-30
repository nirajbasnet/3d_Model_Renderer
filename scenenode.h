#ifndef SCENENODE_H
#define SCENENODE_H

#include<vector>
#include<algorithm>
#include "objloader.hpp"
#include "matrix.h"
#include "Vertexshader.h"
class Scenenode
{
protected:
	Scenenode *parent;
	VertexBuffer nodeobject;
	Matrix worldtransform;
	Matrix localtransform;
	Matrix rotation;
	Matrix translation;
	Matrix modelscale;
	std::vector<Scenenode*>children;
	

public:
	Scenenode();
	~Scenenode();
	int *meshindicator;              //indicates whether a scene node has model assosciated with it or not
	   
	void setRotation(float angle,vec3 axis )
	{
		rotation *= rotation.Rotate(angle,axis);
	}
	void setTranslate(vec3 displacement)
	{
		translation += translation.Translate(displacement);
	}
	void setlocaltransform(Matrix m) {localtransform = m;}
	void calculatelocaltransform()
	{
		localtransform = translation*rotation*modelscale;
	}
    Matrix getlocaltransform()
	{ return localtransform; }
	Matrix getworldtransform()
	{ return worldtransform; }
	void setModelscale(vec3 sc)
	{
		modelscale = modelscale.Scale(sc);
	}

    void Addchild(Scenenode *s);
    virtual void Update(float deltatime);
    void Draw(Vertexshader &shadervertex);
	std::vector<Scenenode *>::const_iterator getchilditeratorstart()
	{
		return children.begin();
	}
	std::vector<Scenenode *>::const_iterator getchilditeratorend()
	{
		return children.end();
	}
	void SetOBJfile(const char *path);
};




#endif
