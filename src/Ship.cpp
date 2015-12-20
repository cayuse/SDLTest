#include "Ship.h"
#include <cmath>


#define PI 3.14159265

void rotateCW()
{
  angle = (angle - ROTATION_STEP) % 360;
}

void rateteCCW()
{
  angle = (angle + ROTATION_STEP) % 360;
}

void thrust()
{
  //apply the thrust vector
  x_vel += MAX_ACCEL * (cos ( (double)angle * PI / 180.0 ));
  y_vel += MAX_ACCEL * (sin ( (double)angle * PI / 180.0 ));
  
  if (x_vel > MAX_SPEED)
  {
    x_vel = MAX_SPEED;
  }
  if (y_vel > MAX_SPEED)
  {
    y_vel = MAX_SPEED;
  }
  
}

void getPosition(Uint32 deltaTicks, int &x, int &y, int &angle)
{
  
}

