#include"graphics.h"
#include "RobotRender.h"
#define VK_SMALL_Q 0x51
#define VK_SMALL_W 0x57
#define VK_SMALL_E 0x45
#define VK_SMALL_R 0x52

VertexBuffer vbuffer;
Vertexshader vshader;
Colorshader cshader;
Camera robocamera;
Projection perspective;
timer robotimer;
Matrix m;
vec3 campos;
Light centerlight;
Main()
{
	InitGraphicsWindow( 0, 0 ,WindowMaxWidth,WindowMaxHeight );
	return 0;
}
void printdata(float data)
	{
		text t;
		
		t.color(255,0,0);
		t=data;
		t.print();

	}


void GraphicsMainLoop( void )
{
	vbuffer.BufferColordata(vec3(0,0,0));
	vshader.ApplyModelTransformation(m);
	robocamera.setView(campos,0,0,0);
	vshader.setModelCamera(robocamera);
	vshader.ApplyNormalRotation(m);
	vshader.LinkVertexBuffer(vbuffer);
	centerlight.setPosition(campos);
	 cshader.SetLightSource(centerlight);
	vshader.LinkColorShader(cshader);
	robotimer.LogTime();
	vshader.RenderToScreen();
	float time =robotimer.GetDeltaTime();
	printdata(time);
    SwapFrameBuffer();
   
}
	

void GraphicsCreate( void )
{
	
	m.LoadIdentityMatrix();
	//m=m*m.Rotate(-90,vec3(0,1,0));
	//m=m*m.Rotate(180,vec3(1,0,0));
	m=m.Scale(3)*m;
	//m=m*m.Rotate(90,vec3(0,1,0));
	vshader.ApplyModelTransformation(m);
	std::vector <vec3> myvertices;
	std::vector<unsigned int > myindices;
	

	vbuffer.BufferColordata(vec3(1,1,1.0));
	if (loadOBJ("finalrobot.obj", myvertices, myindices))
	{
		vbuffer.BufferData(myvertices, myindices);
	}
		
	vshader.LinkVertexBuffer(vbuffer);
			
	
	campos=vec3(80,20,700);
	robocamera.setView(vec3(80,20,700),0,0,0); 
	perspective.Perspective(75, 16.0 / 9.0, 1.0, 150.0);
	vshader.ApplyPerspectiveTransformation(perspective);
	
	cshader.setup_Zbuffer(1366,768);
	centerlight.setambient(vec3(0.1, 0.0, 0.0));
	centerlight.setdiffuse(vec3(1.0, 0.0, 0.0));
	centerlight.setPosition(vec3(40, 50,100 ));
	centerlight.setRadius(500.0);
	centerlight.setspecular(vec3(0.7, 0.1, 0.05), 15);
	cshader.SetLightSource(centerlight);
vshader.setModelCamera(robocamera);
	vshader.LinkColorShader(cshader);

	robotimer.LogTime();
	vshader.RenderToScreen();
		float time =robotimer.GetDeltaTime();
	printdata(time);
    //SwapFrameBuffer();


}

void KeyBoard_Button( WPARAM wParam )
{
    switch (wParam)
	{
	
	case VK_UP:campos.z+=20;
		break;
	case VK_DOWN:campos.z-=20;
		break;
	case VK_LEFT:campos.x-=10;
		break;
	case VK_RIGHT:campos.x+=10;
		break;
	case VK_SHIFT:
		break;
	case VK_TAB:
		break;
	case VK_SPACE:
		break;
	case VK_CONTROL:
		break;
	case VK_SMALL_Q:  m=m*m.Rotate(90,vec3(0,1,0));
		break;
	case VK_SMALL_R:
		break;
	case VK_SMALL_W:campos.y+=10;
		break;
	case VK_SMALL_E:campos.y-=10;
		break;
}

	
 
 
 
	

	
}


void MouseMove(  int x, int y )
{
	;
}