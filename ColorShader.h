#ifndef COLORSHADER_H
#define COLORSHADER_H


#include "Common.h"
#include "lightclass.h"
#include "matrix.h"
#include <math.h>
#include "Vertexbuffer.h"

#define mat_specular 0.83

class Colorshader
{
private:
		unsigned int viewportx;
		unsigned int viewporty;
		unsigned int viewportwidth;
		unsigned int viewportheight;
        std::vector<Light> lightsource;
        vec3 cameraPos;
		//float **Z;       //For Z buffer
	    float Z[1366][768];

public:
       Colorshader()
        {
		    viewportx=0;
		    viewporty=0;
		    viewportwidth=1366;
		    viewportheight=768;
        }

        ~Colorshader()
        {
		   lightsource.clear();
        }
       void SetLightSource(Light &light)
        {
		   lightsource.push_back(light);
        }

	   void RunColorShader(VertexBuffer &colorobjet);
        void SetCameraposition(vec3 cameraPos){ this->cameraPos=cameraPos;}
		vec3 Calculate_Single_Lighting(int light_index, vec3 worldPos,vec3 normal, vec3 color);
        vec3 Compute_final_lighting(vec3 worldPos,vec3 normal,vec3 color);
		void UsePhongModel(VertexBuffer &coloroject);
		void UseGourardModel(VertexBuffer &coloobject);
        void setup_Zbuffer(const int winwidth,const int winheight);
		void setup_Viewport(unsigned int viewportx, unsigned int viewporty, unsigned int viewportwidth, unsigned int viewportheight);
	    bool Run_Zbuffer(int x,int y,float z);
	    Matrix viewport();
	    bool viewport(vec4 &ndc);
		void wireframe(vec3 v1, vec3 v2, vec3 v3);
		void fillLine(vec3 v1,vec3 v2,vec3 c1,vec3 c2);
        void fillTriangle(vec3, vec3, vec3, vec3 cl1, vec3 cl2, vec3 cl3);
        void fillBottomTriangle(vec3 v1,vec3 v2,vec3 v3, vec3 c1, vec3 c2, vec3 c3);
        void fillTopTriangle(vec3 v1,vec3 v2,vec3 v3 , vec3 c1, vec3 c2, vec3 c3);
		void fillflat( vec3 v1, vec3 v2, vec3 v3, vec3 c1, vec3 c2, vec3 c3);
};
#endif
