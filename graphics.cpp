#include "graphics.h"
#include <math.h>
#include <stdlib.h>
#include "RobotRender.h"
#define Sxc 659 //centre of screen
#define Syc 350

HINSTANCE *hInst ;
HWND window_handle = NULL;
HDC hDc = NULL;
COLORREF Color;

HDC m_hSrcDC;
HDC m_hMemDC;
HBITMAP m_hBmp;
HGDIOBJ m_hBuffObj;
BITMAPINFOHEADER   m_bi;

COLORREF *framebuffer;
int **DepthBuffer;



#define putpixel(x,y) framebuffer[ y*WindowMaxWidth+x ]=Color
#define BGRA( Blue, Green, Red, Alpha ) (DWORD)(Blue)|(DWORD)(Green<<8)|(DWORD)(Red<<16)|(DWORD)(Alpha<<24)



/*******************************************************
***This program is event driven program*****************
***All the event is handle by this function**************/
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )
	{
	
	case WM_DESTROY:
		delete framebuffer;
		ReleaseDC(hWnd, hDc);
		PostQuitMessage( 0 );
		break;
	case WM_NULL:
		break;

	case WM_PAINT:
		break;
	
	case WM_MOUSEMOVE:
		MouseMove(  LOWORD( lParam), HIWORD( lParam ) );
		break;

	case WM_MOUSEWHEEL:
		break;

	case WM_LBUTTONDOWN:
		break;

	case WM_KEYDOWN:
		if( wParam==VK_ESCAPE )
		{
			PostQuitMessage( 0 );
			return 0;
		}
		
		KeyBoard_Button( wParam );
		break;

	default:
		return DefWindowProc( hWnd, message, wParam, lParam );
	
	}
	return 0;
}
/****************************************************
**Main loop of program******************************/
void createWindow(HINSTANCE *hInstance, int nCmdShow ,int oRiginX, int oRiginY, int wIdth, int heIght )
{
	MSG m;
	hInst = hInstance;
	BOOL bQuit = FALSE;
	PAINTSTRUCT ps;

	TCHAR classname[] = _T("MyWindow");
	WNDCLASSEX wcex = { NULL };
	wcex.cbSize = sizeof ( WNDCLASSEX );
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.hInstance = *hInstance;
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wcex.lpszClassName = classname;

	if ( !RegisterClassEx( &wcex ) )
		MessageBox( NULL, _T("window registeration fail"),_T("Error"), MB_ICONERROR | MB_OK );

	RECT rcDesktop = {0};
	GetClientRect(GetDesktopWindow(), &rcDesktop);
	
   window_handle = CreateWindowEx( 0,classname,_T("Graphics"),WS_OVERLAPPEDWINDOW,
		                 rcDesktop.left, rcDesktop.top, rcDesktop.right, rcDesktop.bottom, NULL,NULL, 
						 *hInstance, NULL);
   //SetWindowLong(window_handle, GWL_STYLE, 0);
	if ( !window_handle )
		MessageBox( NULL,_T("Unable to create window"), _T("Error"), MB_ICONERROR | MB_OK );

	ShowWindow( window_handle, nCmdShow );
	UpdateWindow( window_handle);

	/***********************Creating frame buffer********************************/
	framebuffer = new COLORREF[WindowMaxWidth*WindowMaxHeight+1];
	

	
	ClearFrameBuffer();

//----------------------------------------------------------------------------------------------------------------------//	
	hDc = BeginPaint( window_handle, &ps);

	m_hSrcDC = hDc;
	m_hMemDC = CreateCompatibleDC(0);
	m_hBmp = CreateCompatibleBitmap(m_hSrcDC, WindowMaxWidth, WindowMaxWidth );
	m_hBuffObj = SelectObject(m_hMemDC, m_hBmp);

	m_bi.biSize = sizeof(BITMAPINFOHEADER);
	m_bi.biWidth = WindowMaxWidth;
	m_bi.biHeight = -WindowMaxHeight;
	m_bi.biPlanes = 1;
	m_bi.biBitCount = 32;
	m_bi.biCompression = BI_RGB;
	m_bi.biSizeImage = 0;
	m_bi.biXPelsPerMeter = 0;
	m_bi.biYPelsPerMeter = 0;
	m_bi.biClrUsed = 0;
	m_bi.biClrImportant = 0;
//---------------------------------------------------------------------------------------------------------------------//
	GraphicsCreate();//function to create image and draw in  the screen in first time

	while ( !bQuit )
	{
		if (PeekMessage(&m, NULL, NULL, NULL, PM_REMOVE))
		{
			if (m.message == WM_QUIT)
				bQuit = TRUE;
			else
			{
				TranslateMessage(&m);
				DispatchMessage(&m);
			}
		}
		else
			GraphicsMainLoop();
	}

}
/**************************************************************************************
***************************************************************************************/

void screenClear(void)
{
	RECT rect;
	rect.top = 0;
	rect.left = 0;
	rect.bottom = 768;
	rect.right = 1366;
	FillRect(hDc, &rect, (HBRUSH)(8) );

}
/**************************************************************************************
***************************************************************************************/
void DDA_Line( int Startx, int Starty, int Endx, int Endy )
{
	Startx+=Sxc;
	Starty+=Syc;
	Endx+=Sxc;
	Endy+=Syc;
	
	int dx = Endx - Startx;
	int dy = Endy - Starty;

	if ( dx )
	{
		float slope = static_cast<float>(dy) / dx;
		
		if (fabsf(slope) <= 1)
		{

			if (dx < 0)
			{
				int temp = Startx;
				Startx = Endx;
				Endx = temp;

				temp = Starty;
				Starty = Endy;
				Endy = temp;

			}
			while (Startx <= Endx)
			{
				putpixel(Startx++,Starty);
				Starty += slope;
			}
		}

		
		else
		{
			if ( dy < 0 )
			{
				int temp = Startx;
				Startx = Endx;
				Endx = temp;

				temp = Starty;
				Starty = Endy;
				Endy = temp;

			}
			float x=Startx;
			while (Starty <= Endy)
			{
				putpixel(static_cast<int>(x), Starty++);
				x += 1 / slope;
			}
		}



	}
	
	
	else
	{
		
		if (dy < 0)
		{
			int temp = Startx;
			Startx = Endx;
			Endx = temp;

			temp = Starty;
			Starty = Endy;
			Endy = temp;

		}
		
		while (Starty <= Endy)
		{
			putpixel( Startx, Starty++ );
		}
	
	}
	


}
/****************************************************************************************
*****************************************************************************************/
void Line( int Startx, int Starty, int Endx, int Endy )
{
	int dx = Endx - Startx;
	int dy = Endy - Starty;
	int increment;
	int decision_parameter;

	if (( dx<0 && dy>0 ) || ( dx > 0 && dy < 0 ))
		increment = -1;
	else
		increment = 1;

	dx = abs(dx);
	dy = abs(dy);


	if (dy < dx)
	{
		if (Endx < Startx)
		{
			int temp = Startx;
			Startx = Endx;
			Endx = temp;

			temp = Starty;
			Starty = Endy;
			Endy = temp;

		}
		decision_parameter = 2 * dy - dx;
		do
		{
			Putpixel(Startx++, Starty);
			if ( decision_parameter < 0 )
				decision_parameter+= 2 * dy;
			else
			{
				decision_parameter += 2 * ( dy - dx );
				Starty += increment;
			}

		} while (Startx <= Endx);
	}


	else
	{
		if (Endy < Starty)
		{
			int temp = Startx;
			Startx = Endx;
			Endx = temp;

			temp = Starty;
			Starty = Endy;
			Endy = temp;

		}
		decision_parameter = 2 * dx - dy;
		do
		{
			Putpixel(Startx, Starty++);
			if (decision_parameter < 0)
				decision_parameter += 2 * dx;
			else
			{
				decision_parameter += 2 * (dx - dy);
				Startx += increment;
			}

		} while (Starty <= Endy);
	}
}

/****************************************************************************************
*****************************************************************************************/
void setcolor4f( float red, float green, float blue ,float alpha )
{
	Color = BGRA((unsigned char)(blue * 255), (unsigned char)(green * 255), (unsigned char)(red * 255),  (unsigned char)(alpha * 255) );
}
/*******************************************************************************************************
******************************************************************************************/
void SwapFrameBuffer( void )
{
	SetDIBits(m_hMemDC, m_hBmp, 0, WindowMaxHeight,framebuffer, (BITMAPINFO *)&m_bi, DIB_RGB_COLORS);
	//BitBlt(m_hSrcDC, 0, 0,WindowMaxWidth, WindowMaxHeight, m_hMemDC, 0, 0, SRCCOPY);
	GdiTransparentBlt( hDc,0,0,WindowMaxWidth,WindowMaxHeight,m_hMemDC,0,0,WindowMaxWidth,WindowMaxHeight,SRCCOPY);
	ClearFrameBuffer();
}
/*****************************************************************************************
******************************************************************************************/
void ClearFrameBuffer(void)
{
	for ( int x = 0; x < WindowMaxWidth*WindowMaxHeight;  x++ )
		framebuffer[x] = 0;
}
/*****************************************************************************************
******************************************************************************************/
void Circle(int xc, int yc, int r)
{
	int x = 0;
	int y = r;
	int decision_parameter = 1 - r;
	do
	{
		putpixel( (x + xc) , (y + yc) );
		putpixel( (-x + xc), (y + yc) );
		putpixel( (x + xc), (-y + yc) );
		putpixel( (-x + xc), (-y + yc) );
		putpixel( (y + xc) ,( x + yc) );
		putpixel( (y + xc), (-x + yc) );
		putpixel( (-y + xc), (x + yc) );
		putpixel( (-y + xc), (-x + yc) );

		x = x + 1;


		if ( decision_parameter < 0)
		{
			decision_parameter += 2 * x + 1;
		}
		else
		{
			y--;
			decision_parameter += 2*(x-y) + 1;
		}
	} while (x <= y);
}
/*****************************************************************************************
******************************************************************************************/
void Ellipse(int xc, int yc, int a, int b)
{
	int x = 0;
	int y = b;
	float decision_parameter = (b*b) + (a*a) / 4 - (a*a*b*b);
	
	int dx = 0;
	int dy = 2 * a*a*b;
	do
	{
		putpixel((x + xc), (y + yc));

		x = x + 1;
		if (decision_parameter < 0)
		{
			dx += 2 * b*b;
			decision_parameter += dx + b*b;

		}

		else
		{
			y--;
			dx += 2 * b*b;
			dy += -2 * a*a;
			decision_parameter += dx - dy + b*b;
		}

	} while (dx < dy);

}
/*****************************************************************************************
******************************************************************************************/
inline void Putpixel(int x, int y)//function to put pixel
{
	if((x<1366 && x>0)&&(y<768 && y>0)) 
	putpixel( x, y );
}

text::text( void )
{
	this->string=new char[25];
	Red=255;
	Green=255;
	Blue=255;
	PositionX=0;
	PositionY=0;
}

void text::operator = ( float value )
{
	int temp1,temp2;
	char chtemp[7];
	temp1=value;
	value-=temp1;
	temp2=(value*10000);
	itoa( temp1, string, 10 );
	itoa( temp2, chtemp , 10);
	strcat( string,"." );
	strcat( string, chtemp );

}

void text::operator = ( double value )
{
	int temp1,temp2;
	char chtemp[10];
	temp1=value;
	value-=temp1;
	temp2=(value*1000000 );
	itoa( temp1, string, 10 );
	itoa( temp2, chtemp , 10);
	strcat( string,"." );
	strcat( string, chtemp );

}

void text::operator = ( int value  )
{
	itoa( value, string, 10 );
}

void text::operator = ( char ch )
{
	for( int i=1; i<25; i++ )
		this->string[i]=0;
	this->string[0]=ch;
}

void text::operator = ( char *String )
{
	strcpy( string, String );
}

void text::operator << ( text t )
{
	SetTextColor( hDc, RGB( t.Red, t.Green, t.Blue ) );
	SetBkColor( hDc, TRANSPARENT ); 
	TextOut( hDc, PositionX, PositionY, t.string, strlen( t.string ) );
}

void text::color(  unsigned char red, unsigned char green, unsigned char blue )
{
	this->Blue=blue;
	this->Red=red;
	this->Green=green;
}

void text::GotoXY( int x, int y )
{
	this->PositionX=x;
	this->PositionY=y;
}

void text::print( void )
{
	SetTextColor( hDc, RGB( Red, Green, Blue ) );
	SetBkColor( hDc, TRANSPARENT ); 
	TextOut( hDc, PositionX, PositionY, string, strlen( string ) );
}




