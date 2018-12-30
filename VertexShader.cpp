#include "VertexShader.h"


  inline bool Vertexshader::ApplyClipping(vec3 point, vec3 camerapos)
  {
	  vec3 v = point - camerapos;

	  float xcomp = vec3::dot(v, vec3(1, 0, 0));
	  float ycomp = vec3::dot(v, vec3(0, 1, 0));
	  float zcomp = vec3::dot(v, vec3(0, 0, 1));
	  float h = zcomp * 2;       //h=zcomp*2*tan(fov/2)  in this case assuming fov=90
	  float width = h*1.77778;
	  if (zcomp<ModelProject.N || zcomp>ModelProject.F)
		  return false;

	  if (ycomp<(-h / 2) || ycomp>(h / 2))
		  return false;

	  if (xcomp<(width / 2) || xcomp>(width / 2))
		  return false;

	  return true;
  }
  
 
  void Vertexshader::UpdateMVPmatrices()
  {
	  int clip_status = 0;
	  int removedindex = 0;
	  /************************************************************************************************************************/
	  for (int i = 0; i < object.triangles.size(); i++)
	  {
		  for (int j = 0; j < 3; j++)
		  {
			  object.triangles[i].position[j] = View * (Model * vec4(object.vertices[object.triangles[i].index[j]], 1.0));
			  object.triangles[i].tr_normal=(normal_rotation*vec4(object.triangles[i].tr_normal,1.0)).xyz();
			 // if (ApplyClipping(object.triangles[i].position[j].xyz(), ModelCamera.getCameraPosition()))
				 // clip_status++;
          }
		  if (clip_status == 3)
		  {
			  //object.triangles.erase(object.triangles.begin() + i-removedindex);
			  clip_status = 0;
			  removedindex++;
		  }
      }
	  /*
	VertexBuffer temp;
	  int num_triangle = object.triangles.size();
	  for (int i = 0; i < num_triangle; i++)
	  {
		  if (RunBackfaceCull(i))
		  {
			  //object.triangles.erase(object.triangles.begin() + i - removedindex);
			  temp.triangles.push_back(object.triangles[i]);
			  removedindex++;
		  }
	  }
	  object.triangles.clear();
	  object.triangles = temp.triangles;
	  */
	 
       colorshader.SetCameraposition(ModelCamera.getCameraPosition());
	   colorshader.UseGourardModel(object);
	  
	  /*PERSPECTIVE PROJECTION*******************************************************************************************************/
	  for (int i = 0; i < object.triangles.size(); i++)
	  {
		  for (int j = 0; j < 3; j++)
		  {
			  object.triangles[i].position[j] = ModelProject.matrix* object.triangles[i].position[j];
			  object.triangles[i].position[j].x = object.triangles[i].position[j].x/object.triangles[i].position[j].w;
			  object.triangles[i].position[j].y = object.triangles[i].position[j].y/object.triangles[i].position[j].w;
			  object.triangles[i].position[j].z = object.triangles[i].position[j].z/object.triangles[i].position[j].w;
			  object.triangles[i].position[j].w = object.triangles[i].position[j].w/object.triangles[i].position[j].w;
		  }
	  }
	  
	  /*****************************************************************************************************************************/
  }

  void Vertexshader::RenderToScreen()
  {
	  UpdateMVPmatrices();
	  
	  colorshader.RunColorShader(object);
  }

  bool Vertexshader::RunBackfaceCull(int tr_index)
  {
	  float angle;
	  vec3 viewdir;
	  viewdir=(object.triangles[tr_index].position[0].xyz()-ModelCamera.getCameraPosition()).Normalise();
	  angle=vec3::dot(viewdir,object.triangles[tr_index].tr_normal);
	  if(angle<0)
		  return true;
	  else
	  return false;
  }