#include "Vector.h"

vec3::vec3(void)
    {
        x=y=z=0;
    }

vec3::vec3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

float vec3::Length()
{
return sqrt((x*x)+(y*y)+(z*z));
}
vec3 vec3::Normalise()
{
        float length = Length();
        if(length != 0.0f)	{
			length = 1.0f / length;
			x = x * length;
			y = y * length;
			z = z * length;
		}
		return(vec3(this->x,this->y, this->z));
}

void vec3::Invert()
 {
        x = -x;
		y = -y;
		z = -z;
 }
vec3 vec3:: operator +(vec3 a)
{
    return vec3(x + a.x,y + a.y, z + a.z);
}

vec3 vec3:: operator -(vec3 a)
{
   return vec3(x - a.x,y - a.y, z - a.z);
}
void vec3:: operator +=(vec3 a)
{
	x += a.x;
	y += a.y;
	z += a.z;
}

void vec3:: operator -=(vec3 a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
}

vec3 vec3:: operator *(float a)
{
    return vec3(x * a,y * a, z * a);
}
vec3 vec3::operator *(vec3 a)
{
	return(vec3(this->x*a.x, this->y*a.y, this->z*a.z));
}
vec3 vec3:: operator /(float a)
{
    return vec3(x / a,y / a, z / a);
}

 float vec3::dot(vec3 a, vec3 b)
{
    return ((a.x*b.x)+(a.y*b.y)+(a.z*b.z));
}

 vec3 vec3::cross(vec3 a, vec3 b)
{
    return vec3((a.y*b.z) - (a.z*b.y) , (a.z*b.x) - (a.x*b.z) , (a.x*b.y) - (a.y*b.x));
}

