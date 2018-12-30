#ifndef LIGHTCLASS_H
#define LIGHTCLASS_H

#include "Vector.h"
class Light
{
private:
    vec3 position;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emit;
    float radius;
    int specularpower;

public:
	    Light()
		{
			position = vec3(0, 0, 0);      //light source at origin
			radius = 1;                    //unit distance coverage of light source
			color = vec3(255, 255, 255);   //white color light
		}
       Light(vec3 position,vec3 color,float radius)
       {
           this->position=position;
           this->color=color;
           this->radius=radius;
       }
       void setPosition(vec3 pos){position=pos;}
       vec3 getPosition() {return position;}
       void setambient(vec3 ambient ){this->ambient=ambient;}
       void setdiffuse(vec3 diffuse){this->diffuse=diffuse;}
       void setspecular(vec3 specular,int spconstant){ this->specular=specular; specularpower=spconstant;}
       void setemit(vec3 emit){this->emit=emit;}
       void setRadius(float radius){this->radius=radius;}

       vec3 get_ambient(){return ambient;}
       vec3 get_diffuse(){return diffuse;}
       vec3 get_specular(){return specular;}
       int get_Spower(){return specularpower;}
       float getRadius(){return radius;}


};
#endif // LIGHTCLASS_H
