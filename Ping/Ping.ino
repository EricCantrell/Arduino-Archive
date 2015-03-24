// http://www.instructables.com/id/Easy-ultrasonic-4-pin-sensor-monitoring-hc-sr04/

void setup() {
  pinMode (2,OUTPUT);//attach pin 2 to vcc
  pinMode (3,OUTPUT);// attach pin 3 to Trig
  pinMode (4, INPUT);//attach pin 4 to Echo
  pinMode (5,OUTPUT);//attach pin 5 to GND
  digitalWrite(2, HIGH);
  pinMode (13,OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}

String inputString = "";
String testString = "";
boolean stringComplete = false;  
  
void serialEvent() {  
  while (Serial.available()) {  
    char inChar = (char)Serial.read();  
    inputString += inChar;
    testString = inputString;
  
    if (inChar == '\n') {  
      stringComplete = true;  
    }  
  }  

  if(inputString == "light=OFF"){  
    digitalWrite(13, LOW); 
  }  
  else if (inputString == "light=ON"){  
    digitalWrite(13, HIGH);  
  } 
  inputString = "";
  stringComplete = false;  
}

void loop()
{
  Serial.print("test:"+testString);
  Serial.println();
  delay(2500);

  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(3, LOW);
  delayMicroseconds(2);
  digitalWrite(3, HIGH);
  delayMicroseconds(5);
  digitalWrite(3, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(4, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
 
  Serial.print("distance:");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(2500);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
