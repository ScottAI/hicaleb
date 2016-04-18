/*
 6-13-2011
 Spark Fun Electronics 2011
 Nathan Seidle
 
 This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 4 digit 7 segment display:
 http://www.sparkfun.com/products/9483
 Datasheet: 
 http://www.sparkfun.com/datasheets/Components/LED/7-Segment/YSD-439AR6B-35.pdf

 This is an example of how to drive a 7 segment LED display from an ATmega without the use of current limiting resistors.
 This technique is very common but requires some knowledge of electronics - you do run the risk of dumping too 
 much current through the segments and burning out parts of the display. If you use the stock code you should be ok, but 
 be careful editing the brightness values.
 
 This code should work with all colors (red, blue, yellow, green) but the brightness will vary from one color to the next
 because the forward voltage drop of each color is different. This code was written and calibrated for the red color.

 This code will work with most Arduinos but you may want to re-route some of the pins.

 7 segments
 4 digits
 1 colon
 =
 12 pins required for full control 

 17 April 2016 
 Updated by Brandon Sharitt and Caleb Sharitt. Abby Sharitt, didn't help, but Caleb wanted it to say hi to his sister too.
 Changes public domain too. You can also buy me a beer if you want. Don't buy Caleb a beer until 2031.
*/

int digit1 = 11; //PWM Display pin 1
int digit2 = 10; //PWM Display pin 2
int digit3 = 9; //PWM Display pin 6
int digit4 = 6; //PWM Display pin 8

//Pin mapping from Arduino to the ATmega DIP28 if you need it
//http://www.arduino.cc/en/Hacking/PinMapping
int segA = A1; //Display pin 14
int segB = 3; //Display pin 16
int segC = 4; //Display pin 13
int segD = 5; //Display pin 3
int segE = A0; //Display pin 5
int segF = 7; //Display pin 11
int segG = 8; //Display pin 15

char message[17] = "HI CALEB HI ABBY";
char first = ' ';
char second = ' ';
char third = ' ';
char fourth = ' ';

void setup() {
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  displayletter();
}

void displayletter() {
#define DISPLAY_BRIGHTNESS  50

#define DIGIT_ON  HIGH
#define DIGIT_OFF  LOW

  long beginTime = millis();

  for (int i = 0; i < 18; i++) {
    first = second;
    second = third;
    third = fourth;
    fourth = message[i];
    long startTime = millis();
    long endTime = startTime;


    while ( (endTime - startTime) < 1000) {
      for (int digit = 1 ; digit < 5 ; digit++) {

        //Turn on a digit for a short amount of time
        switch (digit) {
          case 1:
            digitalWrite(digit1, DIGIT_ON);
            lightletter(first);
            break;
          case 2:
            digitalWrite(digit2, DIGIT_ON);
            lightletter(second);
            break;
          case 3:
            digitalWrite(digit3, DIGIT_ON);
            lightletter(third);
            break;
          case 4:
            digitalWrite(digit4, DIGIT_ON);
            lightletter(fourth);
            break;
        }

        delayMicroseconds(DISPLAY_BRIGHTNESS); //Display this digit for a fraction of a second (between 1us and 5000us, 500 is pretty good)

        //Turn off all segments
        lightletter(10);

        //Turn off all digits
        digitalWrite(digit1, DIGIT_OFF);
        digitalWrite(digit2, DIGIT_OFF);
        digitalWrite(digit3, DIGIT_OFF);
        digitalWrite(digit4, DIGIT_OFF);
      }
      endTime = millis();
      Serial.println(endTime);
    }
  }

  while ( (millis() - beginTime) < 10) ; //Wait for 20ms to pass before we paint the display again
}

void lightletter(char chartodisplay) {

#define SEGMENT_ON  LOW
#define SEGMENT_OFF HIGH

  switch (chartodisplay) {

    case ' ':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;

    case 'A':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 'B':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 'C':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      break;

    case 'E':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 'H':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 'I':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;

    case 'L':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      break;

    case 'Y':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 10:
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;
  }
}

