#include "RobotRender.h"

RobotRender::RobotRender()
{
	rootRobot = new Scenenode();
	roboframe = new Robotframe();
	rootRobot->Addchild(roboframe);

	cameraposition=vec3(0,0,10);
	robocamera.setCamera(cameraposition, vec3(0, 0, 0));
	//robocamera.setView(cameraposition,0,0,0); 
	perspective.Perspective(60, 16.0 / 9.0, 0.1, 10.0);
	vertexshader.ApplyPerspectiveTransformation(perspective);
	vertexshader.setModelCamera(robocamera);

	setup_lighting();
	colorshader.setup_Viewport(0, 0, 1366, 768);
	colorshader.setup_Zbuffer(1366, 768);             
	
	vertexshader.LinkColorShader(colorshader);    //linking finalized color shader and vertex shader

}

RobotRender::~RobotRender()
{
	delete rootRobot;
	delete roboframe;
}
void RobotRender::setup_lighting()    //setting up light sources 
{
	centerlight.setambient(vec3(0, 0, 0));
	centerlight.setdiffuse(vec3(0, 0, 0));
	centerlight.setPosition(vec3(0, 0, 2));
	centerlight.setRadius(1.0);
	centerlight.setspecular(vec3(0, 0, 0), 30);
	colorshader.SetLightSource(centerlight);
}
void RobotRender::DrawNode(Scenenode *model)
{
	if (model->meshindicator)
	{
		//std::cout << "final drawing initiated" << std::endl;
		vertexshader.ApplyModelTransformation(model->getworldtransform());
		model->Draw(vertexshader);
	}
	for (std::vector<Scenenode*>::const_iterator i = model->getchilditeratorstart(); i != model->getchilditeratorend(); i++)
	{
		DrawNode(*i);
	}
}
void RobotRender::Updatescene(float deltatime)  //keyboard and mouse input for scene update purpose
{

	robocamera.SetPosition(cameraposition);   //update rotation of camera 
	//robocamera.RotateCamera(x,y);
	rootRobot->Update(deltatime);

}
void RobotRender::Renderscene()
{
	DrawNode(rootRobot);
}
