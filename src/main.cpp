#include "Arduino.h"
#include "heltec.h"
#include "OneButton.h"
#include "CircularQueue.h"

/** Hardware Related Vars*/
int sensorPin = 36; // select the input pin for the potentiometer
int relayPin = 10;
int sensorValue = 0; // variable to store the value coming from the sensor
int loopsPressed = 0;

/** Password Related Vars*/
enum clickType {s, d,};
clickType lastEntered;
int passwordLength = 4;
int myPassword[4] = {s, d, d, s};
CircularQueue<int> pwQueue(4);
int currentIndex;
bool lastEnteredCorrect = false;

/** Relay Related Vars*/
bool relayEnabled = true;
bool needsRelayReset = false;

/** Display Related Vars*/
String currPassInfo = "Pass";
String currIndexInfo = "Info";
String currVerificationInfo = "Verification";
// StackArray <clickType> stack;

// threshold is 400 for the actual door / 320 for external dc power at 5v
// 1800 for the heltex
// OneButton button(sensorPin, true, false, true, 1900);
OneButton button(sensorPin, true);
CircularQueue<int> queue(5);

void triggerRelay()
{
  digitalWrite(relayPin, HIGH);
  delay(3000);
  digitalWrite(relayPin, LOW);
}

void outputPassInfo(String s){
 currPassInfo = s;
}

void outputIndexInfo(String s){
 currIndexInfo = s;
}
void outputVerificationInfo(String s){
 currVerificationInfo = s;
}

void verifyLastEntered()
{
  Serial.println(lastEntered);

  if (lastEntered == myPassword[currentIndex])
  {
    currentIndex++;
    Serial.println("good");
    outputPassInfo("good");
  }
  else
  {
    currentIndex = 0;
    Serial.println("bad");
    outputPassInfo("bad");
  }
  Serial.println("current index set to:");
  outputIndexInfo("Index now:" + String(currentIndex));
  Serial.println(currentIndex);
}

void doubleClick()
{
  Serial.println("DOUBLE CLICKED");
  lastEntered = d;
  verifyLastEntered();
} // doubleClick

void verifyPassword()
{
  Serial.println("current size of pw set to:");
  if (currentIndex == passwordLength)
  {
    Serial.println("Verified");
    outputVerificationInfo("Verified");
    
    //triggerRelay(); -- commented until we can get the relays working at 3v
  }
  else
  {
    Serial.println("Denied");
    outputVerificationInfo("Denied");
  }
  currentIndex = 0;
  outputIndexInfo("Index now:" + String(currentIndex));
}

void click()
{
  Serial.println("CLICKED");
  lastEntered = s;
  verifyLastEntered();
} // click

void longPress()
{
  Serial.println("LONG PRESSED");
  verifyPassword();
} // click

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(sensorPin, INPUT_PULLUP);  
  pinMode(sensorPin, INPUT_PULLUP);

  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->setFont(ArialMT_Plain_10); 
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT); 

  Serial.println("Monitor connected");
  Serial.println("Starting");
  // declare the ledPin as an OUTPUT:
  // pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  button.attachDoubleClick(doubleClick);
  button.attachClick(click);
  button.attachLongPressStop(longPress);
}

void loop()
{
  Heltec.display->clear();
  /*
  int sensorState = digitalRead(sensorPin);
  int buttonPressed = sensorState == LOW;
  int prevLoopsPressed = loopsPressed;
  if (buttonPressed){
    loopsPressed++;
    // Serial.print("Button Pressed Cnt: ");
    // Serial.println(loopsPressed);
  }
  Serial.println(sensorState);
  */
  
  
  // read the value from the sensor:

  button.tick();

  // sensorValue = analogRead(sensorPin);
  // int digval = digitalRead(sensorPin);  
  // String sensValStr = String(sensorValue);
  // String sensValStr = String(digval);
  // Heltec.display->drawString(0,0, sensValStr);
  
  // Heltec.display->drawString(0,0, String(loopsPressed));
  Heltec.display->drawString(0,0, button.getState());
  Heltec.display->drawString(0,10, currPassInfo);
 Heltec.display->drawString(0,20,currIndexInfo);
 Heltec.display->drawString(0,30, currVerificationInfo);
  Heltec.display->display();
  // Serial.println(digval);
// Serial.println(sensorValue);
}
