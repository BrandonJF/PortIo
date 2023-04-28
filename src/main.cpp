#include "Arduino.h"
#include "heltec.h"
#include "OneButton.h"
#include "CircularQueue.h"
#include <WiFi.h>
#include "NetworkManager.h"
#include "PasswordManager.h"
#include "Config.h"

/** Hardware Related Vars*/
const int sensorPin = 36; // select the input pin for the potentiometer
const int relayPin = 21;
int sensorValue = 0; // variable to store the value coming from the sensor
int loopsPressed = 0;

/** Password Related Vars*/

PasswordManager passMan({s, d, s, s, d});

/** Relay Related Vars*/
bool relayEnabled = true;
bool needsRelayReset = false;

/** Display Related Vars*/
String currPassInfo = "Pass";
String currIndexInfo = "Info";
String currVerificationInfo = "Verification";
OneButton button(sensorPin, true);
boolean relayOn = false;   

void triggerRelay()
{
  Serial.println("Triggering relay");
  digitalWrite(relayPin, HIGH);
  delay(3000);
  digitalWrite(relayPin, LOW);
}

auto lockCallback = []() { triggerRelay(); };

/** Networking */
NetworkManager network(WIFI_SSID, WIFI_PW, lockCallback);

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

void handleClick(ClickType click)
{
  PasswordStatus status = passMan.registerClick(click);
  Serial.println("Click handled: " + click);
  if (status == ACCEPTED)
  {
    triggerRelay();
  }
}

void doubleClick()
{
  handleClick(d);
} // doubleClick

void click()
{
  handleClick(s);
} // click

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(sensorPin, INPUT_PULLUP);

  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  network.setup_wifi();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);

  Serial.println("Monitor connected");
  Serial.println("Starting");
  pinMode(relayPin, OUTPUT);
  button.attachDoubleClick(doubleClick);
  button.attachClick(click);
  passMan.registerClick(s);
  passMan.registerClick(d);
  passMan.registerClick(s);
  passMan.registerClick(s);
  passMan.registerClick(d);
}

void loop()
{
  Heltec.display->clear();
  button.tick();
  network.checkConnected();
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
