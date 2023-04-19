#include "NetworkManager.h"
#include "Arduino.h"
#include <WiFi.h>

NetworkManager::NetworkManager( ) : m_ssid(""), m_pw(0) {}

NetworkManager::NetworkManager(String ssid, String pw) : m_ssid(ssid), m_pw(pw) {}

String NetworkManager::getSsid() const {
    return m_ssid;
}

void NetworkManager::setSsid(String name) {
    m_ssid = name;
}

String NetworkManager::getPw() const {
    return m_pw;
}

void NetworkManager::setPw(String age) {
    m_pw = age;
}

void NetworkManager::connect() {
    delay(1000);

  // Connect to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(m_ssid);

  WiFi.begin(m_ssid.c_str(), m_pw.c_str());

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wi-Fi connected successfully");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}