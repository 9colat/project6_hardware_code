#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Empty.h>
#include <Servo.h>

int VRx = A1;
int VRy = A2;
int VRz = A3;
int VRalt = A4;

float pitch_map;
float roll_map;
float yaw_map;
float altitude_map;


int min_pitch_val = 0;
int max_pitch_val = 1023;
int min_roll_val = 0;
int max_roll_val = 1023;
int min_yaw_val = 0;
int max_yaw_val = 1023;
int min_altitude_val = 0;
int max_altitude_val = 1023;

Servo servo1;
Servo servo2;


ros::NodeHandle  nh;

std_msgs::Int16 xPosition;
ros::Publisher pitch_control_input("arduino_pitch_control_input", &xPosition);

std_msgs::Int16 yPosition;
ros::Publisher roll_control_input("arduino_roll_control_input", &yPosition);

std_msgs::Int16 zPosition;
ros::Publisher yaw_control_input("arduino_yaw_control_input", &zPosition);

std_msgs::Int16 altitudePosition;
ros::Publisher altitude_control_input("arduino_altitude_control_input", &altitudePosition);








void messageCb( const std_msgs::Int16& pitch_val){
  pitch_map = map(pitch_val.data, min_pitch_val, max_pitch_val, 0, 180);
  servo1.write(pitch_map);
}

void messageCg( const std_msgs::Int16& roll_val){
  roll_map = map(roll_val.data, min_roll_val, max_roll_val, 0, 180);
  servo2.write(roll_map);
}

ros::Subscriber<std_msgs::Int16> sub1("pitch_control_input", messageCb );
ros::Subscriber<std_msgs::Int16> sub2("roll_control_input", messageCg );



//std_msgs::String str_msg;
//ros::Publisher chatter("chatter", &str_msg);

//char hello[13] = "hello world!";

void setup()
{
//  pinMode(13, OUTPUT);
  nh.initNode();
  servo1.attach(2);
  servo2.attach(3);
  nh.subscribe(sub1);
  nh.subscribe(sub2);
  nh.advertise(pitch_control_input);
  nh.advertise(roll_control_input);
}

void loop()
{
//  str_msg.data = hello;
//  chatter.publish( &str_msg );
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(VRz, INPUT);
  pinMode(VRalt, INPUT);
  xPosition.data = analogRead(VRx);
  yPosition.data = analogRead(VRy);
  zPosition.data = analogRead(VRz);
  altitudePosition.data = analogRead(VRalt);
  pitch_control_input.publish( &xPosition );
  roll_control_input.publish( &yPosition );
  yaw_control_input.publish( &zPosition );
  altitude_control_input.publish( &altitudePosition );
  nh.spinOnce();
  //delay(500);
}
