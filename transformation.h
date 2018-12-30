#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "matrix.h"
class Projection
{

public:
	Matrix matrix;
	float N,F;
	Projection( void )
	{
		N=0.1;
		F=100;}
	void Frustum( float left, float right, float bottom, float top, float near, float far );
	void Perspective( float fovy, float aspect, float near, float far );
	void Ortho( float left, float right, float bottom, float top, float near, float far );
	void LoadIdentityMatrix( void );
	
	
};



class Camera
{
private:
	vec3 camPosition;
	float Pitch;
	float Heading;
	float Roll;
	int mouseX;
	int mouseY;
	vec3 forward;
	
public:
	Matrix matrix;
    Camera() :mouseX(0), mouseY(0){}
	Camera(vec3 pos, float pitch, float heading, float roll) :mouseX(0), mouseY(0){ setView(pos, pitch, heading, roll); }
	void setCamera(vec3 pos, vec3 target);
	void SetPosition(vec3 campos){this->camPosition=campos;}
    void setCameraRotateX(float pitch){ this->Pitch = pitch; this->upateViewMatrix(); }
	void setCameraRotateY(float heading){ this->Heading = heading; this->upateViewMatrix(); }
	void setCameraRotateZ(float roll){ this->Roll = roll; this->upateViewMatrix(); }
    float getCameraAngleX(void){ return this->Pitch; }
	float getCameraAngleY(void){ return this->Heading; }
	float getCameraAngleZ(void){ return this->Roll; }
	vec3 getCameraPosition(){return camPosition;}
	void setView( vec3 pos, float pitch, float heading, float roll );
	void upateViewMatrix( void );
	void RotateCamera( int x, int y );
	void ZoomCamera( float distance );
};

#endif