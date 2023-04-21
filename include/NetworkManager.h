#pragma once

#include "Arduino.h"

class NetworkManager
{
public:
    // Default constructor
    NetworkManager();

    // Parameterized constructor
    NetworkManager(String ssid, String pw);

    // Getters and setters
    String getSsid() const;
    void setSsid(String ssid);

    String getPw() const;
    void setPw(String pw);

    void setup_wifi();

    void publish();

    void checkConnected();

    void reconnect();

private:
    String m_ssid;
    String m_pw;
    const char *ID = "PortIO";       // Name of our device, must be unique
    const char *TOPIC = "door/buzz"; // Topic to subcribe to
    const char *APT_DOOR_TOPIC = "building/door/set";
};
    void callback(char *topic, byte *payload, unsigned int length);
