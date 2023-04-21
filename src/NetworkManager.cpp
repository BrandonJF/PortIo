#include "NetworkManager.h"
#include "Arduino.h"
#include <WiFi.h>
#include <PubSubClient.h>
#include "Config.h"






IPAddress broker(192, 168, 1, 48); // IP address of your MQTT broker eg. 192.168.1.50

WiFiClient wclient;

PubSubClient client(wclient); // Setup MQTT client

NetworkManager::NetworkManager() : m_ssid(""), m_pw(0), m_callback(NULL) {}

NetworkManager::NetworkManager(String ssid, String pw, LockCallback callback) : m_ssid(ssid), m_pw(pw), m_callback(callback){}

String NetworkManager::getSsid() const
{
    return m_ssid;
}

void NetworkManager::setSsid(String name)
{
    m_ssid = name;
}

String NetworkManager::getPw() const
{
    return m_pw;
}

void NetworkManager::setPw(String age)
{
    m_pw = age;
}

void NetworkManager::setup_wifi()
{
    delay(1000);

    // Connect to Wi-Fi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(m_ssid);

    WiFi.begin(m_ssid.c_str(), m_pw.c_str());

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("Wi-Fi connected successfully");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    client.setServer(broker, 1883);
    //https://hobbytronics.com.pk/arduino-custom-library-and-pubsubclient-call-back/
    client.setCallback([this] (char* topic, byte* payload, unsigned int length) { this->lockCallback(topic, payload, length); });

}

void NetworkManager::lockCallback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message received: ");
    Serial.println((char*) payload);
    m_callback();
}

// Reconnect to client
void NetworkManager::reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect
        if (client.connect(ID, HA_USER, HA_PASS))
        {
            Serial.println("connected");
            Serial.print("Publishing to: ");
            Serial.println(TOPIC);
            Serial.println('\n');
            publish();
            client.subscribe(APT_DOOR_TOPIC);
        }
        else
        {
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}
void NetworkManager::publish()
{
    const int state = 1;
    if (state == 1) // ON
    {
        client.publish(TOPIC, "door unlocked");
        Serial.println((String)TOPIC + " => on");
    }
    else // OFF
    {
        client.publish(TOPIC, "off");
        Serial.println((String)TOPIC + " => off");
    }
}

void NetworkManager::checkConnected()
{
    if (!client.loop())
    {
        reconnect();
    }
    client.loop(); // other docs said to do this, but i need to check
}
