#include "transformation.h"
#include  <math.h>
#define pi 3.14159265f


//***************************************************************************************************************************************//
void Projection::LoadIdentityMatrix( void )
{
	matrix.LoadIdentityMatrix();
}

void Projection::Ortho( float Left, float Right, float Bottom, float Top, float Near, float Far )
{
	N=Near;
	F=Far;
	matrix.LoadIdentityMatrix( );
	matrix[0][0]=2.0f/( Right-Left );
	matrix[1][1]=2.0f/( Top-Bottom );
	matrix[2][2]=2.0f/( Near-Far );
	matrix[0][3]=( Right+Left )/( Left- Right );
	matrix[1][3]=( Top+Bottom )/( Bottom-Top );
	matrix[2][3]=( Far+Near )/( Near-Far );
	matrix[1][0]=matrix[2][0]=matrix[3][0]=matrix[0][1]=matrix[2][1]=matrix[3][1]=matrix[0][2]=matrix[1][2]=matrix[3][2]=0.0f;
	matrix[3][3]=1.0f;
}

void Projection::Frustum( float Left, float Right, float Bottom, float Top, float Near, float Far )
{
	matrix.LoadIdentityMatrix( );
	matrix.M[0][0]=2.0f*Near/( Right-Left );
	matrix.M[0][2]=( Right+Left )/(Right-Left );
	matrix.M[1][1]=2.0f*Near/( Top-Bottom );
	matrix.M[1][2]=( Top+Bottom )/( Top-Bottom );
	matrix.M[2][2]=( Far+Near )/( Near-Far );
	matrix.M[2][3]=2.0f*Far*Near/( Near-Far );
	matrix.M[1][0]=matrix.M[2][0]=matrix.M[3][0]=matrix.M[0][1]=matrix.M[2][1]=matrix.M[3][1]=matrix.M[0][3]=matrix.M[1][3]=matrix.M[3][3]=0.0f;
	matrix.M[3][2]=-1.0f;

}

void Projection::Perspective( float fovy, float aspect, float Near, float Far )
{
	N=Near;
	F=Far;
	matrix.LoadIdentityMatrix( );
	float tangent=tanf( ( fovy/2.0f )*pi/180.0f );
	float height = Near * tangent;           // half height of near plane
    float width = height * aspect;
	Frustum( -width, width, -height, height, Near , Far );
}

void Camera::setCamera(vec3 pos, vec3 target)
{
	float forward[4];
    float up[4];
    float left[4];
    float position[4];
    float invLength;

    // determine forward vector (direction reversed because it is camera)
    forward[0] = pos.x - target.x;    // x
    forward[1] = pos.y - target.y;    // y
    forward[2] = pos.z - target.z;    // z
    forward[3] = 0.0f;              // w
    // normalize it without w-component
    invLength = 1.0f / sqrtf(forward[0]*forward[0] + forward[1]*forward[1] + forward[2]*forward[2]);
    forward[0] *= invLength;
    forward[1] *= invLength;
    forward[2] *= invLength;

    // assume up direction is straight up
    up[0] = 0.0f;   // x
    up[1] = 1.0f;   // y
    up[2] = 0.0f;   // z
    up[3] = 0.0f;   // w

    // compute left vector with cross product
    left[0] = up[1]*forward[2] - up[2]*forward[1];  // x
    left[1] = up[2]*forward[0] - up[0]*forward[2];  // y
    left[2] = up[0]*forward[1] - up[1]*forward[0];  // z
    left[3] = 1.0f;                                 // w

    // re-compute orthogonal up vector
    up[0] = forward[1]*left[2] - forward[2]*left[1];    // x
    up[1] = forward[2]*left[0] - forward[0]*left[2];    // y
    up[2] = forward[0]*left[1] - forward[1]*left[0];    // z
    up[3] = 0.0f;                                       // w

    // camera position
    position[0] = -pos.x;
    position[1] = -pos.y;
    position[2] = -pos.z;
    position[3] = 1.0f;

	matrix.LoadIdentityMatrix();
	matrix.setcolumn( 0, left );
	matrix.setcolumn( 1, up );
	matrix.setcolumn( 2, forward );
	matrix.setcolumn( 3, position );

}

void Camera::setView( vec3 pos, float pitch, float heading, float roll )
{
	camPosition = pos;
	this->Pitch=pitch;
	this->Heading=heading;
	this->Roll=roll;
	this->upateViewMatrix();
}

void Camera::upateViewMatrix( void )
{
	matrix.LoadIdentityMatrix( );
	matrix *=matrix.Translate(-this->camPosition.x, -this->camPosition.y, -this->camPosition.z);
	matrix *=matrix.Rotate( -this->Pitch, 'x' );
	matrix *= matrix.Rotate(-this->Heading, 'y');
	matrix *= matrix.Rotate(-this->Roll, 'z');
}

void Camera::RotateCamera( int x, int y )
{
	this->Pitch+=( y-this->mouseY );
	this->Heading+=( x-this->mouseX );
	this->mouseX=x;
	this->mouseY=y;
	this->upateViewMatrix( );
}

void Camera::ZoomCamera( float distance )
{

}





