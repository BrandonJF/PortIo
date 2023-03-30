#include "Arduino.h"
#include "heltec.h"
// #include "images.h"
#include "OneButton.h"


enum clickType {
  s,
  d,
};
int sensorPin = A0;    // select the input pin for the potentiometer
int relayPin = 10;

int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int passwordLength = 4;
int myPassword[4] = {s, d, d, s};
bool relayEnabled = true;
bool needsRelayReset = false;
clickType lastEntered;
int currentIndex;
bool lastEnteredCorrect = false;
// StackArray <clickType> stack;

//threshold is 400 for the actual door / 320 for external dc power at 5v
OneButton button(sensorPin, true, false, true, 320);




void triggerRelay() {
  digitalWrite(relayPin,HIGH);
  delay(3000);
  digitalWrite(relayPin,LOW);
}


void verifyLastEntered() {
  Serial.println(lastEntered);

  if (lastEntered == myPassword[currentIndex])
  {
    currentIndex++;
      Serial.println("good");
  } else {
    currentIndex = 0;
      Serial.println("bad");
  }
    Serial.println("current index set to:");
    Serial.println(currentIndex);
}

void doubleClick()
{
  lastEntered = d;
verifyLastEntered();
} // doubleClick






void verifyPassword() {
Serial.println("current size of pw set to:"); 
   if (currentIndex == passwordLength)
  {
      Serial.println("Verified");
    triggerRelay();
  } else {
    currentIndex = 0;
      Serial.println("Denied");
  }
  
}

void click()
{
  lastEntered = s;
 verifyLastEntered();
} // click


void longPress()
{
 verifyPassword();
} // click


 void setup() {
  Serial.begin(115200);
  while (!Serial);
  pinMode(LED_BUILTIN, OUTPUT);

  Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
  Heltec.display->setFont(ArialMT_Plain_10);        //设置字体大小
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);//设置字体对齐方式
  
  
  Serial.println("Monitor connected");
  Serial.println("Starting");
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  button.attachDoubleClick(doubleClick);
  button.attachClick(click);
  button.attachLongPressStop(longPress);

  
}

void loop() {
  Heltec.display->clear();
     digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000); 
  Serial.println("looping...");
  Heltec.display->drawString(0, 26, "Hello world");
  Heltec.display->display();
  // read the value from the sensor:
  // button.tick();
  // sensorValue = analogRead(A0);
  // Serial.println(sensorValue);

  // delay(10);
  // triggerRelay();
}
