
#ifndef VECTOR_H_
#define VECTOR_H_

#include <cmath>

class vec3
{
public:
    float x,y,z;
    vec3(void);
	vec3(float x, float y, float z);
    vec3 operator +(vec3);
    vec3 operator -(vec3);
	void operator +=(vec3);
	void operator -=(vec3);
	vec3 operator *(vec3);
    vec3 operator *(float);
    vec3 operator /(float);
    float Length();
    vec3 Normalise();
    void Invert();
    static float dot(vec3,vec3);
    static vec3 cross(vec3,vec3);
	void toInt(void){x=(int)x; y=(int)y; z=z;}

    inline bool	operator==( vec3 A) {return (A.x == x && A.y == y && A.z == z) ? true : false;};
	inline bool	operator!=( vec3 A) {return (A.x == x && A.y == y && A.z == z) ? false : true;};
	
};


class vec4	{
public:
    float x;
	float y;
	float z;
	float w;


	vec4(void) {
		x = y = z=0;
		w = 1.0f;
	}
	vec4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;

	}
    vec4(vec3 a, float w) {
        this->x = a.x;
		this->y = a.y;
		this->z = a.z;
		this->w = w;
    }
	vec3 xyz(void)
	{
		return vec3(this->x, this->y, this->z);
	}
	
	
};
/***********************************************************************************************************************/

#endif
