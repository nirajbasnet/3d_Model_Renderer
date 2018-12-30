#ifndef ROBOTBODY_H
#define ROBOTBODY_H
#include "scenenode.h"

class Robotframe :public Scenenode
{
protected:
		  Scenenode *Bodynode;
		  Scenenode *Headnode;
		  Scenenode *Rightarm_upper;
		  Scenenode *Rightarm_lower;
		  Scenenode *Leftarm_upper;
		  Scenenode *Leftarm_lower;
		  Scenenode *Rightleg_upper;
		  Scenenode *Rightleg_lower;
		  Scenenode *Leftleg_upper;
		  Scenenode *Leftleg_lower;

public:Robotframe();
	   ~Robotframe(){ }
	    virtual void Update(float deltatime);

};
#endif
