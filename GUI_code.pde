import ipcapture.*;


import processing.net.*; //imports the processing network library
//IPCapture cam;
String inString;
Client myClient; //creates a client object
int timer;
 
void setup() { 
 // cam = new IPCapture(this, "http://"+"192.168.4.3:8080/video", "", "");
 // cam.start();
  size(1000 , 1000); //creates a 1000 by 1000 window
  background(66, 99, 245);//sets the background color
  rect(800,75,75,75); //creates 4 rectangles that wil be used to illustrate speed.
  rect(800,175,75,75);
  rect(800,275,75,75);
  rect(800,375,75,75);
  rect(170,600,100,50);
  textSize(32); //defines the size of the text
  text("Speed",795,50);//defines the text and the location
  // Connect to the local machine at port 333.
  myClient = new Client(this, "192.168.4.1", 333); //this connects to the esp-01 as a client on port 333(default)
} 
 
void draw() //void loop()
{ 
 // if (cam.isAvailable()) 
 // {
  //  cam.read();
  //  image(cam,0,0,750,500);
  //}
  if  (millis() - timer >= 500) 
  {
  myClient.write("beat");
  timer=millis();
  }
   //add delay before sending keep alive
}


void keyPressed() //function that detects a key press
{
if (key=='a'||key=='A')
  {
  myClient.write("Left");//writes the direction to the microcontroller
  }
else if(key=='s'||key=='S')
  {
    myClient.write("Back");
  }
else if(key=='d'||key=='D')
  {
   myClient.write("Right5");
  }
else if(key=='w'||key=='W')
  {
    myClient.write("Forward \0");
  }
else if(key=='u'||key=='U')
  {
    myClient.write("Update");
  }
else if(key==ENTER)
{
  //myClient.write("Emergency");
  fill(0);
  text("EMERGENCY",180,630);
  
}
else if(key==SHIFT)
{
}
}
