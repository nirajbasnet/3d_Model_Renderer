#define PI  3.141592f

#define max(a,b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))



static inline double RadToDeg(const double deg)	           //Radians to degrees
{
	return deg * 180.0 / PI;
};
static inline double DegToRad(const double rad)	          //Degrees to radians
{
	return rad * PI / 180.0;
};
static inline float constrain(float value,float lowerV,float upperV)
{
    if(value>=upperV)return upperV;
    else if (value<=lowerV)return lowerV;
    else
        return value;
}




