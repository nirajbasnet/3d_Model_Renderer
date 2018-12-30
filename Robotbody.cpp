#include "Robotbody.h"

Robotframe::Robotframe()
{
	//std::cout << "Robotframe constructor called" << std::endl;
	Bodynode = new Scenenode();
	Bodynode->SetOBJfile("bodyframe.obj");
	Bodynode->setModelscale(vec3(1, 1, 1));
	Bodynode->setTranslate(vec3(0.0, 0.0, 0.0));
	Bodynode->calculatelocaltransform();
	Addchild(Bodynode);

    Headnode= new Scenenode();
	Headnode->SetOBJfile("head.obj");
	Headnode->setModelscale(vec3(1, 1, 1));
	Headnode->setTranslate(vec3(0, 0, 0));
	Headnode->calculatelocaltransform();
	Bodynode->Addchild(Headnode);

	Rightarm_upper = new Scenenode();
	Rightarm_upper->SetOBJfile("rightarmupper.obj");
	Rightarm_upper->setModelscale(vec3(1, 1, 1));
	Rightarm_upper->setTranslate(vec3(0, 0, 0));
	Rightarm_upper->calculatelocaltransform();
	Bodynode->Addchild(Rightarm_upper);

	Rightarm_lower = new Scenenode();
	Rightarm_lower->SetOBJfile("rightarmlower.obj");
	Rightarm_lower->setModelscale(vec3(1, 1, 1));
	Rightarm_lower->setTranslate(vec3(0, 0, 0));
	Rightarm_lower->calculatelocaltransform();
	Rightarm_upper->Addchild(Rightarm_lower);

	Leftarm_upper = new Scenenode();
	Leftarm_upper->SetOBJfile("leftarmupper.obj");
	Leftarm_upper->setModelscale(vec3(1, 1, 1));
	Leftarm_upper->setTranslate(vec3(0, 0, 0));
	Leftarm_upper->calculatelocaltransform();
	Bodynode->Addchild(Leftarm_upper);

	Leftarm_lower = new Scenenode();
	Leftarm_lower->SetOBJfile("leftarmlower.obj");
	Leftarm_lower->setModelscale(vec3(1, 1, 1));
	Leftarm_lower->setTranslate(vec3(0, 0,0));
	Leftarm_lower->calculatelocaltransform();
	Leftarm_upper->Addchild(Leftarm_lower);

	Rightleg_upper = new Scenenode();
	Rightleg_upper->SetOBJfile("rightlegupper.obj");
	Rightleg_upper->setModelscale(vec3(1, 1, 1));
	Rightleg_upper->setTranslate(vec3(0, 0, 0));
	Rightleg_upper->calculatelocaltransform();
	Bodynode->Addchild(Rightleg_upper);

	Rightleg_lower = new Scenenode();
	Rightleg_lower->SetOBJfile("rightleglower.obj");
	Rightleg_lower->setModelscale(vec3(1, 1, 1));
	Rightleg_lower->setTranslate(vec3(0, 0, 0));
	Rightleg_lower->calculatelocaltransform();
	Rightleg_upper->Addchild(Rightleg_lower);

	Leftleg_upper = new Scenenode();
	Leftleg_upper->SetOBJfile("leftlegupper.obj");
	Leftleg_upper->setModelscale(vec3(1, 1, 1));
	Leftleg_upper->setTranslate(vec3(0, 0, 0));
	Leftleg_upper->calculatelocaltransform();
	Bodynode->Addchild(Leftleg_upper);

	Leftleg_lower = new Scenenode();
	Leftleg_lower->SetOBJfile("leftleglower.obj");
	Leftleg_lower->setModelscale(vec3(1, 1, 1));
	Leftleg_lower->setTranslate(vec3(0, 0, 0));
	Leftleg_lower->calculatelocaltransform();
	Leftleg_upper->Addchild(Leftleg_lower);
}

void Robotframe::Update(float deltatime)
{
	float speed = 10.0f;
	float cameraspeed = 15.0f;
	float degrees = speed*deltatime;

    Scenenode::Update(deltatime); //calling parent Scenenode class to apply changes to postion and orientation of model

}
