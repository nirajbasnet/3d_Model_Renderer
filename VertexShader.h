#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H
#include "graphics.h"
#include "Vertexbuffer.h"
#include "ColorShader.h"
#include "transformation.h"


class Vertexshader
{
public:    
	       Matrix Model;
		   Matrix View;
		   Matrix Perspective;
		   Matrix normal_rotation;
		   Projection ModelProject;
		   Camera ModelCamera;
		   VertexBuffer object;
		   Colorshader colorshader;

		  

		   void ApplyModelTransformation(Matrix Model){ this->Model = Model; }
		   void ApplyNormalRotation(Matrix rotation){this->normal_rotation=rotation;}
		   void ApplyViewTransformation(Matrix View) { this->View = View; }
		   void setModelCamera(Camera &Modcamera){ ModelCamera = Modcamera; View = ModelCamera.matrix; }
		   inline bool ApplyClipping(vec3 point, vec3 camerapos);
		   void ApplyPerspectiveTransformation(Projection &modelproject) { ModelProject = modelproject; }
		   void ApplyPerspectiveTransformation(Matrix perspective) { this->Perspective = perspective; }
		   void UpdateMVPmatrices();
		   void LinkVertexBuffer(VertexBuffer obj) { object = obj;}
		   void LinkColorShader(Colorshader &colorobject) { colorshader = colorobject; }
		   void RenderToScreen();
		   bool RunBackfaceCull(int tr_index);

};


#endif
