
#include <Time.h>
#include <math.h>
/*
  Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.

 Created 9 May 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialEvent

 */


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int timezonediff = 6;// utc-mst
String timestring = "";
int count = 0;
void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  Serial.println("Initiate Sync");
  
  
}

void loop() {
  serialEvent(); //call the function
  // print the string when a newline arrives:
   if (stringComplete) {
    delay(1000);
    if(inputString == "Hi Arduino") {
      
      Serial.println("Hi Ruby");
    }
    if(inputString.toInt() > 1445471780) {
      if(count == 0){
        time_t t = inputString.toInt()-timezonediff*3600;
        setTime(t);
        count++;
      }
        
      timestring = String(month()) + " " + String(day()) + " " + String(year()) + " " + String(hour()) + ":";
        if (minute() < 10)
        {
          timestring = timestring + "0" + String(minute()) + ":";
        }
        else 
        {
          timestring = timestring  + String(minute()) + ":";
        }
        if (second() < 10)
        {
          timestring = timestring + "0" + String(second());
        }
        else 
        {
          timestring = timestring  + String(second());
        }
        
      Serial.println("Arduino Time Set To: " + timestring);
    }
    
    
    
    //Serial.flush();
    
    // clear the string:
    inputString = "";
    stringComplete = false;
    
    
  }
  
  
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      inputString.replace("\n","");
      Serial.flush();
    }
  }
}

