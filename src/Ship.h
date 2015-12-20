
#ifndef _SHIP
#define _SHIP

class Ship
{
private:
	static const float MAX_SPEED = 12.0;
  static const int ROTATION_STEP = 3;
  int angle = 0;
  int boxWidth = 640;
  int boxHeight = 480;
  int x_pos;
  int y_pos;
  int x_vel;
  int y_vel;
  

public:
  void rotateCW();
  void rateteCCW();
  void thrust();
  
  int getAngle();
  int getxPos();
  int getyPos();
}; // end Ship

#include "Ship.cpp"
#endif
