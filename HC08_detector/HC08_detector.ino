/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using I2C to communicate
 3 pins are required to interface (two I2C and one reset).

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
//#include <SoftwareSerial2.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// SoftwareSerial mySerial(7, 8);

#define MAXLENGTH  9
uint8_t  receivedCommandStack[MAXLENGTH];
uint8_t  checkSum(uint8_t  array[], uint8_t  length);
boolean receivedFlag;
byte cmd[9];
//HardwareSerial ch08serial(0);//声明串口1

void setup() {
  Serial.begin(9600);
  //ch08serial.begin(9600,SERIAL_8N1);
 // mySerial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
  //  Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  //display.display();
  //delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  // display.display() is NOT necessary after every single drawing command,
  // unless that's what you want...rather, you can batch up a bunch of
  // drawing operations and then update the screen all at once by calling
  // display.display(). These examples demonstrate both approaches...

  // Invert and restore display, pausing in-between
  //display.invertDisplay(true);
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("CH08 Detecting ..."));
  display.display();
  while(Serial.available()>0)
  {
        for (int i = 0 ; i < 9 ; i++)
        {
          cmd[i] = Serial.read();
        }
  }
/*
      for (int i = 0 ; i < 9 ; i++){
        Serial2.print(cmd[i]);
        Serial2.print(" ");
      }
      Serial.println();
*/
    float ppm = ((cmd[4]*256+cmd[5])*1.0/1000.)*0.746;
    display.setTextSize(2);
  display.setCursor(0,20);             // Start at top-left corner
  display.print("PPM = ");
  display.println(ppm);
  //Serial.println(ppm);
  display.display();
  delay(1000);
}
/*
uint8_t  checkSum(uint8_t  array[], uint8_t  length)
{
  uint8_t  sum = 0;
  for (int i = 1; i < length - 1; i ++)
  {
    sum += array[i];
  }
  sum = (~sum) + 1;
  return sum;
}

boolean available1()    //new data was recevied
{
  while (ch08serial.available() > 0)
  {
    for (uint8_t  index = 0; index < MAXLENGTH - 1; index++)
    {
      receivedCommandStack[index] = receivedCommandStack[index + 1];
    }
    receivedCommandStack[MAXLENGTH - 1] = ch08serial.read();

    uint8_t  sumNum = checkSum(receivedCommandStack, MAXLENGTH);
   // if ( (receivedCommandStack[0] == 0xFF) && (receivedCommandStack[1] == 0x17) && (receivedCommandStack[2] == 0x04) && (receivedCommandStack[MAXLENGTH - 1] == sumNum) ) //head bit and sum are all right
     if ( (receivedCommandStack[0] == 0xFF) && (receivedCommandStack[1] == 0x17) && (receivedCommandStack[2] == 0x04)  ) //head bit and sum are all right

    {
      receivedFlag = 1;     //new data received
      return receivedFlag;
    } else {
      receivedFlag = 0;     //data loss or error
      return receivedFlag;
    }
  }
  return receivedFlag;
}

float ze08_PPM()
{
  
  if (available1() == 1)
  {
    receivedFlag = 0;
   
    float ppb = float(receivedCommandStack[4] * 256) + receivedCommandStack[5];  // bit 4: ppm high 8-bit; bit 5: ppm low 8-bit
    float ppm = ppb / 1000; //1ppb = 1000ppm
    //ppm = 3.1414;
    //delay (200);
  //  Serial.print("Formalin ppm == ");
  //  Serial.println(ppm);

 // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,20);

   display.clearDisplay();

    display.print("PPM = ");
    display.print(ppm);

    display.display();


    return ppm;
  }
}*/
