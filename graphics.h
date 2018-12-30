/**************************************************************
*                       -Neeraj Basnet,
*                       -Sagar Shrestha,
*                       -Rabin Giri,Jan 2 2015
**************************************************************/


#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#pragma comment(lib, "Gdi32.lib")

#include<Windows.h>
#include<tchar.h>





#define WindowMaxHeight 768
#define WindowMaxWidth 1366



class text
{
private:
	TCHAR *string;
	unsigned char Red;
	unsigned char Green;
	unsigned char Blue;
	int PositionX;
	int PositionY;
public:
	text( );
	~text( ){ delete string; }
	void operator = ( float value );
	void operator = ( double value );
	void operator = ( int value   );
	void operator = ( char ch     );
	void operator = ( char *String );
	void color( unsigned char red, unsigned char green, unsigned char blue );
	void GotoXY( int x, int y );
	void operator << ( text t );
	void print( void );
};



class timer
{
private:
	LARGE_INTEGER frequency;
    LARGE_INTEGER T1;
	LARGE_INTEGER T2;
public:
	timer( ){ QueryPerformanceFrequency( &frequency ); }
	void LogTime( ){ QueryPerformanceCounter( &T1 ); }
	double GetDeltaTime( void ){ QueryPerformanceCounter( &T2 ); return ( (T2.QuadPart-T1.QuadPart) * 1000.0 / frequency.QuadPart ); }// return time in millisecond
};

//**************************************************************************************************************************//




#define Main() int _stdcall WinMain( HINSTANCE hInstance, HINSTANCE hPrev, LPSTR ipszCmdLine, int nCmdshow )
#define InitGraphicsWindow(  oRiginX, oRiginY,  wIdth,  heIght )  createWindow( &hInstance, nCmdshow , oRiginX, oRiginY,  wIdth,  heIght  )

void createWindow( HINSTANCE *, int ,int ,int ,int ,int );//function to create window

void GraphicsMainLoop( void );//main loop of graphics

void GraphicsCreate( void );//function to create background

void KeyBoard_Button( WPARAM );//function for keyboard

void MouseMove(  int x, int y );//function for mouse

void screenClear( void );//function which clear the screen

inline void Putpixel(int x, int y);//function to put pixel

void DDA_Line( int Startx, int Starty, int Endx, int Endy );//function to draw line using DDA algortihm

void Line( int Startx, int Starty, int Endx, int Endy );//function to draw line using Brasenham's algortihm

void setcolor4f( float red, float green, float blue, float alpha );//color of drawing object

void SwapFrameBuffer( void );//function to draw image and clear the frame buffer

void ClearFrameBuffer( void );//function to clear frame buffer

void Circle( int xc, int yc, int r );//function to draw circle

void Ellipse(int xc, int yc, int a, int b);//function to draw ellipse


LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );//function to handel events



#endif
