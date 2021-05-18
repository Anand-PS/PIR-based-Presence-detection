#include <Servo.h>

//Arduino based Code for PIR human Presence detection
//Hardware requirments: Servo(sg90) x 1 , PIR (140 degree) x 1 

//calibration
bool pir_logic = 1; // change it to 0 for active low PIR module
int speed_of_sweep  = 15; // if value increases speed will be decreased
int angle_of_sweep  = 90; // value should be in between 0 and 180 degrees
int delay_between_direction_change = 1000; // Delay between each direction change
int no_of_sweep_after_pir_low = 2; // number of sweep to be executed after the o/p of PIR becomes low

//

//Hardware Configuration
int pirPin = 2;
int servoPin = 3;
int load = 13;
//

//Global Variables
bool pir_flag = 0;
bool pir_value = 0;
int pos = 0;
bool pir_triggered_flag = 0;

Servo mainServo;



void setup()
{
  mainServo.attach(servoPin);
  pinMode(pirPin, INPUT);
  pinMode(load, OUTPUT);

}


void loop()
{
  pir_value = readPir();

  if (pir_value == HIGH)
  {
    digitalWrite(load, HIGH);
  }
  else
  {
    digitalWrite(load, LOW);
  }

}


bool readPir()
{
  if (digitalRead(pirPin) == pir_logic)
  {
    pir_triggered_flag  = 1;

    for (pos = 0; pos <= angle_of_sweep; pos += 1)
    {
      mainServo.write(pos);
      delay(speed_of_sweep);
    }

    delay(delay_between_direction_change);

    for (pos = angle_of_sweep; pos >= 0; pos -= 1)
    {
      mainServo.write(pos);
      delay(speed_of_sweep);
    }
    pir_flag = 1;
  }
  else if (pir_triggered_flag == 1 && digitalRead(pirPin) == !pir_logic) // when PIR becomes LOW
  {
    for (int i = 0; i < no_of_sweep_after_pir_low; i++)
    {
      for (pos = 0; pos <= angle_of_sweep; pos += 1)
      {
        mainServo.write(pos);
        delay(speed_of_sweep);
      }

      delay(delay_between_direction_change);

      for (pos = angle_of_sweep; pos >= 0; pos -= 1)
      {
        mainServo.write(pos);
        delay(speed_of_sweep);
      }
    }
    pir_triggered_flag = 0;

    pir_flag = 0;
  }
  return pir_flag;
}
