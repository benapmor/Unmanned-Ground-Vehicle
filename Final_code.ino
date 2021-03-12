Onc#include <Servo.h>
Servo steering; //Creates a Servo object named steering
Servo turret;//creates a Servo object name turret, this will be used to control the turret
#define PWM 8 //names pin 8 as PWM, this pin is used to control the PWM of the motor
#define IN0_A 7 //names pin 7 as IN0_A (used to control motor direction)
#define TIMEOUT 5000 // mS
int forward=0;

void setup() 
{
  Serial.begin(9600);// starts a serial connection at a baudrate of 9600 (used for serial terminal/debugging)
  Serial2.begin(115200);
  SendCommand("AT+RST", "OK");
  delay(500);
  SendCommand("AT+CWMODE=3", "OK");
  delay(100);
  SendCommand("AT+CIPMUX=1","OK");
  delay(100);
  SendCommand("AT+CIPSERVER=1","OK");
  delay(100);
  SendCommand("AT+CWSAP=\"esp_123\",\"1234test\",5,3", "OK");
  delay(500);
  Serial.println("Ready");
  steering.attach(3);//attaches the steering servo to pin 4
  turret.attach(4);//attaches the turret servo object to pin 3
  steering.write(85);
}

void loop()
{
String hello;
hello=(retriveString());
Serial.println(hello);
}
boolean SendCommand(String cmd, String ack)
{
  Serial2.println(cmd); // Send "AT+" command to module

  if (!echoFind(ack)) // timed out waiting for ack string
    return true; // ack blank or ack found
}
boolean echoFind(String keyword){
 byte current_char = 0;
 byte keyword_length = keyword.length();
 String information="";
 long deadline = millis() + TIMEOUT;
 while(millis() < deadline){
  if (Serial2.available()){
    char ch = Serial2.read();
    information.concat(ch);
    Serial.write(ch);
    if (ch == keyword[current_char])
      if (++current_char == keyword_length){
       Serial.println();
       return true;
    }
   }
  }
 return false; // Timed out
}
String retriveString()
{
  long deadline = millis() + TIMEOUT;
  String information="";
 
    if (Serial2.available())
    {
        char ch = Serial2.read();
        information.concat(ch);
    }

  return information;
}
void doStuff(String info)
{
  if (info.indexOf("Forward")>0)
  {
    forwards();
  }
  else if(info.indexOf("Back")>0)
  {
   back();
  }
}
void forwards()
{
  Serial.println("Forwards");
    if (forward<4&&forward>=-1)
    {//c1
     forward++;
     digitalWrite(IN0_A,HIGH);
     analogWrite(PWM,(forward*63.75));
     }//c1
     Serial.println(forward);
     Serial.println();
}
void back()
{
 if (forward<=4&&forward>=0)
        {//d1
          forward--;
          analogWrite(PWM,(forward*63.75));//recreases the pwm value of the h-bridge in 25% increments
          if(forward<0)
          {
            digitalWrite(IN0_A,LOW);
            analogWrite(PWM,63.75);
          }
        }//d1
        Serial.println("Backwards");
        Serial.println();
        Serial.println(forward);
}
