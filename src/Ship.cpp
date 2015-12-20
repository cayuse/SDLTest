#include "Ship.h"
#include <cmath>
#include <cstdint> 


#define PI 3.14159265

void Ship::rotateCW()
{
  angle = (angle + Ship::ROTATION_STEP) % 360;
}

void Ship::rotateCCW()
{
  angle = (angle - Ship::ROTATION_STEP) % 360;
}

void Ship::thrust()
{
  //apply the thrust vector
  x_vel += Ship::MAX_ACCEL * (sin ( (double)angle * PI / 180.0 ));
  y_vel -= Ship::MAX_ACCEL * (cos ( (double)angle * PI / 180.0 ));
  
  if (x_vel > Ship::MAX_SPEED)
  {
    x_vel = Ship::MAX_SPEED;
  }
  if (x_vel < -(Ship::MAX_SPEED))
  {
    x_vel = -(Ship::MAX_SPEED);
  }
  if (y_vel > Ship::MAX_SPEED)
  {
    y_vel = Ship::MAX_SPEED;
  }
  if (y_vel < -(Ship::MAX_SPEED))
  {
    y_vel = -(Ship::MAX_SPEED);
  }  
}

void Ship::getPosition(uint32_t deltaTicks, int &x, int &y, int &myAngle)
{
   x_pos += x_vel * ( deltaTicks / 1000.f );
   y_pos += y_vel * ( deltaTicks / 1000.f );
   
   if (x_pos >= boxWidth - 64 || x_pos <= 0)
   {
    x_vel = 0 - x_vel;
   }
      if (y_pos >= boxHeight - 64 || y_pos  <= 0)
   {
    y_vel = 0 - y_vel;
   }
   
   x = x_pos;
   y = y_pos;
   myAngle = angle;
}

