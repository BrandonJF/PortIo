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
enum clickType
{
  s,
  d,
};
clickType lastEntered;
int passwordLength = 4;
std::vector<clickType> pwVect = {s, d, s, d};

CircularQueue<clickType> pwQueue(4);
int currentIndex;
bool lastEnteredCorrect = false;

/** Relay Related Vars*/
bool relayEnabled = true;
bool needsRelayReset = false;

/** Display Related Vars*/
String currPassInfo = "Pass";
String currIndexInfo = "Info";
String currVerificationInfo = "Verification";
OneButton button(sensorPin, true);

void triggerRelay()
{
  digitalWrite(relayPin, HIGH);
  delay(3000);
  digitalWrite(relayPin, LOW);
}

void outputPassInfo(String s)
{
  currPassInfo = s;
}

void outputIndexInfo(String s)
{
  currIndexInfo = s;
}
void outputVerificationInfo(String s)
{
  currVerificationInfo = s;
}

void verifyLastEntered()
{
  Serial.println(lastEntered);

  pwQueue.enqueue(lastEntered);

  if (pwQueue == pwVect)
  {
    Serial.println("Password Accepted!");
    // triggerRelay(); -- commented until we can get the relays working at 3v
  }
}

void doubleClick()
{
  Serial.println("DOUBLE CLICKED");
  lastEntered = d;
  verifyLastEntered();
} // doubleClick

void click()
{
  Serial.println("CLICKED");
  lastEntered = s;
  verifyLastEntered();
} // click

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorPin, INPUT_PULLUP);

  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);

  Serial.println("Monitor connected");
  Serial.println("Starting");
  pinMode(relayPin, OUTPUT);
  button.attachDoubleClick(doubleClick);
  button.attachClick(click);
  // button.attachLongPressStop(longPress);
}

void loop()
{
  Heltec.display->clear();
  button.tick();

  // sensorValue = analogRead(sensorPin);
  // int digval = digitalRead(sensorPin);
  // String sensValStr = String(sensorValue);
  // String sensValStr = String(digval);
  // Heltec.display->drawString(0,0, sensValStr);
  // Heltec.display->drawString(0,0, String(loopsPressed));
  Heltec.display->drawString(0, 0, button.getState());
  Heltec.display->drawString(0, 10, currPassInfo);
  Heltec.display->drawString(0, 20, currIndexInfo);
  Heltec.display->drawString(0, 30, currVerificationInfo);
  Heltec.display->display();
}
