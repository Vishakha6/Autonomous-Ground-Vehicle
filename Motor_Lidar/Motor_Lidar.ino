#include <RPLidar.h>
RPLidar lidar;

#define RPLIDAR_MOTOR 3

int left_fwd_dir = 5;
int left_fwd_pwm = 4;

int left_back_dir = 6;
int left_back_pwm = 7;

int right_fwd_dir = 8;
int right_fwd_pwm = 9;

int right_back_dir = 10;
int right_back_pwm = 11;



void setup() 
{
  lidar.begin(Serial);

  pinMode(RPLIDAR_MOTOR, OUTPUT);
  pinMode(left_fwd_dir, OUTPUT);
  pinMode(left_fwd_pwm, OUTPUT);
  pinMode(left_back_dir, OUTPUT);
  pinMode(left_back_pwm, OUTPUT);
  pinMode(right_fwd_dir, OUTPUT);
  pinMode(right_fwd_pwm, OUTPUT);
  pinMode(right_back_dir, OUTPUT);
  pinMode(right_back_pwm, OUTPUT);


}

void loop() 
{
  if (IS_OK(lidar.waitPoint())) 
  {
    float distance = lidar.getCurrentPoint().distance;
    float angle = lidar.getCurrentPoint().angle;

    if (lidar.getCurrentPoint().startBit)
    {

    
    
    if (distance > 0 && distance < 1000) 
    {
      
      digitalWrite(left_fwd_dir, 1);
      analogWrite(left_fwd_pwm, 200);
      digitalWrite(left_back_dir, 1);
      analogWrite(left_back_pwm, 200);
      digitalWrite(right_fwd_dir, 1);
      analogWrite(right_fwd_pwm, 200);
      digitalWrite(right_back_dir, 1);
      analogWrite(right_back_pwm, 200);
    }
    else if (distance >= 1000)
    {
      
      digitalWrite(left_fwd_dir, 1);
      analogWrite(left_fwd_pwm, 150);
      digitalWrite(left_back_dir, 1);
      analogWrite(left_back_pwm, 150);
      digitalWrite(right_fwd_dir, 0);
      analogWrite(right_fwd_pwm, 150);
      digitalWrite(right_back_dir, 0);
      analogWrite(right_back_pwm, 150);
    }
    
    
   }
  }
   else 
   {
    analogWrite(RPLIDAR_MOTOR, 0); 
    
    rplidar_response_device_info_t info;
    if (IS_OK(lidar.getDeviceInfo(info, 100))) 
    {
       lidar.startScan();
       analogWrite(RPLIDAR_MOTOR, 255);
       delay(1000);
    }
  }
}
