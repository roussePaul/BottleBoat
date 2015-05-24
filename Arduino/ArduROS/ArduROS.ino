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

#define USE_USBCON
#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>

#include "RC.h"

#define RUDDER_PIN 9
#define SAIL_PIN 10

#define RUDDER_MAGNETUDE 120  // magnitude of extrem angles (in degrees)
#define SAIL_MAGNETUDE 120    // magnitude of extrem angles (in degrees)


// --------------------
// ROS
ros::NodeHandle  nh;

// --------------------
// Servo
Servo rudder,sail;
boolean rosControl = true;

void rudder_cb( const std_msgs::UInt16& cmd_msg){
  if(rosControl == false)
    return;
  rudder.write(cmd_msg.data); //set servo angle, should be from 0-180  
}

void sail_cb( const std_msgs::UInt16& cmd_msg){
  if(rosControl == false)
    return;
  sail.write(cmd_msg.data); //set servo angle, should be from 0-180  
}

ros::Subscriber<std_msgs::UInt16> sub_sail("rudder", rudder_cb);
ros::Subscriber<std_msgs::UInt16> sub_rudder("sail", sail_cb);


// --------------------
// Compass
std_msgs::Float32 compass_msg;
ros::Publisher pub_compass("compass", &compass_msg);
int compassAddress = 0x91 >> 1; 

// --------------------
// Manual Control
void manualControl()
{
  float rudderSig = getChannel(0);
  float sailSig = getChannel(1);
  rudder.write(90-(0.5-rudderSig)*RUDDER_MAGNETUDE); //set servo angle, should be from 0-180  
  sail.write(90-(0.5-rudderSig)*SAIL_MAGNETUDE); //set servo angle, should be from 0-180  
}

// --------------------
// Debug
std_msgs::String debug;
ros::Publisher pub_debug("debug", &debug);


float readCompass()
{
  return 0;
}

// --------------------
// Misc
long publisher_timer;


// --------------------
//        BEGIN
// --------------------

void setup(){
  
  // Compass init
  Wire.begin();        // join i2c bus (address optional for master) 

  // RC init
  initRC();

  // ROS init
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.subscribe(sub_sail);
  nh.subscribe(sub_rudder);
  
  // Compass
  nh.advertise(pub_compass);
  
  // Debug
  nh.advertise(pub_debug);
  
  // Servo
  rudder.attach(RUDDER_PIN); //attach it to pin 9
  sail.attach(SAIL_PIN); //attach it to pin 9
}

void loop(){
  
  if (millis() > publisher_timer) {
  // step 1: request reading from sensor 
  publisher_timer = millis() + 1000;
  }
  
  nh.spinOnce();
  
  
  if(isChannelHigh(2) && rosControl==true)
  {
    rosControl = false;
    debug.data = "Manual control";
    pub_debug.publish(&debug);
  }
  else if(isChannelLow(2) && rosControl==false)
  {
    rosControl = true;
    debug.data = "Automatic control";
    pub_debug.publish(&debug);
  }
  
  if(rosControl==false)
  {
    manualControl();
  }
  
  delay(1);
}
