const int sensorPin = 0; //pin A0 == analog pin 0
const int ledPin = 9; 

int lightLevel, low = 0, high = 1023;

void setup()
{
  //Setting pin 9 as the output
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}


void loop()
{

  lightLevel = analogRead(sensorPin);

  //manualTune();  // manually change the range from light to dark

  autoTune();  // have the Arduino do the work for us!


  analogWrite(ledPin, lightLevel);
  Serial.println(lightLevel);

}

void autoTune()
{

  if (lightLevel < low)
  {
    low = lightLevel;
  }


  if (lightLevel > high)
  {
    high = lightLevel;


  lightLevel = map(lightLevel, low+30, high-30, 0, 255);
  lightLevel = constrain(lightLevel, 0, 255);
  }

}
