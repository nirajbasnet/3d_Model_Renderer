/**************************************************************
*                       -Neeraj Basnet,
*                       -Sagar Shrestha,
*                       -Rabin Giri,Jan 2 2015
**************************************************************/

#ifndef MATRIX_H_
#define MATRIX_H_
#include<math.h>
#include<Windows.h>
#include<tchar.h>
#include "Vector.h"
#define pi 3.14159265
//class of matrix 4x4 for 3d transformation
class Matrix
{

private:
	
	inline float Determinant( float m11, float m12, float m13,
		                      float m21, float m22, float m23,
							  float m31, float m32, float m33 );
	class Array
	{
	private:
		float *ptr;
	public:
		Array( float * value ):ptr(value){}
		float & operator []( int index ){ return ptr[index]; }

	};

public:
    float M[4][4];
	Matrix( );
    ~Matrix(  );
    void LoadIdentityMatrix( void );
	Matrix getTransposeMatrix( void );
	Matrix getInverseMatrix( void );
	float  Determinant( void );
	Matrix Translate( float x, float y, float z );
	Matrix Translate(vec3 distance);
	Matrix Rotate( float angle, char axis );// only 'x', 'y' and 'z' are valid argument
	Matrix Rotate( float angle, float x, float y, float z );
	Matrix Matrix::Rotate(float angle, vec3 axis);
	Matrix Scale( float scale );
	Matrix Scale( float sx, float sy, float sz );
	Matrix Scale(vec3 scale);
	void Reflection( char *plane );//only "xy", "yz" and  "xz" are valid argument
	Matrix operator * ( Matrix M );
    vec4 operator * ( vec4 P );
    Matrix operator + ( Matrix M );
	Matrix operator - ( Matrix M );
	Matrix operator * ( float k );
	Matrix operator / ( float k );
	void operator *= ( Matrix M ){ *this=*this*M; }
	void operator += ( Matrix M ){ *this=*this+M; }
	void operator -= ( Matrix M ){ *this=*this-M; }
	void operator *= ( float k ){ *this=*this*k; }
	void operator /= ( float k ){ *this=*this/k; }
	Array & operator []( int index ){ return Array( M[index] ); }
	void setcolumn( int index, const float col[4] );
	void setRow( int index, const float row[4] );
	
};





#endif


