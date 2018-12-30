
#include"matrix.h"



Matrix::Matrix( )
{
	/*M=new float*[4];
	for( int i=0; i<4; i++ )
		M[i]=new float[4];
		*/
	for( int i=0; i<4; i++ )
		for( int j=0; j<4; j++ )
			if( i==j )
				this->M[i][j]=1.0f;
			else
				this->M[i][j]=0.0f;
}

Matrix::~Matrix( )
{

}

void Matrix::LoadIdentityMatrix( void )
{
	for( int i=0; i<4; i++ )
		for( int j=0; j<4; j++ )
			if( i==j )
				this->M[i][j]=1.0f;
			else
				this->M[i][j]=0.0f;
}


inline float Matrix::Determinant(  float m11, float m12, float m13,
		                           float m21, float m22, float m23,
							       float m31, float m32, float m33 )
{

	return( m11*(m22*m33-m23*m32)-m12*(m21*m33-m23*m31)+m13*(m21*m32-m22*m31 ) );
}

Matrix Matrix::getTransposeMatrix( void )
{
	Matrix M;
	for( int i=0; i<4; i++ )
		for( int j=0; j<4; j++ )
			M.M[i][j]=this->M[j][i];

	return M;
}

float Matrix::Determinant( void )
{
	return ( M[0][0]*Determinant( M[1][1], M[1][2], M[1][3], M[2][1], M[2][2], M[2][3], M[3][1], M[3][2], M[3][3] )
		    -M[0][1]*Determinant( M[1][0], M[1][2], M[1][3], M[2][0], M[2][2], M[2][3], M[3][0], M[3][2], M[3][3] )
			+M[0][2]*Determinant( M[1][0], M[1][1], M[1][3], M[2][0], M[2][1], M[2][3], M[3][0], M[3][1], M[3][3] )
			-M[0][3]*Determinant( M[1][0], M[1][1], M[1][2], M[2][0], M[2][1], M[2][2], M[3][0], M[3][1], M[3][2] ) );
}

Matrix Matrix::Translate( float x, float y, float z )
{
	Matrix m;
	m.M[0][3] = x;
	m.M[1][3] = y;
	m.M[2][3] = z;
	return m;
}
Matrix Matrix::Translate(vec3 distance)
{
	return(Translate(distance.x, distance.y, distance.z));
}

Matrix Matrix::Rotate( float angle, char axis )
{
	Matrix m;
	angle*=pi/180;
	float Cos=cosf( angle );
	float Sin=sinf( angle );

	if( axis=='x' )
	{
		m.M[1][0] = m.M[1][0] *Cos - m.M[2][0] *Sin;
		m.M[1][1] = m.M[1][1] *Cos - m.M[2][1] *Sin;
		m.M[1][2] = m.M[1][2] *Cos - m.M[2][2] *Sin;
		m.M[1][3] = m.M[1][3] *Cos - m.M[2][3] *Sin;
		m.M[2][0] = m.M[1][0] *Sin + m.M[2][0] *Cos;
		m.M[2][1] = m.M[1][1] *Sin + m.M[2][1] *Cos;
		m.M[2][2] = m.M[1][2] *Sin + m.M[2][2] *Cos;
		m.M[2][3] = m.M[1][3] *Sin + m.M[2][3] *Cos;
	}

	else if( axis=='y' )
	{
		m.M[0][0] = m.M[0][0] *Cos + m.M[2][0]* Sin;
		m.M[0][1] = m.M[0][1] *Cos + m.M[2][1]* Sin;
		m.M[0][2] = m.M[0][2] *Cos + m.M[2][2]* Sin;
		m.M[0][3] = m.M[0][3] *Cos + m.M[2][3]* Sin;
		m.M[2][0] = -m.M[0][0] *Sin + m.M[2][0]* Cos;
		m.M[2][1] = -m.M[0][1] *Sin + m.M[2][1]* Cos;
		m.M[2][2] = -m.M[0][2] *Sin + m.M[2][2]* Cos;
		m.M[2][3] = -m.M[0][3] *Sin + m.M[2][3]* Cos;
	}

	else if( axis=='z' )
	{
		m.M[0][0] = m.M[0][0] *Cos - m.M[1][0] *Sin;
		m.M[0][1] = m.M[0][1] *Cos - m.M[1][1] *Sin;
		m.M[0][2] = m.M[0][2] *Cos - m.M[1][3] *Sin;
		m.M[0][3] = m.M[0][3] *Cos - m.M[1][3] *Sin;
		m.M[1][0] = m.M[0][0] *Sin + m.M[1][0] *Cos;
		m.M[1][1] = m.M[0][1] *Sin + m.M[1][1] *Cos;
		m.M[1][2] = m.M[0][2] *Sin + m.M[1][2] *Cos;
		m.M[1][3] = m.M[0][3] *Sin + m.M[1][3] *Cos;
	}

	else
		MessageBox( NULL, _T("x, y & z are only valid argument of rotation axis"), _T("Error"), MB_OK|MB_ICONERROR );

	return m;
}

Matrix Matrix::Rotate( float angle, float x, float y, float z )
{
	Matrix m;

	angle*=pi/180;
	float Cos=cosf( angle );
	float Sin=sinf( angle );
	float xx=x*x;
	float yy=y*y;
	float zz=z*z;
	float xy=x*y;
	float xz=x*z;
	float yz=y*z;

	m.M[0][0]=xx *( 1-Cos )+Cos;
	m.M[0][1]=xy *( 1-Cos )-z*Sin;
	m.M[0][2]=xz *( 1-Cos ) + y*Sin;
	m.M[0][3]=0.0f;

	m.M[1][0]=xy *( 1-Cos )+ z*Sin;
	m.M[1][1]=yy *( 1-Cos )+Cos;
	m.M[1][2]=yz *( 1-Cos ) - x*Sin;
	m.M[1][3]=0.0f;

	m.M[2][0]=xz *( 1-Cos )-y*Sin;
	m.M[2][1]=yz *( 1-Cos )+x*Sin;
	m.M[2][2]=zz *( 1-Cos ) + Cos;
	m.M[2][3]=0.0f;

    m.M[3][0]=0.0f;
	m.M[3][1]=0.0f;
	m.M[3][2]=0.0f;
	m.M[3][3]=1.0f;

	
    return m;

}

Matrix Matrix::Rotate(float angle, vec3 axis)
{
	return (Rotate(angle, axis.x, axis.y, axis.z));
}

Matrix Matrix::Scale(float sx, float sy, float sz)
{
	Matrix m;
	m.M[0][0] = sx;
	m.M[1][1] = sy;
	m.M[2][2] = sz;
	return m;
}

Matrix Matrix::Scale(float scale)
{
	Matrix temp = Scale(scale, scale, scale);
	return temp;
}
Matrix Matrix::Scale(vec3 scale)
{
	return(Scale(scale.x, scale.y, scale.z));
}

void Matrix::Reflection(char *plane)
{
	if (plane[0] == _T('y') && plane[1] == _T('x'))
	{
		M[2][0] = -M[2][0]; M[2][1] = -M[2][1]; M[2][2] = -M[2][2]; M[2][3] = -M[2][3];
	}

	else if (plane[0] == _T('z') && plane[1] == _T('y'))
	{
		M[0][0] = -M[0][0]; M[0][1] = -M[0][1]; M[0][2] = -M[0][2]; M[0][3] = -M[0][3];
	}

	else if (plane[0] == _T('z') && plane[1] == _T('x'))
	{
		M[1][0] = -M[1][0]; M[1][1] = -M[1][1]; M[1][2] = -M[1][2]; M[1][3] = -M[1][3];
	}

	else
		MessageBox(NULL, _T("xy, yz and zx are only valid argument"), _T("Error"), MB_OK | MB_ICONERROR);
}

Matrix Matrix::operator*( Matrix M )
{
	Matrix m;
	for( int i=0; i<4; i++ )
		for( int j=0; j<4; j++ )
			m.M[i][j]=this->M[i][0]*M.M[0][j]+this->M[i][1]*M.M[1][j]+this->M[i][2]*M.M[2][j]+this->M[i][3]*M.M[3][j];
	return m;
}

 vec4 Matrix::operator * ( vec4 P )
{
	vec4 temp;
	temp.x = P.x*M[0][0] + P.y*M[0][1] + P.z*M[0][2] + P.w * M[0][3];
	temp.y = P.x*M[1][0] + P.y*M[1][1] + P.z*M[1][2] + P.w * M[1][3];
	temp.z = P.x*M[2][0] + P.y*M[2][1] + P.z*M[2][2] + P.w * M[2][3];
	temp.w = P.x*M[3][0] + P.y*M[3][1] + P.z*M[3][2] + P.w * M[3][3];
	return temp;
}

Matrix Matrix::operator+( Matrix M )
{
	Matrix m;
	for( int i=0; i<4; i++ )
		for( int j=0; j<4; j++ )
			m.M[i][j]=this->M[i][j]+M.M[i][j];

	return m;
}

Matrix Matrix::operator-( Matrix M )
{
	Matrix m;
	for( int i=0; i<4; i++ )
		for( int j=0; j<4; j++ )
			m.M[i][j]=this->M[i][j]-M.M[i][j];

	return m;
}

Matrix Matrix::operator *( float k )
{
	Matrix m;
	for( int i=0; i<4; i++ )
		for( int j=0; j<4; j++ )
			m.M[i][j]=this->M[i][i]*k;
	return m;
}

Matrix Matrix::operator /( float k )
{
	Matrix m;
	for( int i=0; i<4; i++ )
		for( int j=0; j<4; j++ )
			m.M[i][j]=this->M[i][j]/k;
	return m;
}



Matrix Matrix::getInverseMatrix( void )
{
	Matrix M;
	M.M[0][0]=Determinant( this->M[1][1], this->M[1][2], this->M[1][3], 
		                   this->M[2][1], this->M[2][2], this->M[2][3], 
						   this->M[3][1], this->M[3][2], this->M[3][3] );
	
	M.M[0][1]=-Determinant( this->M[1][0], this->M[1][2], this->M[1][3],
		                    this->M[2][0], this->M[2][2], this->M[2][3],
						    this->M[3][0], this->M[3][2], this->M[3][3] );
	
	M.M[0][2]=Determinant( this->M[1][0], this->M[1][1], this->M[1][3],
		                   this->M[2][0], this->M[2][1], this->M[2][3],
						   this->M[3][0], this->M[3][1], this->M[3][3] );

	M.M[0][3]=-Determinant( this->M[1][0], this->M[1][1], this->M[1][2],
		                    this->M[2][0], this->M[2][1], this->M[2][2],
						    this->M[3][0], this->M[3][1], this->M[3][2] );

	M.M[1][0]=-Determinant( this->M[0][1], this->M[0][2], this->M[0][3],
		                    this->M[2][1], this->M[2][2], this->M[2][3],
			    			this->M[3][1], this->M[3][2], this->M[3][3] );
	
	M.M[1][1]=Determinant( this->M[0][0], this->M[0][2], this->M[0][3],
		                   this->M[2][0], this->M[2][2], this->M[2][3],
						   this->M[3][0], this->M[3][2], this->M[3][3] );
	
	M.M[1][2]=-Determinant( this->M[0][0], this->M[0][1], this->M[0][3],
		                    this->M[2][0], this->M[2][1], this->M[2][3],
						    this->M[3][0], this->M[3][1], this->M[3][3] );

	M.M[1][3]=Determinant( this->M[0][0], this->M[0][1], this->M[0][2],
		                   this->M[2][0], this->M[2][1], this->M[2][2],
						   this->M[3][0], this->M[3][1], this->M[3][2] );

	M.M[2][0]=Determinant( this->M[0][1], this->M[0][2], this->M[0][3],
		                   this->M[1][1], this->M[1][2], this->M[1][3],
						   this->M[3][1], this->M[3][2], this->M[3][3] );
	
	M.M[2][1]=-Determinant( this->M[0][0], this->M[0][2], this->M[0][3],
		                    this->M[1][0], this->M[1][2], this->M[1][3],
						    this->M[3][0], this->M[3][2], this->M[3][3] );
	
	M.M[2][2]=Determinant( this->M[0][0], this->M[0][1], this->M[0][3],
		                   this->M[1][0], this->M[1][1], this->M[1][3],
						   this->M[3][0], this->M[3][1], this->M[3][3] );

	M.M[2][3]=-Determinant( this->M[0][0], this->M[0][1], this->M[0][2],
		                    this->M[1][0], this->M[1][1], this->M[1][2],
						    this->M[3][0], this->M[3][1], this->M[3][2] );

	M.M[3][0]=-Determinant( this->M[0][1], this->M[0][2], this->M[0][3],
		                    this->M[1][1], this->M[1][2], this->M[1][3],
						    this->M[2][1], this->M[2][2], this->M[2][3] );
	
	M.M[3][1]=Determinant( this->M[0][0], this->M[0][2], this->M[0][3],
		                   this->M[1][0], this->M[1][2], this->M[1][3],
						   this->M[2][0], this->M[2][2], this->M[2][3] );
	
	M.M[3][2]=-Determinant( this->M[0][0], this->M[0][1], this->M[0][3],
		                    this->M[1][0], this->M[1][1], this->M[1][3],
						    this->M[2][0], this->M[2][1], this->M[2][3] );

	M.M[3][3]=Determinant( this->M[0][0], this->M[0][1], this->M[0][2],
		                   this->M[1][0], this->M[1][1], this->M[1][2],
						   this->M[2][0], this->M[2][1], this->M[2][2] );

	M/=this->Determinant( );

	return M;
}

void Matrix::setcolumn( int index, const float col[4] )
{
	this->M[0][index]=col[0]; this->M[1][index]=col[1]; this->M[2][index]=col[2]; this->M[3][index]=col[3];
}

void Matrix::setRow( int index, const float row[4] )
{
	this->M[index][0]=row[0]; this->M[index][1]=row[1]; this->M[index][2]=row[2]; this->M[index][3]=row[3];
}