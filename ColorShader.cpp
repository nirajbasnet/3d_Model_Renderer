#include "ColorShader.h"
#include "graphics.h"
void Colorshader::RunColorShader(VertexBuffer &verobject)
{
	
	for (int i = 0; i < verobject.triangles.size(); i++)  //Viewport transformation
	{
		verobject.triangles[i].clipper_status= true;
		for (int j = 0; j < 3; j++)
		{
			if(!viewport(verobject.triangles[i].position[j]))
		    verobject.triangles[i].clipper_status= false;		
		}
	}
	//vec3 color(1,1,1);
	//vec4 a(10,10,0,1),b(50,10,0,1),c(100,100,0,1);
	//fillTriangle(a,b,c,color,color,color);
	//std::cout << "entering triangle mode\n";
	for (int i = 0; i < verobject.triangles.size(); i++)  //Viewport transformation
	{
		if(verobject.triangles[i].clipper_status)
		{
			//std::cout << "\n" << "data "<<i+1<<"\t" << verobject.triangles[i].position[j].x << "\t" << verobject.triangles[i].position[j].y << "\t" << verobject.triangles[i].position[j].z;
			//for sagar filling and line drawing of vertices
		    //wireframe(verobject.triangles[i].position[0].xyz(),verobject.triangles[i].position[1].xyz(),verobject.triangles[i].position[2].xyz());
			
			fillTriangle(verobject.triangles[i].position[0].xyz(),verobject.triangles[i].position[1].xyz(),verobject.triangles[i].position[2].xyz(),verobject.triangles[i].color[0],verobject.triangles[i].color[1],verobject.triangles[i].color[2]);
		   
		}
	}


}

void Colorshader:: wireframe(vec3 v1, vec3 v2, vec3 v3)
{
  setcolor4f(1,0,0,0);
  //Line(-10,-10,-150,-150);
  Line(v1.x,v1.y,v2.x,v2.y);
  Line(v2.x,v2.y,v3.x,v3.y);
  Line(v3.x,v3.y,v1.x,v1.y);
  
}

vec3 Colorshader::Calculate_Single_Lighting(int light_index, vec3 worldPos, vec3 normal, vec3 color)
{
	vec3 finalcolor;

	vec3 incident;
	incident = (lightsource[light_index].getPosition() - worldPos).Normalise();
	float lambert = max(0.0, vec3::dot(incident, normal));

	float dist = (lightsource[light_index].getPosition() - worldPos).Length();
	float atten = 1.0 - constrain(dist / (lightsource[light_index].getRadius()), 0.0, 1.0);

          vec3 viewDir = ( cameraPos - worldPos ).Normalise();
          vec3 halfDir = ( incident + viewDir ).Normalise();

          float rFactor = max (0.0 , vec3::dot ( halfDir , normal ));
          float sFactor = powf( rFactor , lightsource[light_index].get_Spower());

          finalcolor =   lightsource[light_index].get_diffuse()*color*lambert*atten  ;
          finalcolor += (lightsource[light_index].get_specular() * sFactor ) * mat_specular;

          return finalcolor;
     }

vec3 Colorshader::Compute_final_lighting(vec3 worldPos,vec3 normal,vec3 color)
{
    vec3 temp;
    for(int i=0;i<lightsource.size();i++){
    temp=Calculate_Single_Lighting(i,worldPos,normal,color)+lightsource[i].get_ambient();
    }
return temp;
}

void Colorshader::UsePhongModel(VertexBuffer &colorobject)
{

}
void Colorshader::UseGourardModel(VertexBuffer &colorobject)
{
	for (int i = 0; i <colorobject.triangles.size() ; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			colorobject.triangles[i].color[j] = Compute_final_lighting(colorobject.triangles[i].position[j].xyz(), colorobject.triangles[i].normal[j], colorobject.triangles[i].color[j]);
		}
	}
}

void Colorshader::setup_Zbuffer(const int winwidth,const int winheight)
{
	//Z = new float*[winheight];
	//for (int i = 0; i<winheight; i++)
	//	Z[i] = new float[winwidth];
    for(int i=0;i<winwidth;i++)
      for(int j=0;j<winheight;j++)
    this->Z[i][j]=9999.0f;

}
bool Colorshader::Run_Zbuffer(int x,int y,float z)
{
if(z<Z[x][y])
{
    Z[x][y]=z;
    return true;
}
else
    return false;
}

void Colorshader::setup_Viewport(unsigned int viewportx, unsigned int viewporty, unsigned int viewportwidth, unsigned int viewportheight)
{
	this->viewportx = viewportx;
	this->viewporty = viewporty;
	this->viewportwidth = viewportwidth;
	this->viewportheight = viewportheight;
}

Matrix Colorshader::viewport()  //x,y=(0,0) lower left corner of viewport rectangle
{
Matrix vp;
vp.LoadIdentityMatrix();
vp[0][0]=vp[0][3]=viewportwidth/2.0f;
vp[1][1]=vp[1][3]=viewportheight/2.0f;
//vp[1][1]=-height/2.0f;          // //For windows display viewport..assuming origin in upper left corner
//vp[1][3]= height/2.0f;
vp[2][2]=vp[2][3]=0.5f;
vp[3][3]=1;
return vp;
}

bool Colorshader::viewport(vec4 &ndc)
{
 ndc.x=(ndc.x+1)*(viewportwidth-200)/2.0f;
 ndc.y=(1-ndc.y)*(viewportheight-200)/2.0f;
// ndc.y=(viewportheight-200)*(ndc.y;            //For windows display viewport..assuming origin in upper left corner
 ndc.z=(ndc.z+1)*100.0f;
 if((ndc.x<0 || ndc.x>1366) || (ndc.y<0 || ndc.y>768))
	 return false;
 else
	 return true;
}

void Colorshader::fillTriangle(vec3 p1,vec3 p2,vec3 p3, vec3 cl1, vec3 cl2, vec3 cl3)
{
  //int v4[2],v1[2],v2[2],v3.y, p1[2], p2[2], p3[2];

  /*p1.x= vt1.x;   p2.x= vt2.x;   p3.x= vt3.x;
  p1.y= vt1.y;   p2.y= vt2.y;   p3.y= vt3.y;
  p1[2]= vt1.z;   p2[2]= vt3.z;   p3[3]= vt3.z;
  */
  vec3 v1,v2,v3,v4, c1,c2,c3,c4;
  
  if(p1.y>= p2.y)
  {
	  if(p1.y>=p3.y)
	  {
		  v1 = p1;
		  c1 = cl1;

		  if(p2.y>=p3.y)
		  {
			  v2 = p2;
			  c2 = cl2;
			  v3 = p3;
			  c3 = cl3;
		  }
		  else
		  {
			  v2 = p3;  
			  c2 = cl3;
			  v3 = p2;
			  c3 = cl2;
		  }
	  }
	  else
	  {
		  v1 = p3;
		  c1 = cl3;
		  v2 = p1;
		  c2 = cl1;

		  v3 = p2;
		  c3 = cl2;
	  }
  }
  else
  {
	  if(p2.y>=p3.y)
	  {
		  v1 = p2;
		  c1 = cl2;

		  if(p3.y>=p1.y)
		  {
			  v2 = p3;
		   	  c2 = cl3;

			  v3 = p1;
			  c3 = cl1;
		  }
		  else
		  {
			  v2 = p1;
			  c2 = cl1;

			  v3 = p3;
			  c3 = cl3;
		  }
	  }
	  else
	  {
		  v1 = p3;
		  c1 = cl3;

		  v2 = p2;
		  c2 = cl2;

		  v3 = p1;
		  c3 = cl1;
	  }
  }
  
  if((int)v1.y==(int)v2.y && (int)v2.y==(int)v3.y)
  {
    if(v1.x>v2.x)
    {
        if(v1.x>v3.x)
        {
			if(v2.x>v3.x)
			{
				fillLine(v1,v3,c1,c3);
			}
			else
				fillLine(v1,v2,c1,c2);
        }
        else
        {
			fillLine(v2,v3,c2,c3);
        }
    }
    else
    {
        if(v2.x>v3.x)
        {
			if(v1.x>v3.x)
			{
				fillLine(v2,v3,c2,c3);
			}
			else
				fillLine(v2,v1,c2,c1);
        }
        else
        {
			fillLine(v1,v3,c1,c3);
        }
    }
  }


  else if((int)v1.x==(int)v2.x && (int)v1.x==(int)v3.x)
  {
	  fillLine(v1,v3,c1,c3);
  }

  else if(((float)((int)v2.y-(int)v1.y)/((int)v2.x-(int)v1.x))==((float)((int)v3.y-(int)v2.y)/((int)v3.x-(int)v2.x)))
  {
	  fillLine(v1,v3,c1,c3);
  }
  
  else if ((int)v2.y == (int)v3.y && v2.x<=v3.x)
  {
   fillTopTriangle(v2, v3, v1, c2, c3, c1);
  }
  else if((int)v2.y == (int)v3.y && v2.x>v3.x)
  {
    fillTopTriangle(v3, v2, v1, c3, c2, c1);
  }
  
  else if ((int)v1.y == (int)v2.y && v1.x<=v2.x)
  {
    fillBottomTriangle(v3, v1, v2, c3, c1, c2);
  }
  else if ((int)v1.y == (int)v2.y && v1.x > v2.x)
  {
    fillBottomTriangle(v3, v2, v1, c3, c2, c1);
  }
  
  else
  {
  v4.x=(int)(v1.x + ((float)(v2.y - v1.y) / (float)(v3.y - v1.y)) * (v3.x - v1.x));
  v4.y=v2.y;
  
  
  float v1_comp  = abs(v1.y-v4.y) + abs(v1.x-v4.x);
  float v3_comp  = abs(v3.y-v4.y) + abs(v3.x-v4.x);
  float length   = v1_comp+v3_comp;
  v1_comp  /= length;
  v3_comp  /= length;
  c4 = c3*v1_comp + c1*v3_comp;
  
  v4.z = v3.z*v1_comp + v1.z*v3_comp;

   if(v4.x<v2.x)
  {
    fillBottomTriangle(v3,v4,v2,c3,c4,c2);
    fillTopTriangle(v4,v2,v1,c4,c2,c1);
  }
  else
  {
    fillBottomTriangle(v3,v2,v4,c3,c2,c4);
    fillTopTriangle(v2,v4,v1,c2,c4,c1);
  }
  }
  
}

void Colorshader::fillBottomTriangle(vec3 v1,vec3 v2,vec3 v3, vec3 c1, vec3 c2, vec3 c3)
{
	
  float invslope1=0;
  float invslope2=0;
  if(v1.y!=v2.y)
  invslope1 = (float)((int)v2.x - (int)v1.x) / ((int)v2.y - (int)v1.y);
  if(v3.y!=v1.y)
  invslope2 = (float)((int)v3.x - (int)v1.x) / ((int)v3.y - (int)v1.y);

  float v2_comp, vv2_comp, v3_comp,vv3_comp, length2,length3;
  float depth1=300.0, depth2=300.0;
  float depth_buff=300.0;
  vec3 c1_buffer=c1;
  vec3 c2_buffer=c1;
  vec3 pixel_color=c1;

  float curx1 = (int)(ceil(v1.x));
  float curx2 = floor(v1.x+0.5f);
 
  v1.toInt(); v2.toInt(); v3.toInt();
  length2= fabs(v2.y-v1.y);
  length3= fabs(v3.y-v1.y);
  
  if(length2!=0)
  {
  c1_buffer=(c2-c1)/length2;
  depth1=((float)(v2.z-v1.z))/length2;
  }
  else
  return;
  if(length3!=0)
  {
  c2_buffer=(c3-c1)/length3;
  depth2=((float)(v3.z-v1.z))/length3;
  }
  else
	  return;
  float depth_buff1=v1.z;
  float depth_buff2=v1.z;
  float depth_para=0.0f;
  vec3 color_buff1=c1;
  vec3 color_buff2=c1;
  vec3 color_para(0.0f,0.0f,0.0f);
  
  for (int scanlineY = (int)v1.y; scanlineY <= (int)v2.y; scanlineY++)
  {
     
	  //if(curx2!=curx1)
	  color_para = (color_buff2 - color_buff1)/(curx2-curx1+1.7f);
	  //else
	  //color_para=vec3(0.0f,0.0f,0.0f);
	  pixel_color = color_buff1;

	  depth_buff =depth_buff1;
	  //if(curx1!=curx2)
      depth_para = (float)(depth_buff2-depth_buff1)/(curx2-curx1+1.7f);
	  //else
		//  depth_para=0.0f;
	  
	  for(int i=(int)(ceil(curx1-1.0f));i<=(int)((curx2+0.7f));i++)
	  {
		  //depth_buff  = depth1*abs((float)(curx2-i)/(curx2-curx1)) + depth2*abs((float)(i-curx1)/(curx2-curx1));
		 
		  if(Run_Zbuffer(i,scanlineY,depth_buff))
		  {
		  //pixel_color = c1_buffer*abs((float)(curx2-i)/(curx2-curx1)) + c2_buffer*abs((float)(i-curx1)/(curx2-curx1));
		  
		  if(pixel_color.x>1.0)
			  pixel_color.x=1;
		  if(pixel_color.y>1.0)
			  pixel_color.y=1;
          if(pixel_color.z>1.0)
			  pixel_color.z=1;
		  setcolor4f(pixel_color.x,pixel_color.y,pixel_color.z,0);
		  Putpixel(i,scanlineY);
		  
		  }
		  pixel_color = pixel_color+ color_para;
		   depth_buff += depth_para;
	  }
	  	  color_buff1 = color_buff1+ c1_buffer;
	      color_buff2 = color_buff2+ c2_buffer;
	  	  depth_buff1 +=depth1;
	      depth_buff2 +=depth2;
		  curx1 += invslope1;
          curx2 += invslope2;
  
  
  }
}


void Colorshader::fillTopTriangle(vec3 v1, vec3 v2, vec3 v3 , vec3 c1, vec3 c2, vec3 c3)
{

  float invslope1=0;
	 // if(v3.y!=v1.y)
	  invslope1= (float)((int)v3.x - (int)v1.x) / ((int)v3.y - (int)v1.y);
	 
  float invslope2=0;
	  //if(v3.y!=v2.y)
	  invslope2= (float)((int)v3.x - (int)v2.x) / ((int)v3.y - (int)v2.y);

  float v2_comp, vv2_comp, v3_comp,vv3_comp, length2,length3;
  float depth1=300.0, depth2=300.0;
  float depth_buff=300.0;
  vec3 c1_buffer=c1;
  vec3 c2_buffer=c1;
  vec3 pixel_color=c1;

  float curx1 = (int)((v3.x));
  float curx2 = v3.x+0.5f;
   v1.toInt(); v2.toInt(); v3.toInt();
  length2= fabs(v3.y-v1.y);
  length3= fabs(v3.y-v2.y);
 



  if(length2!=0)
  {
  c1_buffer=(c1-c3)/length2;
  depth1=((float)(v1.z-v3.z))/length2;
  }
  else
  return;
  if(length3!=0)
  {
  c2_buffer=(c2-c3)/length3;
  depth2=((float)(v2.z-v3.z))/length3;
  }
  else
	  return;

  float depth_buff1=v3.z;
  float depth_buff2=v3.z;
  float depth_para=0.0f;
  vec3 color_buff1=c3;
  vec3 color_buff2=c3;
  vec3 color_para(0,0,0);
 


  for (int scanlineY = (int)v3.y; scanlineY > (int)v1.y; scanlineY--)
  {
  
	  //if(curx2!=curx1)
	  color_para = (color_buff2 - color_buff1)/(curx2-curx1+1.7f);
	  //else
	//	  color_para=vec3(0,0,0);
	  pixel_color = color_buff1;
	  depth_buff =depth_buff1;
	  //if(curx1!=curx2)
      depth_para = (depth_buff2-depth_buff1)/(curx2-curx1+1.7f);
	  //else
	//	  depth_para=0;
	  
	  for(int i=(int)(ceil(curx1-1.0f));i<=(int)((curx2+0.7f));i++)
	  {
		 // depth_buff = depth1*abs((float)(curx2-i)/(curx2-curx1)) + depth2*abs((float)(i-curx1)/(curx2-curx1));
		  if(Run_Zbuffer(i,scanlineY,depth_buff))
		  {
		  //pixel_color = c1_buffer*abs((float)(curx2-i)/(curx2-curx1)) + c2_buffer*abs((float)(i-curx1)/(curx2-curx1));
		  if(pixel_color.x>1.0)
			  pixel_color.x=1;
		  if(pixel_color.y>1.0)
			  pixel_color.y=1;
          if(pixel_color.z>1.0)
			  pixel_color.z=1;
		  setcolor4f(pixel_color.x,pixel_color.y,pixel_color.z,0);
		  Putpixel(i,scanlineY);
		  
		  }
		  pixel_color = pixel_color+color_para;
		  depth_buff+=depth_para;
	  }
	color_buff1 = color_buff1+ c1_buffer;
	color_buff2 = color_buff2+ c2_buffer;
	  depth_buff1 +=depth1;
	  depth_buff2 +=depth2;
    curx1 -= invslope1;
    curx2 -= invslope2;
  }
  

}

void Colorshader::fillLine(vec3 v1,vec3 v2,vec3 c1,vec3 c2)
{
	int Startx=v1.x;
    int Starty=v1.y;
    int Endx=v2.x;
    int Endy=v2.y;

    float v1_comp=0;
    float v2_comp=0;
    float length=0;
    vec3 c_buffer;
	float depth_buff=9999.0f;

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

		    v2_comp  = abs(v2.y-Starty) + abs(v2.x-Startx);
	        v1_comp = abs(v1.y-Starty) + abs(v1.x-Startx);
            length = (v1_comp + v2_comp);
	        v1_comp  /= length;
	        v2_comp  /= length;
			depth_buff = (v1.z*v2_comp + v2.z*v1_comp);
	 	    if(Run_Zbuffer(Startx,Starty,depth_buff))
			{
			c_buffer = (c1*v2_comp + c2*v1_comp);
			setcolor4f(c_buffer.x,c_buffer.y,c_buffer.z,0);    
			Putpixel(Startx, Starty);
			}
			Startx++;
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
			v2_comp  = abs(v2.y-Starty) + abs(v2.x-Startx);
	        v1_comp = abs(v1.y-Starty) + abs(v1.x-Startx);
            length = (v1_comp + v2_comp);
	        v1_comp  /= length;
	        v2_comp  /= length;
	 	    depth_buff = (v1.z*v2_comp + v2.z*v1_comp);
	 	    if(Run_Zbuffer(Startx,Starty,depth_buff))
			{
			c_buffer = (c1*v2_comp + c2*v1_comp);
			setcolor4f(c_buffer.x,c_buffer.y,c_buffer.z,0);    
			Putpixel(Startx, Starty);
			}
			Starty++;
		
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

void Colorshader::fillflat( vec3 v1, vec3 v2, vec3 v3, vec3 c1, vec3 c2, vec3 c3)
    {
		  float v2_comp, vv2_comp, v3_comp,vv3_comp, length2,length3;
          float depth1=9999, depth2=9999;
          float depth_buff=9999;
          vec3 c1_buffer=c1;
          vec3 c2_buffer=c1;
          vec3 pixel_color=c1;

		v1.toInt(); v2.toInt(); v3.toInt();
        int vTmp1[2];
        int vTmp2[2];
        vTmp1[0]=v1.x;
		vTmp1[1]=v1.y;
		vTmp2[0]=v1.x;
		vTmp2[1]=v1.y;
		
        bool changed1 = false;
        bool changed2 = false;
        
        int dx1 = abs(v2.x- v1.x);
        int dy1 = abs(v2.y - v1.y);
        
        int dx2 = abs(v3.x - v1.x);
        int dy2 = abs(v3.y - v1.y);
        
        int signx1=0;
        int signx2=0;
        
		if(v2.x>v1.x)
			signx1 = +1;
		else if(v2.x<v1.x)
			signx1 = -1;

		if(v3.x>v1.x)
			signx2 = +1;
		else if(v3.x<v1.x)
			signx2 = -1;

		int signy1=0;
        int signy2=0;

		if(v2.y>v1.y)
			signy1 = +1;
		else if(v2.y<v1.y)
			signy1 = -1;
       
		if(v3.y>v1.y)
			signy2 = +1;
		else if(v3.y<v1.y)
			signy2 = -1;
        

        if (dy1 > dx1)
        {   // swap values
            int tmp = dx1;
            dx1 = dy1;
            dy1 = tmp;
            changed1 = true;
        }
        
        if (dy2 > dx2)
        {   // swap values
            int tmp = dx2;
            dx2 = dy2;
            dy2 = tmp;
            changed2 = true;
        }
        
        int e1 = 2 * dy1 - dx1;
        int e2 = 2 * dy2 - dx2;
        
		int scanlineY = vTmp1[1];
		int curx1= vTmp1[0];
		int curx2= vTmp2[0];
		
		{
        for (int i = 0; i <= dx1; i++)
        {
			 scanlineY = vTmp1[1];
		     curx1= vTmp1[0];
			 curx2= vTmp2[0];
		
			v2_comp  = abs(v2.y-scanlineY) + abs(v2.x-curx1);
	        vv2_comp = abs(v1.y-scanlineY) + abs(v1.x-curx1);
	        v3_comp  = abs(v3.y-scanlineY) + abs(v3.x-curx2);
	        vv3_comp = abs(v1.y-scanlineY) + abs(v1.x-curx2);
	        length2 = (v2_comp + vv2_comp);
	        length3 = (v3_comp + vv3_comp);
			if(length2!=0)
			{
	        v2_comp  /= length2;
	        vv2_comp /= length2;
			}
			else
			{
			v2_comp =0.5;
	        vv2_comp =0.5;
			}

			if(length3!=0)
			{
			v3_comp  /= length3;
	        vv3_comp /= length3;
			}
			else
			{
		    v3_comp  = 0.5;
	        vv3_comp = 0.5;
			}

	        depth1  = (v1.z*v2_comp + v2.z*vv2_comp);
	        depth2  = (v1.z*v3_comp + v3.z*vv3_comp);

	        c1_buffer = (c1*v2_comp + c2*vv2_comp);
	        c2_buffer = (c1*v3_comp + c3*vv3_comp);
            
            
			for(int j=vTmp1[0];j<=vTmp2[0];j++)
			{
			  if(curx1!=curx2)
			  depth_buff  = depth1*abs((float)(curx2-j)/(curx2-curx1)) + depth2*abs((float)(j-curx1)/(curx2-curx1));
			  else 
				  depth_buff = depth1;
			  if(Run_Zbuffer(j,scanlineY,depth_buff))
		       {
				if(curx1!=curx2)
		         pixel_color = c1_buffer*abs((float)(curx2-j)/(curx2-curx1)) + c2_buffer*abs((float)(j-curx1)/(curx2-curx1));
				else
					pixel_color = c1_buffer;
		          if(pixel_color.x>1.0)
			          pixel_color.x=1;
		          if(pixel_color.y>1.0)
			          pixel_color.y=1;
                  if(pixel_color.z>1.0)
			          pixel_color.z=1;
		          setcolor4f(pixel_color.x,pixel_color.y,pixel_color.z,0);
		          
				  Putpixel(j,vTmp1[1]);
				  
		       }
			
			}
			
			while (e1 >= 0)
            {
                if (changed1)
                    vTmp1[0] += signx1;
                else
                    vTmp1[1] += signy1;
                if(dx1==0)
					e1=-1;
				e1 = e1 - 2 * dx1;
            }
			
            if (changed1)
                vTmp1[1] += signy1;
            else
                vTmp1[0] += signx1;  
          
            e1 = e1 + 2 * dy1;
            
            while (vTmp2[1] != vTmp1[1])
            {
				
                while (e2 >= 0)
                {
                    if (changed2)
                        vTmp2[0] += signx2;
                    else
                        vTmp2[1] += signy2;
					if(dx2==0)
						e2=-1;
				
                    e2 = e2 - 2 * dx2;
                }
				
                if (changed2)
                    vTmp2[1] += signy2;
                else
                    vTmp2[0] += signx2;

                e2 = e2 + 2 * dy2;
            }
			
        }
		}
  }      
  