#include "scenenode.h"
Scenenode::Scenenode()
{
	parent = NULL;
	meshindicator = NULL;
    modelscale.LoadIdentityMatrix();
	translation.LoadIdentityMatrix();
    rotation.LoadIdentityMatrix();
	localtransform.LoadIdentityMatrix();
	worldtransform.LoadIdentityMatrix();
}
Scenenode::~Scenenode()
{
	for (int i = 0; i < children.size(); ++i)
	{
		delete children[i];
	}
}

void Scenenode::Addchild(Scenenode *s)
{
	//std::cout << "child added" << std::endl;
	children.push_back(s);
	s->parent = this;
}
void Scenenode::Update(float deltatime)
{
	//std::cout << "scenenode update initiated" << std::endl;
	if (parent)
	{
		worldtransform = parent->worldtransform*localtransform;
	}
	else{
		worldtransform = localtransform;
	}
	for (std::vector<Scenenode *>::iterator i = children.begin(); i != children.end(); ++i)
	{
		(*i)->Update(deltatime);
	}
}
void Scenenode::SetOBJfile(const char *path)
{
    std::vector <vec3> myvertices;
	std::vector<unsigned int > myindices;
	if (loadOBJ(path, myvertices, myindices))
	{
		nodeobject.BufferData(myvertices, myindices);
	}
	meshindicator = new int[0];
	meshindicator[0] = 1;
}
void Scenenode::Draw(Vertexshader &shadervertex)
{
	shadervertex.LinkVertexBuffer(this->nodeobject);
	shadervertex.RenderToScreen();
}
