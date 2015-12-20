
#ifndef _SHIP
#define _SHIP

class Ship
{
private:
	static const float MAX_SPEED = 12.0;
  static const float MAX_ACCEL = 2.0;
  static const int ROTATION_STEP = 3;
  int angle = 0;
  int boxWidth = 640;
  int boxHeight = 480;
  int x_pos = boxWidth / 2;
  int y_pos = boxHeight / 2;
  double x_vel;
  double y_vel;
  

public:
  void rotateCW();
  void rateteCCW();
  void thrust();
  
  void getPosition(Uint32 deltaTicks, int &x, int &y, int &angle);

}; // end Ship

#include "Ship.cpp"
#endif
