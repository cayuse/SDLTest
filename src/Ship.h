
#ifndef _SHIP
#define _SHIP

#include <cstdint>

class Ship
{
private:
  static constexpr float MAX_SPEED = 1200.0;
  static constexpr float MAX_ACCEL = 12.0;
  static constexpr int ROTATION_STEP = 3;
  int angle = 0;
  int boxWidth = 640;
  int boxHeight = 480;
  int x_pos = boxWidth / 2;
  int y_pos = boxHeight / 2;
  double x_vel;
  double y_vel;
  double getTrueSpeed(double new_x_vel, double new_y_vel);

public:
  void rotateCW();
  void rotateCCW();
  void thrust();
  void getPosition(uint32_t deltaTicks, int &x, int &y, int &myAngle);

}; // end Ship

#endif
