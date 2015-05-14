/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial_arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <Servo.h> 
#include <Wire.h>

#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt16.h>

#define RUDDER_PIN 9
#define SAIL_PIN 10

ros::NodeHandle  nh;


// Servo
Servo rudder,sail;

void rudder_cb( const std_msgs::UInt16& cmd_msg){
  rudder.write(cmd_msg.data); //set servo angle, should be from 0-180  
}

void sail_cb( const std_msgs::UInt16& cmd_msg){
  sail.write(cmd_msg.data); //set servo angle, should be from 0-180  
}

ros::Subscriber<std_msgs::UInt16> sub_sail("rudder", rudder_cb);
ros::Subscriber<std_msgs::UInt16> sub_rudder("sail", sail_cb);

// Compass
std_msgs::Float32 compass_msg;
ros::Publisher pub_compass("compass", &compass_msg);
int compassAddress = 0x91 >> 1; 

float readCompass()
{
  return 0;
}

// Misc
long publisher_timer;


void setup(){
  Wire.begin();        // join i2c bus (address optional for master) 

  nh.initNode();
  nh.subscribe(sub_sail);
  nh.subscribe(sub_rudder);
  
  nh.advertise(pub_compass);
  
  rudder.attach(RUDDER_PIN); //attach it to pin 9
  sail.attach(SAIL_PIN); //attach it to pin 9
}

void loop(){
  
  if (millis() > publisher_timer) {
  // step 1: request reading from sensor 
    Wire.requestFrom(compassAddress,2); 
    delay(10);
    if (2 <= Wire.available())  // if two bytes were received 
    {
      byte msb;
      byte lsb;
      float angle;
      
      readCompass();
      
      compass_msg.data = angle;
      pub_compass.publish(&compass_msg);
    }
  
  publisher_timer = millis() + 1000;
  }
  
  nh.spinOnce();
  delay(1);
}
