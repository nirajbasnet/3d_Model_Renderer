#ifndef ROBOTRENDER_H
#define ROBOTRENDER_H

#include "Robotbody.h"
#include "graphics.h"
#include "VertexShader.h"
#include "ColorShader.h"


class RobotRender
{
private:
	      Vertexshader vertexshader;
	      Colorshader colorshader;
		  Scenenode *rootRobot;
		  Camera robocamera;
		  Projection perspective;
		  Robotframe *roboframe;
		  Light centerlight;
		  vec3 cameraposition;

public:
	   RobotRender();
	   ~RobotRender();
	   void setup_lighting();
	   void DrawNode(Scenenode *model);
	   void Updatescene(float deltatime);
	   void Renderscene();



};


#endif