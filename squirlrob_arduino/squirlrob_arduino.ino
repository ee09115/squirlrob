#include <Servo.h>

#define MOTOR_LEFT_ZERO  39
#define MOTOR_RIGHT_ZERO 70

#define SCALE(value,zero) ((zero) == MOTOR_RIGHT_ZERO ? -(value)*80/510+MOTOR_RIGHT_ZERO : (value)*80/510+MOTOR_LEFT_ZERO)

Servo left_servo,right_servo;

void setup() 
{
  // Servos Initialization
  left_servo.attach(11);//71
  right_servo.attach(10);//40
  
  // Initialize Serial Port
  Serial.begin(9600);
  Serial.setTimeout(1000);
  
  // Set velocities to zero
  left_servo.write(SCALE(0,MOTOR_LEFT_ZERO));
  right_servo.write(SCALE(0,MOTOR_RIGHT_ZERO)); 
}

void loop()
{
  int v11 = 0, v22 = 0;
  char buf= -0x01; 
  Serial.readBytes(&buf,1);
  
  char parity, end1, end2;
  switch(buf)
  {
    case -0x01:
      // Set servo velocities to zero
      left_servo.write(SCALE(0,MOTOR_LEFT_ZERO));
      right_servo.write(SCALE(0,MOTOR_RIGHT_ZERO));
    break;
    case 0x00:
      char control;
      Serial.readBytes(&control,1);
      Serial.readBytes(&parity,1);
      Serial.readBytes(&end1,1);
      Serial.readBytes(&end2,1);
      //Serial.print(int(control));
    break;
    case 0x01:
      char v1, v2;
      Serial.readBytes(&v1,1);
      Serial.readBytes(&v2,1);
      Serial.readBytes(&parity,1);
      Serial.readBytes(&end1,1);
      Serial.readBytes(&end2,1);
      //Serial.print(int(v1));
      //Serial.print(' ');
      //Serial.println(int(v2));
      v11 = (v1 * (255/128.0));
      v22 = (v2 * (255/128.0));
      v11 = SCALE(v11,MOTOR_LEFT_ZERO);
      v22 = SCALE(v22,MOTOR_RIGHT_ZERO);
      left_servo.write(v11);
      right_servo.write(v22);
    break;
    case 0x02:
      char bumper;
      Serial.readBytes(&control,1);
      Serial.readBytes(&parity,1);
      Serial.readBytes(&end1,1);
      Serial.readBytes(&end2,1);
      //Serial.print(int(bumper));
    break;
    default:
    break;
  }
}
